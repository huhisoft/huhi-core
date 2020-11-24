/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/browser_context_keyed_service_factories.h"

#include "huhi/browser/huhi_shields/ad_block_pref_service_factory.h"
#include "huhi/browser/huhi_shields/cookie_pref_service_factory.h"
#include "huhi/browser/search_engines/search_engine_provider_service_factory.h"
#include "huhi/browser/search_engines/search_engine_tracker.h"
#include "huhi/browser/tor/tor_profile_service_factory.h"
#include "huhi/components/huhi_ads/browser/ads_service_factory.h"
#include "huhi/components/ipfs/browser/buildflags/buildflags.h"
#include "huhi/browser/huhi_rewards/rewards_service_factory.h"
#include "huhi/components/greaselion/browser/buildflags/buildflags.h"
#include "huhi/browser/ntp_background_images/view_counter_service_factory.h"
#include "huhi/components/huhi_wallet/browser/buildflags/buildflags.h"

#if BUILDFLAG(ENABLE_GREASELION)
#include "huhi/browser/greaselion/greaselion_service_factory.h"
#endif

#if !defined(OS_ANDROID)
#include "huhi/browser/ui/bookmark/bookmark_prefs_service_factory.h"
#else
#include "huhi/browser/ntp_background_images/android/ntp_background_images_bridge.h"
#endif

#if BUILDFLAG(HUHI_WALLET_ENABLED)
#include "huhi/browser/huhi_wallet/huhi_wallet_service_factory.h"
#endif

#if BUILDFLAG(IPFS_ENABLED)
#include "huhi/browser/ipfs/ipfs_service_factory.h"
#endif

namespace huhi {

void EnsureBrowserContextKeyedServiceFactoriesBuilt() {
  huhi_ads::AdsServiceFactory::GetInstance();
  huhi_rewards::RewardsServiceFactory::GetInstance();
  huhi_shields::AdBlockPrefServiceFactory::GetInstance();
  huhi_shields::CookiePrefServiceFactory::GetInstance();
#if BUILDFLAG(ENABLE_GREASELION)
  greaselion::GreaselionServiceFactory::GetInstance();
#endif
  TorProfileServiceFactory::GetInstance();
  SearchEngineProviderServiceFactory::GetInstance();
  SearchEngineTrackerFactory::GetInstance();
  ntp_background_images::ViewCounterServiceFactory::GetInstance();

#if !defined(OS_ANDROID)
  BookmarkPrefsServiceFactory::GetInstance();
#else
  ntp_background_images::NTPBackgroundImagesBridgeFactory::GetInstance();
#endif

#if BUILDFLAG(HUHI_WALLET_ENABLED)
  HuhiWalletServiceFactory::GetInstance();
#endif

#if BUILDFLAG(IPFS_ENABLED)
  ipfs::IpfsServiceFactory::GetInstance();
#endif
}

}  // namespace huhi
