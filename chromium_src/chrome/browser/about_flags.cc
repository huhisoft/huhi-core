/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/browser/about_flags.h"

#include "base/strings/string_util.h"
#include "huhi/common/huhi_features.h"
#include "huhi/common/pref_names.h"
#include "huhi/components/huhi_component_updater/browser/features.h"
#include "huhi/components/huhi_shields/common/features.h"
#include "huhi/components/huhi_sync/buildflags/buildflags.h"
#include "huhi/components/ipfs/buildflags/buildflags.h"
#include "huhi/components/ntp_background_images/browser/features.h"
#include "huhi/components/speedreader/buildflags.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_manager.h"
#include "components/prefs/pref_service.h"
#include "third_party/blink/public/common/features.h"

using huhi_shields::features::kHuhiAdblockCosmeticFiltering;
using ntp_background_images::features::kHuhiNTPBrandedWallpaper;
using ntp_background_images::features::kHuhiNTPBrandedWallpaperDemo;
using ntp_background_images::features::kHuhiNTPSuperReferralWallpaper;


#if BUILDFLAG(ENABLE_SPEEDREADER)
#include "huhi/components/speedreader/features.h"

#define SPEEDREADER_FEATURE_ENTRIES \
    {"huhi-speedreader",                                                  \
     flag_descriptions::kHuhiSpeedreaderName,                             \
     flag_descriptions::kHuhiSpeedreaderDescription, kOsDesktop,          \
     FEATURE_VALUE_TYPE(speedreader::kSpeedreaderFeature)},
#else
#define SPEEDREADER_FEATURE_ENTRIES
#endif

#if BUILDFLAG(ENABLE_HUHI_SYNC)
#include "huhi/components/huhi_sync/features.h"

#define HUHI_SYNC_FEATURE_ENTRIES                                         \
    {"huhi-sync-v2",                                                      \
     flag_descriptions::kHuhiSyncName,                                    \
     flag_descriptions::kHuhiSyncDescription, kOsDesktop,                 \
     FEATURE_VALUE_TYPE(huhi_sync::features::kHuhiSync)},
#else
#define HUHI_SYNC_FEATURE_ENTRIES
#endif

#if BUILDFLAG(IPFS_ENABLED)
#include "huhi/components/ipfs/features.h"

#define HUHI_IPFS_FEATURE_ENTRIES                                         \
    {"huhi-ipfs",                                                         \
     flag_descriptions::kHuhiIpfsName,                                    \
     flag_descriptions::kHuhiIpfsDescription, kOsDesktop,                 \
     FEATURE_VALUE_TYPE(ipfs::features::kIpfsFeature)},
#else
#define HUHI_IPFS_FEATURE_ENTRIES
#endif

#define HUHI_FEATURE_ENTRIES \
    {"use-dev-updater-url",                                                \
     flag_descriptions::kUseDevUpdaterUrlName,                             \
     flag_descriptions::kUseDevUpdaterUrlDescription, kOsAll,              \
     FEATURE_VALUE_TYPE(huhi_component_updater::kUseDevUpdaterUrl)},      \
    {"huhi-ntp-branded-wallpaper",                                        \
     flag_descriptions::kHuhiNTPBrandedWallpaperName,                     \
     flag_descriptions::kHuhiNTPBrandedWallpaperDescription, kOsAll,      \
     FEATURE_VALUE_TYPE(kHuhiNTPBrandedWallpaper)},                       \
    {"huhi-ntp-branded-wallpaper-demo",                                   \
     flag_descriptions::kHuhiNTPBrandedWallpaperDemoName,                 \
     flag_descriptions::kHuhiNTPBrandedWallpaperDemoDescription, kOsAll,  \
     FEATURE_VALUE_TYPE(kHuhiNTPBrandedWallpaperDemo)},                   \
    {"huhi-adblock-cosmetic-filtering",                                   \
     flag_descriptions::kHuhiAdblockCosmeticFilteringName,                \
     flag_descriptions::kHuhiAdblockCosmeticFilteringDescription, kOsAll, \
     FEATURE_VALUE_TYPE(kHuhiAdblockCosmeticFiltering)},                  \
    SPEEDREADER_FEATURE_ENTRIES                                            \
    HUHI_SYNC_FEATURE_ENTRIES                                             \
    HUHI_IPFS_FEATURE_ENTRIES                                             \
    {"huhi-super-referral",                                               \
     flag_descriptions::kHuhiSuperReferralName,                           \
     flag_descriptions::kHuhiSuperReferralDescription,                    \
     flags_ui::kOsMac | flags_ui::kOsWin | flags_ui::kOsAndroid,           \
     FEATURE_VALUE_TYPE(kHuhiNTPSuperReferralWallpaper)},                 \
    {"huhi-ephemeral-storage",                                            \
     flag_descriptions::kHuhiEphemeralStorageName,                        \
     flag_descriptions::kHuhiEphemeralStorageDescription, kOsAll,         \
     FEATURE_VALUE_TYPE(blink::features::kHuhiEphemeralStorage)},

#define SetFeatureEntryEnabled SetFeatureEntryEnabled_ChromiumImpl
#include "../../../../chrome/browser/about_flags.cc"  // NOLINT
#undef SetFeatureEntryEnabled
#undef HUHI_FEATURE_ENTRIES

namespace about_flags {

void UpdateHuhiMediaRouterPref(const std::string& internal_name,
                                Profile* profile) {
  bool enable = false;
  if (base::EndsWith(internal_name, "@1", base::CompareCase::SENSITIVE)) {
    enable = true;
  }
  if (base::StartsWith(internal_name, "load-media-router-component-extension",
                       base::CompareCase::SENSITIVE)) {
    profile->GetPrefs()->SetBoolean(kHuhiEnabledMediaRouter, enable);
  }
}

void SetFeatureEntryEnabled(flags_ui::FlagsStorage* flags_storage,
                            const std::string& internal_name,
                            bool enable) {
  UpdateHuhiMediaRouterPref(internal_name,
                             ProfileManager::GetActiveUserProfile());
  SetFeatureEntryEnabled_ChromiumImpl(flags_storage, internal_name, enable);
}

}  // namespace about_flags
