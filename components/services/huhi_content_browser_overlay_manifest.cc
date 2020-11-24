/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/components/services/huhi_content_browser_overlay_manifest.h"

#include "base/no_destructor.h"
#include "huhi/browser/tor/buildflags.h"
#include "huhi/components/huhi_ads/browser/buildflags/buildflags.h"
#include "huhi/components/huhi_rewards/browser/buildflags/buildflags.h"
#include "services/service_manager/public/cpp/manifest_builder.h"

#if BUILDFLAG(HUHI_REWARDS_ENABLED)
#include "huhi/components/services/bat_ledger/public/cpp/manifest.h"
#endif

#if BUILDFLAG(HUHI_ADS_ENABLED)
#include "huhi/components/services/bat_ads/public/cpp/manifest.h"
#endif

#if BUILDFLAG(ENABLE_TOR)
#include "huhi/components/services/tor/public/cpp/manifest.h"
#endif

const service_manager::Manifest& GetHuhiContentBrowserOverlayManifest() {
  static base::NoDestructor<service_manager::Manifest> manifest{
      service_manager::ManifestBuilder()
          .WithServiceName("content_browser")
          .WithDisplayName("Huhi")
#if BUILDFLAG(HUHI_REWARDS_ENABLED)
          .RequireCapability("bat_ledger", "bat_ledger")
#if BUILDFLAG(HUHI_ADS_ENABLED)
          .RequireCapability("bat_ads", "bat_ads")
#endif
#endif
#if BUILDFLAG(ENABLE_TOR)
          .RequireCapability("tor_launcher", "tor_launcher")
#endif
          .Build()};
  return *manifest;
}
