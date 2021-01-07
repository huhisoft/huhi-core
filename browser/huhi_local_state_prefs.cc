/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/huhi_local_state_prefs.h"

#include "base/values.h"
#include "huhi/browser/huhi_stats/huhi_stats_updater.h"
#include "huhi/browser/metrics/metrics_reporting_util.h"
#include "huhi/browser/themes/huhi_dark_mode_utils.h"
#include "huhi/common/pref_names.h"
#include "huhi/components/huhi_referrals/buildflags/buildflags.h"
#include "huhi/components/huhi_shields/browser/ad_block_service.h"
#include "huhi/components/huhi_shields/browser/huhi_shields_p3a.h"
#include "huhi/components/ipfs/buildflags/buildflags.h"
#include "huhi/components/ntp_background_images/browser/ntp_background_images_service.h"
#include "huhi/components/ntp_background_images/browser/view_counter_service.h"
#include "huhi/components/p3a/huhi_p3a_service.h"
#include "huhi/components/p3a/buildflags.h"
#include "huhi/components/tor/buildflags/buildflags.h"
#include "chrome/browser/first_run/first_run.h"
#include "chrome/common/pref_names.h"
#include "components/metrics/metrics_pref_names.h"
#include "components/prefs/pref_registry_simple.h"
#include "third_party/widevine/cdm/buildflags.h"

#if BUILDFLAG(ENABLE_HUHI_REFERRALS)
#include "huhi/components/huhi_referrals/browser/huhi_referrals_service.h"
#endif

#if BUILDFLAG(ENABLE_TOR)
#include "huhi/components/tor/tor_profile_service.h"
#endif

#if BUILDFLAG(IPFS_ENABLED)
#include "huhi/components/ipfs/ipfs_service.h"
#endif

#if !defined(OS_ANDROID)
#include "huhi/browser/p3a/p3a_core_metrics.h"
#include "huhi/browser/ui/webui/new_tab_page/huhi_new_tab_message_handler.h"
#endif  // !defined(OS_ANDROID)

#if BUILDFLAG(ENABLE_WIDEVINE)
#include "huhi/browser/widevine/widevine_utils.h"
#endif

namespace huhi {

void RegisterLocalStatePrefs(PrefRegistrySimple* registry) {
  huhi_shields::RegisterPrefsForAdBlockService(registry);
  huhi_stats::RegisterLocalStatePrefs(registry);
  ntp_background_images::NTPBackgroundImagesService::RegisterLocalStatePrefs(
      registry);
  ntp_background_images::ViewCounterService::RegisterLocalStatePrefs(registry);
#if BUILDFLAG(ENABLE_HUHI_REFERRALS)
  RegisterPrefsForHuhiReferralsService(registry);
#endif
#if defined(OS_MAC)
  // Turn off super annoying 'Hold to quit'
  registry->SetDefaultPrefValue(prefs::kConfirmToQuitEnabled,
      base::Value(false));
#endif
#if BUILDFLAG(ENABLE_TOR)
  tor::TorProfileService::RegisterLocalStatePrefs(registry);
#endif
  registry->SetDefaultPrefValue(
      metrics::prefs::kMetricsReportingEnabled,
      base::Value(GetDefaultPrefValueForMetricsReporting()));
#if BUILDFLAG(IPFS_ENABLED)
  ipfs::IpfsService::RegisterLocalStatePrefs(registry);
#endif

#if BUILDFLAG(HUHI_P3A_ENABLED)
  huhi::HuhiP3AService::RegisterPrefs(registry,
                                        first_run::IsChromeFirstRun());
#endif  // BUILDFLAG(HUHI_P3A_ENABLED)

  huhi_shields::RegisterShieldsP3APrefs(registry);
#if !defined(OS_ANDROID)
  HuhiNewTabMessageHandler::RegisterLocalStatePrefs(registry);
  HuhiWindowTracker::RegisterPrefs(registry);
  HuhiUptimeTracker::RegisterPrefs(registry);
  dark_mode::RegisterHuhiDarkModeLocalStatePrefs(registry);
#endif

#if BUILDFLAG(ENABLE_WIDEVINE)
  RegisterWidevineLocalstatePrefs(registry);
#endif
}

}  // namespace huhi
