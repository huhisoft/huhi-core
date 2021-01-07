// Copyright (c) 2020 The Huhi Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#include "huhi/browser/profiles/huhi_profile_manager.h"

#include <memory>
#include <string>
#include <vector>

#include "base/metrics/histogram_macros.h"
#include "huhi/browser/huhi_rewards/rewards_service_factory.h"
#include "huhi/browser/profiles/profile_util.h"
#include "huhi/browser/translate/buildflags/buildflags.h"
#include "huhi/common/pref_names.h"
#include "huhi/components/huhi_ads/browser/ads_service_factory.h"
#include "huhi/components/huhi_shields/browser/ad_block_regional_service.h"
#include "huhi/components/huhi_shields/browser/ad_block_service.h"
#include "huhi/components/huhi_shields/browser/huhi_shields_util.h"
#include "huhi/components/huhi_wallet/buildflags/buildflags.h"
#include "huhi/components/huhi_webtorrent/browser/buildflags/buildflags.h"
#include "huhi/components/ipfs/buildflags/buildflags.h"
#include "huhi/components/tor/buildflags/buildflags.h"
#include "huhi/components/tor/pref_names.h"
#include "huhi/components/tor/tor_constants.h"
#include "huhi/components/tor/tor_profile_service.h"
#include "huhi/content/browser/webui/huhi_shared_resources_data_source.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/chrome_notification_types.h"
#include "chrome/browser/profiles/profile_attributes_entry.h"
#include "chrome/browser/profiles/profile_attributes_storage.h"
#include "chrome/browser/profiles/profiles_state.h"
#include "chrome/common/chrome_constants.h"
#include "chrome/common/pref_names.h"
#include "chrome/grit/generated_resources.h"
#include "components/bookmarks/common/bookmark_pref_names.h"
#include "components/gcm_driver/gcm_buildflags.h"
#include "components/prefs/pref_service.h"
#include "components/safe_browsing/core/common/safe_browsing_prefs.h"
#include "components/signin/public/base/signin_pref_names.h"
#include "components/translate/core/browser/translate_pref_names.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/notification_service.h"
#include "content/public/browser/notification_source.h"
#include "content/public/browser/url_data_source.h"
#include "extensions/buildflags/buildflags.h"
#include "third_party/blink/public/common/peerconnection/webrtc_ip_handling_policy.h"
#include "ui/base/l10n/l10n_util.h"

#if BUILDFLAG(ENABLE_EXTENSIONS)
#include "chrome/browser/extensions/extension_service.h"
#include "extensions/browser/extension_system.h"
#endif

#if BUILDFLAG(HUHI_WALLET_ENABLED)
#include "huhi/browser/huhi_wallet/huhi_wallet_service_factory.h"
#endif

#if !BUILDFLAG(USE_GCM_FROM_PLATFORM)
#include "huhi/browser/gcm_driver/huhi_gcm_channel_status.h"
#endif

#if BUILDFLAG(IPFS_ENABLED)
#include "huhi/browser/ipfs/ipfs_service_factory.h"
#endif

#if BUILDFLAG(ENABLE_TOR)
#include "huhi/browser/tor/tor_profile_service_factory.h"
#endif

using content::BrowserThread;

HuhiProfileManager::HuhiProfileManager(const base::FilePath& user_data_dir)
    : ProfileManager(user_data_dir) {
  MigrateProfileNames();

  registrar_.Add(this, chrome::NOTIFICATION_PROFILE_CREATED,
                 content::NotificationService::AllSources());
}

HuhiProfileManager::~HuhiProfileManager() {
  std::vector<Profile*> profiles = GetLoadedProfiles();
  for (Profile* profile : profiles) {
    if (huhi::IsSessionProfile(profile)) {
      // passing false for `success` removes the profile from the info cache
      OnProfileCreated(profile, false, false);
    }
  }
}

// static
// TODO(bridiver) - this should take the last used profile dir as an argument
base::FilePath HuhiProfileManager::GetTorProfilePath() {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);

  ProfileManager* profile_manager = g_browser_process->profile_manager();
  base::FilePath parent_path =
      profile_manager->GetLastUsedProfileDir(profile_manager->user_data_dir());

  DCHECK(!huhi::IsTorProfilePath(parent_path));

  base::FilePath tor_path = parent_path.AppendASCII("session_profiles");
  return tor_path.Append(tor::kTorProfileDir);
}

// static
void HuhiProfileManager::InitTorProfileUserPrefs(Profile* profile) {
  PrefService* pref_service = profile->GetPrefs();
  pref_service->SetInteger(prefs::kProfileAvatarIndex, 0);
  pref_service->SetBoolean(prefs::kProfileUsingDefaultName, false);
  pref_service
    ->SetString(prefs::kProfileName,
                l10n_util::GetStringUTF8(IDS_PROFILES_TOR_PROFILE_NAME));
  pref_service->SetString(prefs::kWebRTCIPHandlingPolicy,
                          blink::kWebRTCIPHandlingDisableNonProxiedUdp);
  pref_service->SetBoolean(prefs::kSafeBrowsingEnabled, false);
  // https://blog.torproject.org/bittorrent-over-tor-isnt-good-idea
#if BUILDFLAG(ENABLE_HUHI_WEBTORRENT)
  pref_service->SetBoolean(kWebTorrentEnabled, false);
#endif
  // Disable the automatic translate bubble in Tor because we currently don't
  // support extensions in Tor mode and users cannot disable this through
  // settings page for Tor windows.
#if BUILDFLAG(ENABLE_HUHI_TRANSLATE_EXTENSION)
  pref_service->SetBoolean(prefs::kOfferTranslateEnabled, false);
#endif
}

void HuhiProfileManager::InitProfileUserPrefs(Profile* profile) {
  if (huhi::IsTorProfile(profile)) {
    InitTorProfileUserPrefs(profile);
  } else {
    ProfileManager::InitProfileUserPrefs(profile);
    huhi::RecordInitialP3AValues(profile);
    huhi::SetDefaultSearchVersion(profile, profile->IsNewProfile());
  }
}

std::string HuhiProfileManager::GetLastUsedProfileName() {
  PrefService* local_state = g_browser_process->local_state();
  DCHECK(local_state);
  const std::string last_used_profile_name =
      local_state->GetString(prefs::kProfileLastUsed);
  if (last_used_profile_name ==
      base::FilePath(tor::kTorProfileDir).AsUTF8Unsafe())
    return chrome::kInitialProfile;
  return ProfileManager::GetLastUsedProfileName();
}

void HuhiProfileManager::DoFinalInitForServices(Profile* profile,
                                                 bool go_off_the_record) {
  ProfileManager::DoFinalInitForServices(profile, go_off_the_record);
  if (!do_final_services_init_)
    return;
  huhi_ads::AdsServiceFactory::GetForProfile(profile);
  huhi_rewards::RewardsServiceFactory::GetForProfile(profile);
#if BUILDFLAG(HUHI_WALLET_ENABLED)
  HuhiWalletServiceFactory::GetForProfile(profile);
#endif
#if BUILDFLAG(IPFS_ENABLED)
  ipfs::IpfsServiceFactory::GetForContext(profile);
#endif
#if !BUILDFLAG(USE_GCM_FROM_PLATFORM)
  gcm::HuhiGCMChannelStatus* status =
      gcm::HuhiGCMChannelStatus::GetForProfile(profile);
  DCHECK(status);
  status->UpdateGCMDriverStatus();
#endif
}

bool HuhiProfileManager::IsAllowedProfilePath(
    const base::FilePath& path) const {
  // Chromium only allows profiles to be created in the user_data_dir, but we
  // want to also be able to create profile in subfolders of user_data_dir.
  return ProfileManager::IsAllowedProfilePath(path) ||
         user_data_dir().IsParent(path.DirName());
}

void HuhiProfileManager::AddProfileToStorage(Profile* profile) {
  if (huhi::IsTorProfile(profile))
    return;
  ProfileManager::AddProfileToStorage(profile);
}

// Profile can be loaded sync or async; if sync, there is a matching block
// in `browser/profiles/huhi_profile_impl.cc` (constructor)
void HuhiProfileManager::OnProfileCreated(Profile* profile,
                                           bool success,
                                           bool is_new_profile) {
  ProfileManager::OnProfileCreated(profile, success, is_new_profile);

  if (!success)
    return;

#if BUILDFLAG(ENABLE_TOR)
  if (huhi::IsTorProfile(profile)) {
#if BUILDFLAG(ENABLE_EXTENSIONS)
    // This is added in addition to our AreExtensionsDisabled override in
    // huhi_extensions_browser_client_impl because there were extension
    // icons briefly showing up when opening Tor windows with that override
    // only.
    extensions::ExtensionService* extension_service =
        extensions::ExtensionSystem::Get(profile)->extension_service();
    // In tests, HuhiProfileManagerWithoutInit is used, so extension_service
    // won't be there.
    if (extension_service)
      extension_service->BlockAllExtensions();
#endif

    // We need to wait until OnProfileCreated to
    // ensure that the request context is available.
    TorProfileServiceFactory::GetForContext(profile);
  }
#endif
}

// This overridden method doesn't clear |kDefaultSearchProviderDataPrefName|.
// W/o this, prefs set by TorWindowSearchEngineProviderService is cleared
// during the initialization.
void HuhiProfileManager::SetNonPersonalProfilePrefs(Profile* profile) {
  PrefService* prefs = profile->GetPrefs();
  prefs->SetBoolean(prefs::kSigninAllowed, false);
  prefs->SetBoolean(bookmarks::prefs::kEditBookmarksEnabled, false);
  prefs->SetBoolean(bookmarks::prefs::kShowBookmarkBar, false);
}

void HuhiProfileManager::MigrateProfileNames() {
#if !defined(OS_ANDROID) && !defined(OS_CHROMEOS)
  // If any profiles have a default name using an
  // older version of the default name string format,
  // then name it with the new default name string format.
  // e.g. 'Person X' --> 'Profile X'.
  ProfileAttributesStorage& storage = GetProfileAttributesStorage();
  std::vector<ProfileAttributesEntry*> entries =
      storage.GetAllProfilesAttributesSortedByName();
  // Make sure we keep the numbering the same.
  for (auto* entry : entries) {
    // Rename the necessary profiles. Don't check for legacy names as profile
    // info cache should have migrated them by now.
    if (entry->IsUsingDefaultName() &&
        !storage.IsDefaultProfileName(
            entry->GetName(),
            /*include_check_for_legacy_profile_name=*/false)) {
      auto icon_index = entry->GetAvatarIconIndex();
      entry->SetLocalProfileName(storage.ChooseNameForNewProfile(icon_index));
    }
  }
#endif
}

void HuhiProfileManager::Observe(int type,
                                  const content::NotificationSource& source,
                                  const content::NotificationDetails& details) {
  switch (type) {
    case chrome::NOTIFICATION_PROFILE_CREATED: {
      Profile* profile = content::Source<Profile>(source).ptr();
      content::URLDataSource::Add(
          profile,
          std::make_unique<huhi_content::HuhiSharedResourcesDataSource>());
      break;
    }
    default: {
      ProfileManager::Observe(type, source, details);
      break;
    }
  }
}

HuhiProfileManagerWithoutInit::HuhiProfileManagerWithoutInit(
    const base::FilePath& user_data_dir)
    : HuhiProfileManager(user_data_dir) {
  set_do_final_services_init(false);
}
