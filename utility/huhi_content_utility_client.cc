/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/utility/huhi_content_utility_client.h"

#include <memory>
#include <string>
#include <utility>

#include "huhi/browser/tor/buildflags.h"
#include "huhi/components/huhi_ads/browser/buildflags/buildflags.h"
#include "huhi/components/huhi_rewards/browser/buildflags/buildflags.h"
#include "content/public/utility/utility_thread.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"

#if BUILDFLAG(HUHI_ADS_ENABLED)
#include "huhi/components/services/bat_ads/bat_ads_app.h"
#include "huhi/components/services/bat_ads/public/interfaces/bat_ads.mojom.h"
#endif

#if BUILDFLAG(HUHI_REWARDS_ENABLED)
#include "huhi/components/services/bat_ledger/bat_ledger_app.h"
#include "huhi/components/services/bat_ledger/public/interfaces/bat_ledger.mojom.h"
#endif

#if BUILDFLAG(ENABLE_TOR)
#include "huhi/components/services/tor/public/interfaces/tor.mojom.h"
#include "huhi/components/services/tor/tor_launcher_service.h"
#endif

HuhiContentUtilityClient::HuhiContentUtilityClient()
    : ChromeContentUtilityClient() {}

HuhiContentUtilityClient::~HuhiContentUtilityClient() = default;

namespace {

#if BUILDFLAG(HUHI_ADS_ENABLED) || BUILDFLAG(HUHI_REWARDS_ENABLED) || \
    BUILDFLAG(ENABLE_TOR)
void RunServiceAsyncThenTerminateProcess(
    std::unique_ptr<service_manager::Service> service) {
  service_manager::Service::RunAsyncUntilTermination(
      std::move(service),
      base::BindOnce([] { content::UtilityThread::Get()->ReleaseProcess(); }));
}
#endif

#if BUILDFLAG(ENABLE_TOR)
std::unique_ptr<service_manager::Service> CreateTorLauncherService(
    mojo::PendingReceiver<service_manager::mojom::Service> receiver) {
  return std::make_unique<tor::TorLauncherService>(
      std::move(receiver));
}
#endif

#if BUILDFLAG(HUHI_ADS_ENABLED)
std::unique_ptr<service_manager::Service> CreateBatAdsService(
    mojo::PendingReceiver<service_manager::mojom::Service> receiver) {
  return std::make_unique<bat_ads::BatAdsApp>(
      std::move(receiver));
}
#endif

#if BUILDFLAG(HUHI_REWARDS_ENABLED)
std::unique_ptr<service_manager::Service> CreateBatLedgerService(
    mojo::PendingReceiver<service_manager::mojom::Service> receiver) {
  return std::make_unique<bat_ledger::BatLedgerApp>(
      std::move(receiver));
}
#endif

}  // namespace

bool HuhiContentUtilityClient::HandleServiceRequest(
    const std::string& service_name,
    mojo::PendingReceiver<service_manager::mojom::Service> receiver) {

#if BUILDFLAG(ENABLE_TOR)
  if (service_name == tor::mojom::kServiceName) {
    RunServiceAsyncThenTerminateProcess(
        CreateTorLauncherService(std::move(receiver)));
    return true;
  }
#endif

#if BUILDFLAG(HUHI_ADS_ENABLED)
  if (service_name == bat_ads::mojom::kServiceName) {
    RunServiceAsyncThenTerminateProcess(
        CreateBatAdsService(std::move(receiver)));
    return true;
  }
#endif

#if BUILDFLAG(HUHI_REWARDS_ENABLED)
  if (service_name == bat_ledger::mojom::kServiceName) {
    RunServiceAsyncThenTerminateProcess(
        CreateBatLedgerService(std::move(receiver)));
    return true;
  }
#endif

  return ChromeContentUtilityClient::HandleServiceRequest(
      service_name, std::move(receiver));
}
