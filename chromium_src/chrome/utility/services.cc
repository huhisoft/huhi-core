/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "build/build_config.h"
#include "huhi/components/huhi_ads/browser/buildflags/buildflags.h"
#include "huhi/components/huhi_rewards/browser/buildflags/buildflags.h"
#include "huhi/components/ipfs/buildflags/buildflags.h"
#include "huhi/components/tor/buildflags/buildflags.h"

#if !defined(OS_ANDROID)
#include "huhi/utility/importer/huhi_profile_import_impl.h"
#endif

#if BUILDFLAG(IPFS_ENABLED)
#include "huhi/components/services/ipfs/ipfs_service_impl.h"
#include "huhi/components/services/ipfs/public/mojom/ipfs_service.mojom.h"
#endif

#if BUILDFLAG(ENABLE_TOR)
#include "huhi/components/services/tor/public/interfaces/tor.mojom.h"
#include "huhi/components/services/tor/tor_launcher_impl.h"
#endif

#if BUILDFLAG(HUHI_REWARDS_ENABLED)
#include "huhi/components/services/bat_ledger/bat_ledger_service_impl.h"
#include "huhi/components/services/bat_ledger/public/interfaces/bat_ledger.mojom.h"
#endif

#if BUILDFLAG(HUHI_ADS_ENABLED)
#include "huhi/components/services/bat_ads/bat_ads_service_impl.h"
#include "huhi/components/services/bat_ads/public/interfaces/bat_ads.mojom.h"
#endif

namespace {

#if !defined(OS_ANDROID)
auto RunHuhiProfileImporter(
    mojo::PendingReceiver<huhi::mojom::ProfileImport> receiver) {
  return std::make_unique<HuhiProfileImportImpl>(std::move(receiver));
}
#endif

#if BUILDFLAG(IPFS_ENABLED)
auto RunIpfsService(mojo::PendingReceiver<ipfs::mojom::IpfsService> receiver) {
  return std::make_unique<ipfs::IpfsServiceImpl>(std::move(receiver));
}
#endif

#if BUILDFLAG(ENABLE_TOR)
auto RunTorLauncher(mojo::PendingReceiver<tor::mojom::TorLauncher> receiver) {
  return std::make_unique<tor::TorLauncherImpl>(std::move(receiver));
}
#endif

#if BUILDFLAG(HUHI_REWARDS_ENABLED)
auto RunBatLedgerService(
    mojo::PendingReceiver<bat_ledger::mojom::BatLedgerService> receiver) {
  return std::make_unique<bat_ledger::BatLedgerServiceImpl>(
      std::move(receiver));
}
#endif

#if BUILDFLAG(HUHI_ADS_ENABLED)
auto RunBatAdsService(
    mojo::PendingReceiver<bat_ads::mojom::BatAdsService> receiver) {
  return std::make_unique<bat_ads::BatAdsServiceImpl>(
      std::move(receiver));
}
#endif

}  // namespace

#if defined(OS_ANDROID)
#define HUHI_PROFILE_IMPORTER
#else
#define HUHI_PROFILE_IMPORTER \
    RunHuhiProfileImporter,
#endif

#if BUILDFLAG(IPFS_ENABLED)
#define HUHI_IPFS_SERVICE \
  RunIpfsService,
#else
#define HUHI_IPFS_SERVICE
#endif

#if BUILDFLAG(ENABLE_TOR)
#define HUHI_TOR_LAUNCHER \
  RunTorLauncher,
#else
#define HUHI_TOR_LAUNCHER
#endif

#if BUILDFLAG(HUHI_REWARDS_ENABLED)
#define HUHI_BAT_LEDGER_SERVICE \
  RunBatLedgerService,
#else
#define HUHI_BAT_LEDGER_SERVICE
#endif

#if BUILDFLAG(HUHI_ADS_ENABLED)
#define HUHI_BAT_ADS_SERVICE \
  RunBatAdsService,
#else
#define HUHI_BAT_ADS_SERVICE
#endif

#define HUHI_GET_MAIN_THREAD_SERVICE_FACTORY \
    HUHI_PROFILE_IMPORTER \
    HUHI_IPFS_SERVICE \
    HUHI_TOR_LAUNCHER \
    HUHI_BAT_LEDGER_SERVICE \
    HUHI_BAT_ADS_SERVICE

#include "../../../../chrome/utility/services.cc"

#undef HUHI_GET_MAIN_THREAD_SERVICE_FACTORY
#undef HUHI_PROFILE_IMPORTER
#undef HUHI_IPFS_SERVICE
#undef HUHI_TOR_LAUNCHER
#undef HUHI_BAT_LEDGER_SERVICE
#undef HUHI_BAT_ADS_SERVICE
