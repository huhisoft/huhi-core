/* Copyright (c) 2020 The Huhi Software Authors
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/ui/webui/huhi_settings_ui.h"

#include <string>

#include "huhi/browser/huhi_browser_process_impl.h"
#include "huhi/browser/extensions/huhi_component_loader.h"
#include "huhi/browser/ntp_background_images/view_counter_service_factory.h"
#include "huhi/browser/resources/settings/grit/huhi_settings_resources.h"
#include "huhi/browser/resources/settings/grit/huhi_settings_resources_map.h"
#include "huhi/browser/sparkle_buildflags.h"
#include "huhi/browser/ui/webui/navigation_bar_data_provider.h"
#include "huhi/browser/ui/webui/settings/huhi_appearance_handler.h"
#include "huhi/browser/ui/webui/settings/huhi_default_extensions_handler.h"
#include "huhi/browser/ui/webui/settings/huhi_privacy_handler.h"
#include "huhi/browser/ui/webui/settings/huhi_sync_handler.h"
#include "huhi/browser/ui/webui/settings/default_huhi_shields_handler.h"
#include "huhi/browser/version_info.h"
#include "huhi/components/huhi_sync/buildflags/buildflags.h"
#include "huhi/components/ntp_background_images/browser/view_counter_service.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/webui/settings/metrics_reporting_handler.h"
#include "content/public/browser/web_ui_data_source.h"

#if BUILDFLAG(ENABLE_HUHI_SYNC)
#include "components/sync/driver/sync_driver_switches.h"
#endif

#if BUILDFLAG(ENABLE_SPARKLE)
#include "huhi/browser/ui/webui/settings/huhi_relaunch_handler_mac.h"
#endif

using ntp_background_images::ViewCounterServiceFactory;

HuhiSettingsUI::HuhiSettingsUI(content::WebUI* web_ui,
                                 const std::string& host)
    : SettingsUI(web_ui) {
  web_ui->AddMessageHandler(
    std::make_unique<settings::MetricsReportingHandler>());
  web_ui->AddMessageHandler(std::make_unique<HuhiPrivacyHandler>());
  web_ui->AddMessageHandler(std::make_unique<DefaultHuhiShieldsHandler>());
  web_ui->AddMessageHandler(std::make_unique<HuhiDefaultExtensionsHandler>());
  web_ui->AddMessageHandler(std::make_unique<HuhiAppearanceHandler>());
  web_ui->AddMessageHandler(std::make_unique<HuhiSyncHandler>());
#if BUILDFLAG(ENABLE_SPARKLE)
  // Use sparkle's relaunch api for browser relaunch on update.
  web_ui->AddMessageHandler(std::make_unique<HuhiRelaunchHandler>());
#endif
}

HuhiSettingsUI::~HuhiSettingsUI() {
}

// static
void HuhiSettingsUI::AddResources(content::WebUIDataSource* html_source,
                                   Profile* profile) {
  constexpr char generated_prefix[] =
      "@out_folder@/gen/huhi/browser/resources/settings/";
  const auto generated_prefix_len = strlen(generated_prefix);
  for (size_t i = 0; i < kHuhiSettingsResourcesSize; ++i) {
    // Rewrite path for any generated entries
    std::string path(kHuhiSettingsResources[i].name);
    size_t pos = path.find(generated_prefix);
    if (pos != std::string::npos) {
      path.erase(pos, generated_prefix_len);
    }
    html_source->AddResourcePath(path, kHuhiSettingsResources[i].value);
  }

#if BUILDFLAG(ENABLE_HUHI_SYNC)
  html_source->AddBoolean("isSyncDisabled",
                          !switches::IsSyncAllowedByFlag());
#else
  html_source->AddBoolean("isSyncDisabled", true);
#endif
  html_source->AddString("huhiProductVersion",
    version_info::GetHuhiVersionWithoutChromiumMajorVersion());
  NavigationBarDataProvider::Initialize(html_source);
  if (auto* service = ViewCounterServiceFactory::GetForProfile(profile))
    service->InitializeWebUIDataSource(html_source);
}
