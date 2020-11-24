/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_HUHI_BROWSER_PROCESS_IMPL_H_
#define HUHI_BROWSER_HUHI_BROWSER_PROCESS_IMPL_H_

#include <memory>

#include "base/memory/ref_counted.h"
#include "huhi/browser/tor/buildflags.h"
#include "huhi/components/huhi_ads/browser/buildflags/buildflags.h"
#include "huhi/components/huhi_component_updater/browser/huhi_component.h"
#include "huhi/components/huhi_referrals/buildflags/buildflags.h"
#include "huhi/components/greaselion/browser/buildflags/buildflags.h"
#include "huhi/components/ipfs/browser/buildflags/buildflags.h"
#include "huhi/components/speedreader/buildflags.h"
#include "chrome/browser/browser_process_impl.h"
#include "extensions/buildflags/buildflags.h"
#include "third_party/widevine/cdm/buildflags.h"

namespace huhi {
class HuhiReferralsService;
class HuhiStatsUpdater;
class HuhiP3AService;
}  // namespace huhi

#if BUILDFLAG(BUNDLE_WIDEVINE_CDM)
class HuhiWidevineBundleManager;
#endif

namespace huhi_component_updater {
#if BUILDFLAG(ENABLE_EXTENSIONS)
class ExtensionWhitelistService;
#endif
class LocalDataFilesService;
}  // namespace huhi_component_updater

namespace huhi_shields {
class AdBlockService;
class AdBlockCustomFiltersService;
class AdBlockRegionalServiceManager;
class HTTPSEverywhereService;
class TrackingProtectionService;
}  // namespace huhi_shields

namespace greaselion {
#if BUILDFLAG(ENABLE_GREASELION)
class GreaselionDownloadService;
#endif
}  // namespace greaselion

namespace ntp_background_images {
class NTPBackgroundImagesService;
}  // namespace ntp_background_images

namespace extensions {
class HuhiTorClientUpdater;
}

namespace ipfs {
class HuhiIpfsClientUpdater;
}

namespace speedreader {
class SpeedreaderRewriterService;
}

namespace huhi_user_model {
class UserModelFileService;
}

class HuhiBrowserProcessImpl : public BrowserProcessImpl {
 public:
  explicit HuhiBrowserProcessImpl(StartupData* startup_data);
  ~HuhiBrowserProcessImpl() override;

  // BrowserProcess implementation.

  ProfileManager* profile_manager() override;
  NotificationPlatformBridge* notification_platform_bridge() override;

  void StartHuhiServices();
  huhi_shields::AdBlockService* ad_block_service();
  huhi_shields::AdBlockCustomFiltersService* ad_block_custom_filters_service();
  huhi_shields::AdBlockRegionalServiceManager*
  ad_block_regional_service_manager();
#if BUILDFLAG(ENABLE_EXTENSIONS)
  huhi_component_updater::ExtensionWhitelistService*
  extension_whitelist_service();
#endif
#if BUILDFLAG(ENABLE_GREASELION)
  greaselion::GreaselionDownloadService* greaselion_download_service();
#endif
  huhi_shields::TrackingProtectionService* tracking_protection_service();
  huhi_shields::HTTPSEverywhereService* https_everywhere_service();
  huhi_component_updater::LocalDataFilesService* local_data_files_service();
#if BUILDFLAG(ENABLE_TOR)
  extensions::HuhiTorClientUpdater* tor_client_updater();
#endif
#if BUILDFLAG(IPFS_ENABLED)
  ipfs::HuhiIpfsClientUpdater* ipfs_client_updater();
#endif
  huhi::HuhiP3AService* huhi_p3a_service();
#if BUILDFLAG(BUNDLE_WIDEVINE_CDM)
  HuhiWidevineBundleManager* huhi_widevine_bundle_manager();
#endif
  huhi::HuhiStatsUpdater* huhi_stats_updater();
  ntp_background_images::NTPBackgroundImagesService*
  ntp_background_images_service();
#if BUILDFLAG(ENABLE_SPEEDREADER)
  speedreader::SpeedreaderRewriterService* speedreader_rewriter_service();
#endif
#if BUILDFLAG(HUHI_ADS_ENABLED)
  huhi_user_model::UserModelFileService* user_model_file_service();
#endif

 private:
  // BrowserProcessImpl overrides:
  void Init() override;

  void CreateProfileManager();
  void CreateNotificationPlatformBridge();

#if BUILDFLAG(ENABLE_TOR)
  void OnTorEnabledChanged();
#endif

  void UpdateHuhiDarkMode();
  void OnHuhiDarkModeChanged();

  huhi_component_updater::HuhiComponent::Delegate*
  huhi_component_updater_delegate();

  // local_data_files_service_ should always be first because it needs
  // to be destroyed last
  std::unique_ptr<huhi_component_updater::LocalDataFilesService>
      local_data_files_service_;
  std::unique_ptr<huhi_component_updater::HuhiComponent::Delegate>
      huhi_component_updater_delegate_;
  std::unique_ptr<huhi_shields::AdBlockService> ad_block_service_;
#if BUILDFLAG(ENABLE_EXTENSIONS)
  std::unique_ptr<huhi_component_updater::ExtensionWhitelistService>
      extension_whitelist_service_;
#endif
#if BUILDFLAG(ENABLE_GREASELION)
  std::unique_ptr<greaselion::GreaselionDownloadService>
      greaselion_download_service_;
#endif
  std::unique_ptr<huhi_shields::TrackingProtectionService>
      tracking_protection_service_;
  std::unique_ptr<huhi_shields::HTTPSEverywhereService>
      https_everywhere_service_;
  std::unique_ptr<huhi::HuhiStatsUpdater> huhi_stats_updater_;
#if BUILDFLAG(ENABLE_HUHI_REFERRALS)
  std::unique_ptr<huhi::HuhiReferralsService> huhi_referrals_service_;
#endif
#if BUILDFLAG(ENABLE_TOR)
  std::unique_ptr<extensions::HuhiTorClientUpdater> tor_client_updater_;
#endif
#if BUILDFLAG(IPFS_ENABLED)
  std::unique_ptr<ipfs::HuhiIpfsClientUpdater> ipfs_client_updater_;
#endif
#if BUILDFLAG(BUNDLE_WIDEVINE_CDM)
  std::unique_ptr<HuhiWidevineBundleManager> huhi_widevine_bundle_manager_;
#endif
  scoped_refptr<huhi::HuhiP3AService> huhi_p3a_service_;
  std::unique_ptr<ntp_background_images::NTPBackgroundImagesService>
      ntp_background_images_service_;

#if BUILDFLAG(ENABLE_SPEEDREADER)
  std::unique_ptr<speedreader::SpeedreaderRewriterService>
      speedreader_rewriter_service_;
#endif

#if BUILDFLAG(HUHI_ADS_ENABLED)
  std::unique_ptr<huhi_user_model::UserModelFileService>
      user_model_file_service_;
#endif

  SEQUENCE_CHECKER(sequence_checker_);

  DISALLOW_COPY_AND_ASSIGN(HuhiBrowserProcessImpl);
};

extern HuhiBrowserProcessImpl* g_huhi_browser_process;

#endif  // HUHI_BROWSER_HUHI_BROWSER_PROCESS_IMPL_H_
