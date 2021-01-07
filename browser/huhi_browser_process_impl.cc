/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/huhi_browser_process_impl.h"

#include <utility>

#include "base/bind.h"
#include "base/path_service.h"
#include "base/task/post_task.h"
#include "base/threading/sequenced_task_runner_handle.h"
#include "huhi/browser/huhi_stats/huhi_stats_updater.h"
#include "huhi/browser/component_updater/huhi_component_updater_configurator.h"
#include "huhi/browser/component_updater/huhi_component_updater_delegate.h"
#include "huhi/browser/net/huhi_system_request_handler.h"
#include "huhi/browser/profiles/huhi_profile_manager.h"
#include "huhi/browser/themes/huhi_dark_mode_utils.h"
#include "huhi/browser/ui/huhi_browser_command_controller.h"
#include "huhi/common/pref_names.h"
#include "huhi/components/huhi_component_updater/browser/huhi_on_demand_updater.h"
#include "huhi/components/huhi_component_updater/browser/local_data_files_service.h"
#include "huhi/components/huhi_shields/browser/ad_block_custom_filters_service.h"
#include "huhi/components/huhi_shields/browser/ad_block_regional_service_manager.h"
#include "huhi/components/huhi_shields/browser/ad_block_service.h"
#include "huhi/components/huhi_shields/browser/https_everywhere_service.h"
#include "huhi/components/huhi_shields/browser/tracking_protection_service.h"
#include "huhi/components/huhi_sync/buildflags/buildflags.h"
#include "huhi/components/huhi_sync/network_time_helper.h"
#include "huhi/components/ntp_background_images/browser/features.h"
#include "huhi/components/ntp_background_images/browser/ntp_background_images_service.h"
#include "huhi/components/p3a/buildflags.h"
#include "huhi/components/p3a/huhi_histogram_rewrite.h"
#include "huhi/components/p3a/huhi_p3a_service.h"
#include "huhi/services/network/public/cpp/system_request_handler.h"
#include "chrome/browser/component_updater/component_updater_utils.h"
#include "chrome/browser/net/system_network_context_manager.h"
#include "chrome/common/buildflags.h"
#include "chrome/common/chrome_paths.h"
#include "components/component_updater/component_updater_service.h"
#include "components/component_updater/timer_update_scheduler.h"
#include "content/public/browser/browser_thread.h"
#include "services/network/public/cpp/resource_request.h"
#include "services/network/public/cpp/shared_url_loader_factory.h"

#if BUILDFLAG(ENABLE_NATIVE_NOTIFICATIONS)
#include "chrome/browser/notifications/notification_platform_bridge.h"
#include "huhi/browser/notifications/huhi_notification_platform_bridge.h"
#endif

#if BUILDFLAG(BUNDLE_WIDEVINE_CDM)
#include "huhi/browser/widevine/huhi_widevine_bundle_manager.h"
#endif

#if BUILDFLAG(ENABLE_HUHI_REFERRALS)
#include "huhi/browser/huhi_referrals/huhi_referrals_service_factory.h"
#include "huhi/components/huhi_referrals/browser/huhi_referrals_service.h"
#endif

#if BUILDFLAG(ENABLE_EXTENSIONS)
#include "huhi/common/extensions/whitelist.h"
#include "huhi/components/huhi_component_updater/browser/extension_whitelist_service.h"
#endif

#if BUILDFLAG(ENABLE_GREASELION)
#include "huhi/components/greaselion/browser/greaselion_download_service.h"
#endif

#if BUILDFLAG(ENABLE_TOR)
#include "huhi/components/tor/huhi_tor_client_updater.h"
#include "huhi/components/tor/pref_names.h"
#endif

#if BUILDFLAG(IPFS_ENABLED)
#include "huhi/components/ipfs/huhi_ipfs_client_updater.h"
#endif

#if BUILDFLAG(ENABLE_SPEEDREADER)
#include "huhi/components/speedreader/speedreader_rewriter_service.h"
#endif

#if defined(OS_ANDROID)
#include "chrome/browser/flags/android/chrome_feature_list.h"
#include "chrome/browser/android/component_updater/background_task_update_scheduler.h"
#else
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_list.h"
#endif

#if BUILDFLAG(HUHI_ADS_ENABLED)
#include "huhi/components/huhi_user_model/browser/user_model_file_service.h"
#endif

using huhi_component_updater::HuhiComponent;
using ntp_background_images::features::kHuhiNTPBrandedWallpaper;
using ntp_background_images::NTPBackgroundImagesService;

namespace {

// Initializes callback for SystemRequestHandler
void InitSystemRequestHandlerCallback() {
  network::SystemRequestHandler::OnBeforeSystemRequestCallback
      before_system_request_callback = base::Bind(huhi::OnBeforeSystemRequest);
  network::SystemRequestHandler::GetInstance()
      ->RegisterOnBeforeSystemRequestCallback(before_system_request_callback);
}

}  // namespace

HuhiBrowserProcessImpl* g_huhi_browser_process = nullptr;

using content::BrowserThread;

HuhiBrowserProcessImpl::~HuhiBrowserProcessImpl() {}

HuhiBrowserProcessImpl::HuhiBrowserProcessImpl(StartupData* startup_data)
    : BrowserProcessImpl(startup_data) {
  g_browser_process = this;
  g_huhi_browser_process = this;

#if BUILDFLAG(ENABLE_HUHI_REFERRALS)
  huhi_referrals_service_ = huhi::HuhiReferralsServiceFactory::GetInstance()
    ->GetForPrefs(local_state());
  base::SequencedTaskRunnerHandle::Get()->PostDelayedTask(
      FROM_HERE,
      base::BindOnce(
          [](huhi::HuhiReferralsService* referrals_service) {
            referrals_service->Start();
          },
          base::Unretained(huhi_referrals_service_.get())),
      base::TimeDelta::FromSeconds(3));
#endif

  base::SequencedTaskRunnerHandle::Get()->PostTask(
      FROM_HERE, base::BindOnce(
                     [](huhi_stats::HuhiStatsUpdater* stats_updater) {
                       stats_updater->Start();
                     },
                     base::Unretained(huhi_stats_updater())));
  // Disabled on mobile platforms, see for instance issues/6176
#if BUILDFLAG(HUHI_P3A_ENABLED)
  // Create P3A Service early to catch more histograms. The full initialization
  // should be started once browser process impl is ready.
  huhi_p3a_service();
  huhi::SetupHistogramsHuhiization();
#endif  // BUILDFLAG(HUHI_P3A_ENABLED)
}

void HuhiBrowserProcessImpl::Init() {
  BrowserProcessImpl::Init();

  huhi_component_updater::HuhiOnDemandUpdater::GetInstance()->
      RegisterOnDemandUpdateCallback(
          base::BindRepeating(&component_updater::HuhiOnDemandUpdate));
  UpdateHuhiDarkMode();
  pref_change_registrar_.Add(
      kHuhiDarkMode,
      base::Bind(&HuhiBrowserProcessImpl::OnHuhiDarkModeChanged,
                 base::Unretained(this)));

#if BUILDFLAG(ENABLE_TOR)
  pref_change_registrar_.Add(
      tor::prefs::kTorDisabled,
      base::Bind(&HuhiBrowserProcessImpl::OnTorEnabledChanged,
                 base::Unretained(this)));
#endif

  InitSystemRequestHandlerCallback();
}

huhi_component_updater::HuhiComponent::Delegate*
HuhiBrowserProcessImpl::huhi_component_updater_delegate() {
  if (!huhi_component_updater_delegate_)
    huhi_component_updater_delegate_ =
        std::make_unique<huhi::HuhiComponentUpdaterDelegate>();

  return huhi_component_updater_delegate_.get();
}

ProfileManager* HuhiBrowserProcessImpl::profile_manager() {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  if (!created_profile_manager_)
    CreateProfileManager();
  return profile_manager_.get();
}

void HuhiBrowserProcessImpl::StartHuhiServices() {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);

  ad_block_service()->Start();
  https_everywhere_service()->Start();

#if BUILDFLAG(ENABLE_EXTENSIONS)
  extension_whitelist_service();
#endif
  tracking_protection_service();
#if BUILDFLAG(ENABLE_GREASELION)
  greaselion_download_service();
#endif
#if BUILDFLAG(ENABLE_SPEEDREADER)
  speedreader_rewriter_service();
#endif
#if BUILDFLAG(HUHI_ADS_ENABLED)
  user_model_file_service();
#endif
  // Now start the local data files service, which calls all observers.
  local_data_files_service()->Start();

#if BUILDFLAG(ENABLE_HUHI_SYNC)
  huhi_sync::NetworkTimeHelper::GetInstance()
    ->SetNetworkTimeTracker(g_browser_process->network_time_tracker());
#endif
}

huhi_shields::AdBlockService* HuhiBrowserProcessImpl::ad_block_service() {
  if (ad_block_service_)
    return ad_block_service_.get();

  ad_block_service_ =
      huhi_shields::AdBlockServiceFactory(huhi_component_updater_delegate());
  return ad_block_service_.get();
}

huhi_shields::AdBlockCustomFiltersService*
HuhiBrowserProcessImpl::ad_block_custom_filters_service() {
  return ad_block_service()->custom_filters_service();
}

huhi_shields::AdBlockRegionalServiceManager*
HuhiBrowserProcessImpl::ad_block_regional_service_manager() {
  return ad_block_service()->regional_service_manager();
}

NTPBackgroundImagesService*
HuhiBrowserProcessImpl::ntp_background_images_service() {
  if (!base::FeatureList::IsEnabled(kHuhiNTPBrandedWallpaper))
    return nullptr;

  if (!ntp_background_images_service_) {
    ntp_background_images_service_ =
        std::make_unique<NTPBackgroundImagesService>(component_updater(),
                                                     local_state());
    ntp_background_images_service_->Init();
  }

  return ntp_background_images_service_.get();
}

#if BUILDFLAG(ENABLE_EXTENSIONS)
huhi_component_updater::ExtensionWhitelistService*
HuhiBrowserProcessImpl::extension_whitelist_service() {
  if (!extension_whitelist_service_) {
    extension_whitelist_service_ =
        huhi_component_updater::ExtensionWhitelistServiceFactory(
            local_data_files_service(), kVettedExtensions);
  }
  return extension_whitelist_service_.get();
}
#endif

#if BUILDFLAG(ENABLE_GREASELION)
greaselion::GreaselionDownloadService*
HuhiBrowserProcessImpl::greaselion_download_service() {
  if (!greaselion_download_service_) {
    greaselion_download_service_ = greaselion::GreaselionDownloadServiceFactory(
        local_data_files_service());
  }
  return greaselion_download_service_.get();
}
#endif

huhi_shields::TrackingProtectionService*
HuhiBrowserProcessImpl::tracking_protection_service() {
  if (!tracking_protection_service_) {
    tracking_protection_service_ =
        huhi_shields::TrackingProtectionServiceFactory(
            local_data_files_service());
  }
  return tracking_protection_service_.get();
}

huhi_shields::HTTPSEverywhereService*
HuhiBrowserProcessImpl::https_everywhere_service() {
  if (!https_everywhere_service_)
    https_everywhere_service_ = huhi_shields::HTTPSEverywhereServiceFactory(
        huhi_component_updater_delegate());
  return https_everywhere_service_.get();
}

huhi_component_updater::LocalDataFilesService*
HuhiBrowserProcessImpl::local_data_files_service() {
  if (!local_data_files_service_)
    local_data_files_service_ =
        huhi_component_updater::LocalDataFilesServiceFactory(
            huhi_component_updater_delegate());
  return local_data_files_service_.get();
}

void HuhiBrowserProcessImpl::UpdateHuhiDarkMode() {
  // Update with proper system theme to make huhi theme and base ui components
  // theme use same theme.
  dark_mode::SetSystemDarkMode(dark_mode::GetHuhiDarkModeType());
}

void HuhiBrowserProcessImpl::OnHuhiDarkModeChanged() {
  UpdateHuhiDarkMode();
}

#if BUILDFLAG(ENABLE_TOR)
tor::HuhiTorClientUpdater*
HuhiBrowserProcessImpl::tor_client_updater() {
  if (tor_client_updater_)
    return tor_client_updater_.get();

  base::FilePath user_data_dir;
  base::PathService::Get(chrome::DIR_USER_DATA, &user_data_dir);

  tor_client_updater_.reset(new tor::HuhiTorClientUpdater(
      huhi_component_updater_delegate(), local_state(), user_data_dir));
  return tor_client_updater_.get();
}

void HuhiBrowserProcessImpl::OnTorEnabledChanged() {
  // Update all browsers' tor command status.
  for (Browser* browser : *BrowserList::GetInstance()) {
    static_cast<chrome::HuhiBrowserCommandController*>(
        browser->command_controller())->UpdateCommandForTor();
  }
}
#endif

huhi::HuhiP3AService* HuhiBrowserProcessImpl::huhi_p3a_service() {
  if (huhi_p3a_service_) {
    return huhi_p3a_service_.get();
  }
  huhi_p3a_service_ = new huhi::HuhiP3AService(local_state());
  huhi_p3a_service()->InitCallbacks();
  return huhi_p3a_service_.get();
}

#if BUILDFLAG(BUNDLE_WIDEVINE_CDM)
HuhiWidevineBundleManager*
HuhiBrowserProcessImpl::huhi_widevine_bundle_manager() {
  if (!huhi_widevine_bundle_manager_)
    huhi_widevine_bundle_manager_.reset(new HuhiWidevineBundleManager);
  return huhi_widevine_bundle_manager_.get();
}
#endif

huhi_stats::HuhiStatsUpdater* HuhiBrowserProcessImpl::huhi_stats_updater() {
  if (!huhi_stats_updater_)
    huhi_stats_updater_ = huhi_stats::HuhiStatsUpdaterFactory(local_state());
  return huhi_stats_updater_.get();
}

void HuhiBrowserProcessImpl::CreateProfileManager() {
  DCHECK(!created_profile_manager_ && !profile_manager_);
  created_profile_manager_ = true;

  base::FilePath user_data_dir;
  base::PathService::Get(chrome::DIR_USER_DATA, &user_data_dir);
  profile_manager_ = std::make_unique<HuhiProfileManager>(user_data_dir);
}

NotificationPlatformBridge*
HuhiBrowserProcessImpl::notification_platform_bridge() {
#if !defined(OS_MAC)
  return BrowserProcessImpl::notification_platform_bridge();
#else
#if BUILDFLAG(ENABLE_NATIVE_NOTIFICATIONS)
  if (!created_notification_bridge_)
    CreateNotificationPlatformBridge();
  return notification_bridge_.get();
#else
  return nullptr;
#endif
#endif
}

void HuhiBrowserProcessImpl::CreateNotificationPlatformBridge() {
#if defined(OS_MAC)
#if BUILDFLAG(ENABLE_NATIVE_NOTIFICATIONS)
  DCHECK(!notification_bridge_);
  notification_bridge_ = HuhiNotificationPlatformBridge::Create();
  created_notification_bridge_ = true;
#endif
#endif
}

#if BUILDFLAG(ENABLE_SPEEDREADER)
speedreader::SpeedreaderRewriterService*
HuhiBrowserProcessImpl::speedreader_rewriter_service() {
  if (!speedreader_rewriter_service_) {
    speedreader_rewriter_service_.reset(
        new speedreader::SpeedreaderRewriterService(
            huhi_component_updater_delegate()));
  }
  return speedreader_rewriter_service_.get();
}
#endif  // BUILDFLAG(ENABLE_SPEEDREADER)

#if BUILDFLAG(HUHI_ADS_ENABLED)
huhi_user_model::UserModelFileService*
HuhiBrowserProcessImpl::user_model_file_service() {
  if (!user_model_file_service_) {
    user_model_file_service_.reset(
        new huhi_user_model::UserModelFileService(
            huhi_component_updater_delegate()));
  }
  return user_model_file_service_.get();
}

#endif  // BUILDFLAG(HUHI_ADS_ENABLED)

#if BUILDFLAG(IPFS_ENABLED)
ipfs::HuhiIpfsClientUpdater*
HuhiBrowserProcessImpl::ipfs_client_updater() {
  if (ipfs_client_updater_)
    return ipfs_client_updater_.get();

  base::FilePath user_data_dir;
  base::PathService::Get(chrome::DIR_USER_DATA, &user_data_dir);

  ipfs_client_updater_ = ipfs::HuhiIpfsClientUpdaterFactory(
      huhi_component_updater_delegate(), user_data_dir);
  return ipfs_client_updater_.get();
}
#endif  // BUILDFLAG(IPFS_ENABLED)
