/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/ui/webui/huhi_adblock_ui.h"

#include "huhi/browser/huhi_browser_process_impl.h"
#include "huhi/common/pref_names.h"
#include "huhi/common/webui_url_constants.h"
#include "huhi/components/huhi_adblock/resources/grit/huhi_adblock_generated_map.h"
#include "huhi/components/huhi_shields/browser/ad_block_custom_filters_service.h"
#include "huhi/components/huhi_shields/browser/ad_block_regional_service_manager.h"
#include "chrome/browser/profiles/profile.h"
#include "components/grit/huhi_components_resources.h"
#include "components/prefs/pref_change_registrar.h"
#include "components/prefs/pref_service.h"
#include "content/public/browser/render_frame_host.h"
#include "content/public/browser/render_view_host.h"
#include "content/public/browser/web_ui_data_source.h"
#include "content/public/browser/web_ui_message_handler.h"

namespace {

class AdblockDOMHandler : public content::WebUIMessageHandler {
 public:
  AdblockDOMHandler();
  ~AdblockDOMHandler() override;

  // WebUIMessageHandler implementation.
  void RegisterMessages() override;

 private:
  void HandleEnableFilterList(const base::ListValue* args);
  void HandleGetCustomFilters(const base::ListValue* args);
  void HandleGetRegionalLists(const base::ListValue* args);
  void HandleUpdateCustomFilters(const base::ListValue* args);

  DISALLOW_COPY_AND_ASSIGN(AdblockDOMHandler);
};

AdblockDOMHandler::AdblockDOMHandler() {}

AdblockDOMHandler::~AdblockDOMHandler() {}

void AdblockDOMHandler::RegisterMessages() {
  web_ui()->RegisterMessageCallback(
      "huhi_adblock.enableFilterList",
      base::BindRepeating(&AdblockDOMHandler::HandleEnableFilterList,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "huhi_adblock.getCustomFilters",
      base::BindRepeating(&AdblockDOMHandler::HandleGetCustomFilters,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "huhi_adblock.getRegionalLists",
      base::BindRepeating(&AdblockDOMHandler::HandleGetRegionalLists,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "huhi_adblock.updateCustomFilters",
      base::BindRepeating(&AdblockDOMHandler::HandleUpdateCustomFilters,
                          base::Unretained(this)));
}

void AdblockDOMHandler::HandleEnableFilterList(const base::ListValue* args) {
  DCHECK_EQ(args->GetSize(), 2U);
  std::string uuid;
  if (!args->GetString(0, &uuid))
    return;
  bool enabled;
  if (!args->GetBoolean(1, &enabled))
    return;
  g_huhi_browser_process->ad_block_regional_service_manager()
      ->EnableFilterList(uuid, enabled);
}

void AdblockDOMHandler::HandleGetCustomFilters(const base::ListValue* args) {
  DCHECK_EQ(args->GetSize(), 0U);
  const std::string custom_filters =
      g_huhi_browser_process->ad_block_custom_filters_service()
          ->GetCustomFilters();
  if (!web_ui()->CanCallJavascript())
    return;
  web_ui()->CallJavascriptFunctionUnsafe("huhi_adblock.onGetCustomFilters",
                                         base::Value(custom_filters));
}

void AdblockDOMHandler::HandleGetRegionalLists(const base::ListValue* args) {
  DCHECK_EQ(args->GetSize(), 0U);
  if (!web_ui()->CanCallJavascript())
    return;
  std::unique_ptr<base::ListValue> regional_lists =
      g_huhi_browser_process->ad_block_regional_service_manager()
          ->GetRegionalLists();
  web_ui()->CallJavascriptFunctionUnsafe("huhi_adblock.onGetRegionalLists",
                                         *regional_lists);
}

void AdblockDOMHandler::HandleUpdateCustomFilters(const base::ListValue* args) {
  DCHECK_EQ(args->GetSize(), 1U);
  std::string custom_filters;
  if (!args->GetString(0, &custom_filters))
    return;

  g_huhi_browser_process->ad_block_custom_filters_service()
      ->UpdateCustomFilters(custom_filters);
}

}  // namespace

HuhiAdblockUI::HuhiAdblockUI(content::WebUI* web_ui, const std::string& name)
    : BasicUI(web_ui, name, kHuhiAdblockGenerated,
        kHuhiAdblockGeneratedSize, IDR_HUHI_ADBLOCK_HTML) {
  Profile* profile = Profile::FromWebUI(web_ui);
  PrefService* prefs = profile->GetPrefs();
  pref_change_registrar_ = std::make_unique<PrefChangeRegistrar>();
  pref_change_registrar_->Init(prefs);
  pref_change_registrar_->Add(kAdsBlocked,
    base::Bind(&HuhiAdblockUI::OnPreferenceChanged, base::Unretained(this)));
  web_ui->AddMessageHandler(std::make_unique<AdblockDOMHandler>());
}

HuhiAdblockUI::~HuhiAdblockUI() {
}

void HuhiAdblockUI::CustomizeWebUIProperties(
    content::RenderFrameHost* render_frame_host) {
  DCHECK(IsSafeToSetWebUIProperties());
  Profile* profile = Profile::FromWebUI(web_ui());
  PrefService* prefs = profile->GetPrefs();
  if (render_frame_host) {
    render_frame_host->SetWebUIProperty(
        "adsBlockedStat", std::to_string(prefs->GetUint64(kAdsBlocked) +
            prefs->GetUint64(kTrackersBlocked)));
  }
}

void HuhiAdblockUI::UpdateWebUIProperties() {
  if (IsSafeToSetWebUIProperties()) {
    CustomizeWebUIProperties(GetRenderFrameHost());
    web_ui()->CallJavascriptFunctionUnsafe("huhi_adblock.statsUpdated");
  }
}

void HuhiAdblockUI::OnPreferenceChanged() {
  UpdateWebUIProperties();
}
