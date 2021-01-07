/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/huhi_tab_helpers.h"

#include "base/command_line.h"
#include "base/feature_list.h"
#include "huhi/browser/huhi_stats/huhi_stats_tab_helper.h"
#include "huhi/browser/ephemeral_storage/ephemeral_storage_tab_helper.h"
#include "huhi/browser/farbling/farbling_tab_helper.h"
#include "huhi/browser/profiles/profile_util.h"
#include "huhi/browser/ui/bookmark/huhi_bookmark_tab_helper.h"
#include "huhi/components/huhi_ads/browser/ads_tab_helper.h"
#include "huhi/components/huhi_perf_predictor/browser/buildflags.h"
#include "huhi/components/huhi_rewards/browser/buildflags/buildflags.h"
#include "huhi/components/huhi_shields/browser/huhi_shields_web_contents_observer.h"
#include "huhi/components/huhi_shields/browser/buildflags/buildflags.h"  // For STP
#include "huhi/components/huhi_wayback_machine/buildflags.h"
#include "huhi/components/greaselion/browser/buildflags/buildflags.h"
#include "huhi/components/ipfs/buildflags/buildflags.h"
#include "huhi/components/speedreader/buildflags.h"
#include "huhi/components/tor/buildflags/buildflags.h"
#include "content/public/browser/web_contents.h"
#include "third_party/blink/public/common/features.h"
#include "third_party/widevine/cdm/buildflags.h"

#if BUILDFLAG(ENABLE_GREASELION)
#include "huhi/browser/greaselion/greaselion_tab_helper.h"
#endif

#if defined(OS_ANDROID)
#include "huhi/browser/android/huhi_cosmetic_resources_tab_helper.h"
#include "huhi/browser/android/preferences/background_video_playback_tab_helper.h"
#include "huhi/browser/android/preferences/website/desktop_mode_tab_helper.h"
#endif

#if BUILDFLAG(HUHI_REWARDS_ENABLED)
#include "huhi/browser/huhi_rewards/rewards_tab_helper.h"
#endif

#if BUILDFLAG(HUHI_STP_ENABLED)
#include "huhi/components/huhi_shields/browser/tracking_protection_helper.h"
#include "huhi/components/huhi_shields/browser/tracking_protection_service.h"
#endif

#if BUILDFLAG(ENABLE_WIDEVINE)
#include "huhi/browser/huhi_drm_tab_helper.h"
#endif

#if BUILDFLAG(ENABLE_HUHI_WAYBACK_MACHINE)
#include "huhi/browser/infobars/huhi_wayback_machine_delegate_impl.h"
#endif

#if BUILDFLAG(ENABLE_HUHI_PERF_PREDICTOR)
#include "huhi/components/huhi_perf_predictor/browser/perf_predictor_tab_helper.h"
#endif

#if BUILDFLAG(ENABLE_SPEEDREADER)
#include "huhi/browser/speedreader/speedreader_tab_helper.h"
#endif

#if BUILDFLAG(ENABLE_TOR)
#include "huhi/components/tor/onion_location_tab_helper.h"
#include "huhi/components/tor/tor_tab_helper.h"
#endif

#if BUILDFLAG(IPFS_ENABLED)
#include "huhi/browser/infobars/ipfs_infobar_delegate.h"
#include "huhi/browser/ipfs/ipfs_service_factory.h"
#include "huhi/browser/ipfs/ipfs_tab_helper.h"
#endif

namespace huhi {

void AttachTabHelpers(content::WebContents* web_contents) {
#if BUILDFLAG(ENABLE_GREASELION)
  greaselion::GreaselionTabHelper::CreateForWebContents(web_contents);
#endif
  huhi_shields::HuhiShieldsWebContentsObserver::CreateForWebContents(
      web_contents);

#if defined(OS_ANDROID)
  DesktopModeTabHelper::CreateForWebContents(web_contents);
  BackgroundVideoPlaybackTabHelper::CreateForWebContents(web_contents);
  HuhiCosmeticResourcesTabHelper::CreateForWebContents(web_contents);
#else
  // Add tab helpers here unless they are intended for android too
  HuhiBookmarkTabHelper::CreateForWebContents(web_contents);
#endif

#if BUILDFLAG(HUHI_REWARDS_ENABLED)
  huhi_rewards::RewardsTabHelper::CreateForWebContents(web_contents);
#endif

#if BUILDFLAG(HUHI_STP_ENABLED)
  if (huhi_shields::TrackingProtectionService::
          IsSmartTrackingProtectionEnabled()) {
    huhi_shields::TrackingProtectionHelper::CreateForWebContents(web_contents);
  }
#endif

#if BUILDFLAG(ENABLE_WIDEVINE)
  HuhiDrmTabHelper::CreateForWebContents(web_contents);
#endif

#if BUILDFLAG(ENABLE_HUHI_WAYBACK_MACHINE)
  HuhiWaybackMachineDelegateImpl::AttachTabHelperIfNeeded(web_contents);
#endif

#if BUILDFLAG(ENABLE_HUHI_PERF_PREDICTOR)
  huhi_perf_predictor::PerfPredictorTabHelper::CreateForWebContents(
      web_contents);
#endif

  huhi_ads::AdsTabHelper::CreateForWebContents(web_contents);

#if BUILDFLAG(ENABLE_SPEEDREADER)
  speedreader::SpeedreaderTabHelper::CreateForWebContents(web_contents);
#endif

#if BUILDFLAG(ENABLE_TOR)
  tor::TorTabHelper::MaybeCreateForWebContents(
      web_contents, huhi::IsTorProfile(web_contents->GetBrowserContext()));
  tor::OnionLocationTabHelper::CreateForWebContents(web_contents);
#endif

#if BUILDFLAG(IPFS_ENABLED)
  ipfs::IPFSTabHelper::MaybeCreateForWebContents(web_contents);
#endif

  FarblingTabHelper::CreateForWebContents(web_contents);

  huhi_stats::HuhiStatsTabHelper::CreateForWebContents(web_contents);

  if (base::FeatureList::IsEnabled(blink::features::kHuhiEphemeralStorage)) {
    ephemeral_storage::EphemeralStorageTabHelper::CreateForWebContents(
        web_contents);
  }
}

}  // namespace huhi
