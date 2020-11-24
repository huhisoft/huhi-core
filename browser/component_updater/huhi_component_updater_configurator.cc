/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/component_updater/huhi_component_updater_configurator.h"

#include <stdint.h>

#include <memory>
#include <string>
#include <vector>

#include "base/command_line.h"
#include "base/strings/string_number_conversions.h"
#include "base/strings/sys_string_conversions.h"
#include "base/version.h"
#include "huhi/common/huhi_switches.h"
#include "build/build_config.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/net/system_network_context_manager.h"
#include "chrome/common/pref_names.h"
#include "components/component_updater/component_updater_command_line_config_policy.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/pref_service.h"
#include "components/services/patch/content/patch_service.h"
#include "components/services/unzip/content/unzip_service.h"
#include "components/update_client/activity_data_service.h"
#include "components/update_client/crx_downloader_factory.h"
#include "components/update_client/net/network_chromium.h"
#include "components/update_client/patch/patch_impl.h"
#include "components/update_client/protocol_handler.h"
#include "components/update_client/unzip/unzip_impl.h"
#include "components/update_client/unzipper.h"
#include "components/update_client/update_query_params.h"
#include "content/public/browser/browser_thread.h"
#include "services/network/public/cpp/shared_url_loader_factory.h"

#if defined(OS_WIN)
#include "base/win/win_util.h"
#include "chrome/installer/util/google_update_settings.h"
#endif

namespace component_updater {

// Allows the component updater to use non-encrypted communication with the
// update backend. The security of the update checks is enforced using
// a custom message signing protocol and it does not depend on using HTTPS.
HuhiConfigurator::HuhiConfigurator(
    const base::CommandLine* cmdline,
    PrefService* pref_service)
    : configurator_impl_(ComponentUpdaterCommandLineConfigPolicy(cmdline),
        false),
      pref_service_(pref_service) {
  DCHECK(pref_service_);
}

HuhiConfigurator::~HuhiConfigurator() {}

int HuhiConfigurator::InitialDelay() const {
  return configurator_impl_.InitialDelay();
}

int HuhiConfigurator::NextCheckDelay() const {
  auto* command = base::CommandLine::ForCurrentProcess();
  if (command->HasSwitch(switches::kComponentUpdateIntervalInSec)) {
    int interval = 0;
    if (base::StringToInt(command->GetSwitchValueASCII(
                              switches::kComponentUpdateIntervalInSec),
                          &interval)) {
      DCHECK_GE(interval, 1);
      return interval;
    }
  }
  return configurator_impl_.NextCheckDelay();
}

int HuhiConfigurator::OnDemandDelay() const {
  return configurator_impl_.OnDemandDelay();
}

int HuhiConfigurator::UpdateDelay() const {
  return configurator_impl_.UpdateDelay();
}

std::vector<GURL> HuhiConfigurator::UpdateUrl() const {
  return configurator_impl_.UpdateUrl();
}

std::vector<GURL> HuhiConfigurator::PingUrl() const {
  return configurator_impl_.PingUrl();
}

std::string HuhiConfigurator::GetProdId() const {
  return std::string();
}

base::Version HuhiConfigurator::GetBrowserVersion() const {
  return configurator_impl_.GetBrowserVersion();
}

std::string HuhiConfigurator::GetChannel() const {
  return std::string("stable");
}

std::string HuhiConfigurator::GetBrand() const {
  return std::string();
}

std::string HuhiConfigurator::GetLang() const {
  return std::string();
}

std::string HuhiConfigurator::GetOSLongName() const {
  return configurator_impl_.GetOSLongName();
}

base::flat_map<std::string, std::string>
HuhiConfigurator::ExtraRequestParams() const {
  return configurator_impl_.ExtraRequestParams();
}

std::string HuhiConfigurator::GetDownloadPreference() const {
  return std::string();
}

scoped_refptr<update_client::NetworkFetcherFactory>
HuhiConfigurator::GetNetworkFetcherFactory() {
  if (!network_fetcher_factory_) {
    network_fetcher_factory_ =
        base::MakeRefCounted<update_client::NetworkFetcherChromiumFactory>(
            g_browser_process->system_network_context_manager()
                ->GetSharedURLLoaderFactory(),
            // Never send cookies for component update downloads.
            base::BindRepeating([](const GURL& url) { return false; }));
  }
  return network_fetcher_factory_;
}

scoped_refptr<update_client::CrxDownloaderFactory>
HuhiConfigurator::GetCrxDownloaderFactory() {
  if (!crx_downloader_factory_) {
    crx_downloader_factory_ =
        update_client::MakeCrxDownloaderFactory(GetNetworkFetcherFactory());
  }
  return crx_downloader_factory_;
}

scoped_refptr<update_client::UnzipperFactory>
HuhiConfigurator::GetUnzipperFactory() {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
  if (!unzip_factory_) {
    unzip_factory_ = base::MakeRefCounted<update_client::UnzipChromiumFactory>(
        base::BindRepeating(&unzip::LaunchUnzipper));
  }
  return unzip_factory_;
}

scoped_refptr<update_client::PatcherFactory>
HuhiConfigurator::GetPatcherFactory() {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
  if (!patch_factory_) {
    patch_factory_ = base::MakeRefCounted<update_client::PatchChromiumFactory>(
        base::BindRepeating(&patch::LaunchFilePatcher));
  }
  return patch_factory_;
}

bool HuhiConfigurator::EnabledDeltas() const {
  return configurator_impl_.EnabledDeltas();
}

bool HuhiConfigurator::EnabledComponentUpdates() const {
  return pref_service_->GetBoolean(prefs::kComponentUpdatesEnabled);
}

bool HuhiConfigurator::EnabledBackgroundDownloader() const {
  return configurator_impl_.EnabledBackgroundDownloader();
}

bool HuhiConfigurator::EnabledCupSigning() const {
  return false;
}

PrefService* HuhiConfigurator::GetPrefService() const {
  return pref_service_;
}

update_client::ActivityDataService* HuhiConfigurator::GetActivityDataService()
    const {
  return nullptr;
}

bool HuhiConfigurator::IsPerUserInstall() const {
  return false;
}

std::unique_ptr<update_client::ProtocolHandlerFactory>
HuhiConfigurator::GetProtocolHandlerFactory() const {
  return configurator_impl_.GetProtocolHandlerFactory();
}

}  // namespace component_updater
