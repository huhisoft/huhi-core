/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/extensions/api/huhi_shields_api.h"

#include <utility>

#include "base/strings/string_number_conversions.h"
#include "huhi/browser/huhi_browser_process_impl.h"
#include "huhi/browser/extensions/api/huhi_action_api.h"
#include "huhi/browser/webcompat_reporter/webcompat_reporter_dialog.h"
#include "huhi/common/extensions/api/huhi_shields.h"
#include "huhi/components/huhi_shields/browser/ad_block_base_service.h"
#include "huhi/components/huhi_shields/browser/ad_block_custom_filters_service.h"
#include "huhi/components/huhi_shields/browser/ad_block_regional_service_manager.h"
#include "huhi/components/huhi_shields/browser/ad_block_service.h"
#include "huhi/components/huhi_shields/browser/ad_block_service_helper.h"
#include "huhi/components/huhi_shields/browser/huhi_shields_p3a.h"
#include "huhi/components/huhi_shields/browser/huhi_shields_util.h"
#include "huhi/components/huhi_shields/browser/huhi_shields_web_contents_observer.h"
#include "huhi/components/huhi_shields/common/huhi_shield_constants.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/extensions/api/tabs/tabs_constants.h"
#include "chrome/browser/extensions/chrome_extension_function_details.h"
#include "chrome/browser/extensions/extension_tab_util.h"
#include "chrome/browser/profiles/profile.h"
#include "content/public/browser/web_contents.h"
#include "extensions/browser/extension_util.h"
#include "extensions/common/constants.h"

using huhi_shields::HuhiShieldsWebContentsObserver;
using huhi_shields::ControlType;
using huhi_shields::ControlTypeFromString;
using huhi_shields::ControlTypeToString;

namespace extensions {
namespace api {

namespace {

const char kInvalidUrlError[] = "Invalid URL.";
const char kInvalidControlTypeError[] = "Invalid ControlType.";

}  // namespace


ExtensionFunction::ResponseAction
HuhiShieldsUrlCosmeticResourcesFunction::Run() {
  std::unique_ptr<huhi_shields::UrlCosmeticResources::Params> params(
      huhi_shields::UrlCosmeticResources::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());
  g_huhi_browser_process->ad_block_service()->GetTaskRunner()
      ->PostTaskAndReplyWithResult(
          FROM_HERE,
          base::BindOnce(&HuhiShieldsUrlCosmeticResourcesFunction::
                             GetUrlCosmeticResourcesOnTaskRunner,
                         this, params->url),
          base::BindOnce(&HuhiShieldsUrlCosmeticResourcesFunction::
                             GetUrlCosmeticResourcesOnUI,
                         this));
  return RespondLater();
}

std::unique_ptr<base::ListValue> HuhiShieldsUrlCosmeticResourcesFunction::
    GetUrlCosmeticResourcesOnTaskRunner(const std::string& url) {
  base::Optional<base::Value> resources = g_huhi_browser_process->
      ad_block_service()->UrlCosmeticResources(url);

  if (!resources || !resources->is_dict()) {
    return std::unique_ptr<base::ListValue>();
  }

  base::Optional<base::Value> regional_resources = g_huhi_browser_process->
      ad_block_regional_service_manager()->UrlCosmeticResources(url);

  if (regional_resources && regional_resources->is_dict()) {
    ::huhi_shields::MergeResourcesInto(
        std::move(*regional_resources), &*resources, /*force_hide=*/false);
  }

  base::Optional<base::Value> custom_resources = g_huhi_browser_process->
      ad_block_custom_filters_service()->UrlCosmeticResources(url);

  if (custom_resources && custom_resources->is_dict()) {
    ::huhi_shields::MergeResourcesInto(
        std::move(*custom_resources), &*resources, /*force_hide=*/true);
  }

  auto result_list = std::make_unique<base::ListValue>();
  result_list->Append(std::move(*resources));
  return result_list;
}

void HuhiShieldsUrlCosmeticResourcesFunction::GetUrlCosmeticResourcesOnUI(
    std::unique_ptr<base::ListValue> resources) {
  if (!resources) {
    Respond(Error("Url-specific cosmetic resources could not be returned"));
    return;
  }
  Respond(ArgumentList(std::move(resources)));
}

ExtensionFunction::ResponseAction
HuhiShieldsHiddenClassIdSelectorsFunction::Run() {
  std::unique_ptr<huhi_shields::HiddenClassIdSelectors::Params> params(
      huhi_shields::HiddenClassIdSelectors::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());
  g_huhi_browser_process->ad_block_service()->GetTaskRunner()
      ->PostTaskAndReplyWithResult(
          FROM_HERE,
          base::BindOnce(&HuhiShieldsHiddenClassIdSelectorsFunction::
                             GetHiddenClassIdSelectorsOnTaskRunner,
                         this, params->classes, params->ids,
                         params->exceptions),
          base::BindOnce(&HuhiShieldsHiddenClassIdSelectorsFunction::
                             GetHiddenClassIdSelectorsOnUI,
                         this));
  return RespondLater();
}

std::unique_ptr<base::ListValue> HuhiShieldsHiddenClassIdSelectorsFunction::
    GetHiddenClassIdSelectorsOnTaskRunner(
        const std::vector<std::string>& classes,
        const std::vector<std::string>& ids,
        const std::vector<std::string>& exceptions) {
  base::Optional<base::Value> hide_selectors = g_huhi_browser_process->
      ad_block_service()->HiddenClassIdSelectors(classes, ids, exceptions);

  base::Optional<base::Value> regional_selectors = g_huhi_browser_process->
      ad_block_regional_service_manager()->
          HiddenClassIdSelectors(classes, ids, exceptions);

  base::Optional<base::Value> custom_selectors = g_huhi_browser_process->
      ad_block_custom_filters_service()->
          HiddenClassIdSelectors(classes, ids, exceptions);

  if (hide_selectors && hide_selectors->is_list()) {
    if (regional_selectors && regional_selectors->is_list()) {
      for (auto i = regional_selectors->GetList().begin();
              i < regional_selectors->GetList().end();
              i++) {
        hide_selectors->Append(std::move(*i));
      }
    }
  } else {
    hide_selectors = std::move(regional_selectors);
  }

  auto result_list = std::make_unique<base::ListValue>();
  if (hide_selectors && hide_selectors->is_list()) {
    result_list->Append(std::move(*hide_selectors));
  }
  if (custom_selectors && custom_selectors->is_list()) {
    result_list->Append(std::move(*custom_selectors));
  }

  return result_list;
}

void HuhiShieldsHiddenClassIdSelectorsFunction::
    GetHiddenClassIdSelectorsOnUI(std::unique_ptr<base::ListValue> selectors) {
  Respond(ArgumentList(std::move(selectors)));
}


ExtensionFunction::ResponseAction HuhiShieldsAllowScriptsOnceFunction::Run() {
  std::unique_ptr<huhi_shields::AllowScriptsOnce::Params> params(
      huhi_shields::AllowScriptsOnce::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  // Get web contents for this tab
  content::WebContents* contents = nullptr;
  if (!ExtensionTabUtil::GetTabById(
          params->tab_id, Profile::FromBrowserContext(browser_context()),
          include_incognito_information(), nullptr, nullptr, &contents,
          nullptr)) {
    return RespondNow(Error(tabs_constants::kTabNotFoundError,
                            base::NumberToString(params->tab_id)));
  }

  HuhiShieldsWebContentsObserver::FromWebContents(contents)->AllowScriptsOnce(
      params->origins, contents);
  return RespondNow(NoArguments());
}

HuhiShieldsOpenBrowserActionUIFunction::
~HuhiShieldsOpenBrowserActionUIFunction() {
}

ExtensionFunction::ResponseAction
HuhiShieldsOpenBrowserActionUIFunction::Run() {
  std::unique_ptr<huhi_shields::OpenBrowserActionUI::Params> params(
      huhi_shields::OpenBrowserActionUI::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());
  std::string error;
  if (!HuhiActionAPI::ShowActionUI(this,
      huhi_extension_id,
      std::move(params->window_id),
      std::move(params->relative_path), &error)) {
    return RespondNow(Error(error));
  }
  return RespondNow(NoArguments());
}

ExtensionFunction::ResponseAction
HuhiShieldsSetHuhiShieldsEnabledFunction::Run() {
  std::unique_ptr<huhi_shields::SetHuhiShieldsEnabled::Params> params(
      huhi_shields::SetHuhiShieldsEnabled::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  const GURL url(params->url);
  // we don't allow setting defaults from the extension
  if (url.is_empty() || !url.is_valid()) {
    return RespondNow(Error(kInvalidUrlError, params->url));
  }

  Profile* profile = Profile::FromBrowserContext(browser_context());
  ::huhi_shields::SetHuhiShieldsEnabled(
      HostContentSettingsMapFactory::GetForProfile(profile),
      params->enabled,
      url,
      g_browser_process->local_state());

  return RespondNow(NoArguments());
}

ExtensionFunction::ResponseAction
HuhiShieldsGetHuhiShieldsEnabledFunction::Run() {
  std::unique_ptr<huhi_shields::GetHuhiShieldsEnabled::Params> params(
      huhi_shields::GetHuhiShieldsEnabled::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  const GURL url(params->url);
  // we don't allow getting defaults from the extension
  if (url.is_empty() || !url.is_valid()) {
    return RespondNow(Error(kInvalidUrlError, params->url));
  }

  Profile* profile = Profile::FromBrowserContext(browser_context());
  auto enabled = ::huhi_shields::GetHuhiShieldsEnabled(
      HostContentSettingsMapFactory::GetForProfile(profile),
      url);
  auto result = std::make_unique<base::Value>(enabled);

  return RespondNow(OneArgument(std::move(result)));
}

ExtensionFunction::ResponseAction
HuhiShieldsShouldDoCosmeticFilteringFunction::Run() {
  std::unique_ptr<huhi_shields::ShouldDoCosmeticFiltering::Params>
    params(
      huhi_shields::ShouldDoCosmeticFiltering::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  const GURL url(params->url);
  // we don't allow getting defaults from the extension
  if (url.is_empty() || !url.is_valid()) {
    return RespondNow(Error(kInvalidUrlError, params->url));
  }

  Profile* profile = Profile::FromBrowserContext(browser_context());
  const bool enabled = ::huhi_shields::ShouldDoCosmeticFiltering(
      HostContentSettingsMapFactory::GetForProfile(profile),
      url);

  return RespondNow(OneArgument(std::make_unique<base::Value>(enabled)));
}

ExtensionFunction::ResponseAction
HuhiShieldsSetCosmeticFilteringControlTypeFunction::Run() {
  std::unique_ptr<huhi_shields::SetCosmeticFilteringControlType::Params>
    params(
      huhi_shields::SetCosmeticFilteringControlType::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  const GURL url(params->url);
  // we don't allow setting defaults from the extension
  if (url.is_empty() || !url.is_valid()) {
    return RespondNow(Error(kInvalidUrlError, params->url));
  }

  auto control_type = ControlTypeFromString(params->control_type);
  if (control_type == ControlType::INVALID) {
    return RespondNow(Error(kInvalidControlTypeError, params->control_type));
  }

  Profile* profile = Profile::FromBrowserContext(browser_context());
  ::huhi_shields::SetCosmeticFilteringControlType(
      HostContentSettingsMapFactory::GetForProfile(profile),
      control_type,
      url,
      g_browser_process->local_state());

  return RespondNow(NoArguments());
}

ExtensionFunction::ResponseAction
HuhiShieldsIsFirstPartyCosmeticFilteringEnabledFunction::Run() {
  std::unique_ptr<huhi_shields::IsFirstPartyCosmeticFilteringEnabled::Params>
      params(
          huhi_shields::IsFirstPartyCosmeticFilteringEnabled::Params::Create(
          *args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  const GURL url(params->url);
  // we don't allow getting defaults from the extension
  if (url.is_empty() || !url.is_valid()) {
    return RespondNow(Error(kInvalidUrlError, params->url));
  }

  Profile* profile = Profile::FromBrowserContext(browser_context());
  auto result = std::make_unique<base::Value>(
      ::huhi_shields::IsFirstPartyCosmeticFilteringEnabled(
          HostContentSettingsMapFactory::GetForProfile(profile),
          url));

  return RespondNow(OneArgument(std::move(result)));
}

ExtensionFunction::ResponseAction HuhiShieldsSetAdControlTypeFunction::Run() {
  std::unique_ptr<huhi_shields::SetAdControlType::Params> params(
      huhi_shields::SetAdControlType::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  const GURL url(params->url);
  // we don't allow setting defaults from the extension
  if (url.is_empty() || !url.is_valid()) {
    return RespondNow(Error(kInvalidUrlError, params->url));
  }

  auto control_type = ControlTypeFromString(params->control_type);
  if (control_type == ControlType::INVALID) {
    return RespondNow(Error(kInvalidControlTypeError, params->control_type));
  }

  Profile* profile = Profile::FromBrowserContext(browser_context());
  ::huhi_shields::SetAdControlType(
      HostContentSettingsMapFactory::GetForProfile(profile),
      control_type,
      url,
      g_browser_process->local_state());

  return RespondNow(NoArguments());
}

ExtensionFunction::ResponseAction HuhiShieldsGetAdControlTypeFunction::Run() {
  std::unique_ptr<huhi_shields::GetAdControlType::Params> params(
      huhi_shields::GetAdControlType::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  const GURL url(params->url);
  // we don't allow getting defaults from the extension
  if (url.is_empty() || !url.is_valid()) {
    return RespondNow(Error(kInvalidUrlError, params->url));
  }

  Profile* profile = Profile::FromBrowserContext(browser_context());
  auto type = ::huhi_shields::GetAdControlType(
      HostContentSettingsMapFactory::GetForProfile(profile),
      url);
  auto result = std::make_unique<base::Value>(ControlTypeToString(type));

  return RespondNow(OneArgument(std::move(result)));
}

ExtensionFunction::ResponseAction
HuhiShieldsSetCookieControlTypeFunction::Run() {
  std::unique_ptr<huhi_shields::SetCookieControlType::Params> params(
      huhi_shields::SetCookieControlType::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  const GURL url(params->url);
  // we don't allow setting defaults from the extension
  if (url.is_empty() || !url.is_valid()) {
    return RespondNow(Error(kInvalidUrlError, params->url));
  }

  auto control_type = ControlTypeFromString(params->control_type);
  if (control_type == ControlType::INVALID) {
    return RespondNow(Error(kInvalidControlTypeError, params->control_type));
  }

  Profile* profile = Profile::FromBrowserContext(browser_context());
  ::huhi_shields::SetCookieControlType(
      HostContentSettingsMapFactory::GetForProfile(profile),
      control_type,
      url,
      g_browser_process->local_state());

  return RespondNow(NoArguments());
}

ExtensionFunction::ResponseAction
HuhiShieldsGetCookieControlTypeFunction::Run() {
  std::unique_ptr<huhi_shields::GetCookieControlType::Params> params(
      huhi_shields::GetCookieControlType::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  const GURL url(params->url);
  // we don't allow getting defaults from the extension
  if (url.is_empty() || !url.is_valid()) {
    return RespondNow(Error(kInvalidUrlError, params->url));
  }

  Profile* profile = Profile::FromBrowserContext(browser_context());
  auto type = ::huhi_shields::GetCookieControlType(
      HostContentSettingsMapFactory::GetForProfile(profile),
      url);
  auto result = std::make_unique<base::Value>(ControlTypeToString(type));

  return RespondNow(OneArgument(std::move(result)));
}

ExtensionFunction::ResponseAction
HuhiShieldsSetFingerprintingControlTypeFunction::Run() {
  std::unique_ptr<huhi_shields::SetFingerprintingControlType::Params> params(
      huhi_shields::SetFingerprintingControlType::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  const GURL url(params->url);
  // we don't allow setting defaults from the extension
  if (url.is_empty() || !url.is_valid()) {
    return RespondNow(Error(kInvalidUrlError, params->url));
  }

  auto control_type = ControlTypeFromString(params->control_type);
  if (control_type == ControlType::INVALID) {
    return RespondNow(Error(kInvalidControlTypeError, params->control_type));
  }

  Profile* profile = Profile::FromBrowserContext(browser_context());
  ::huhi_shields::SetFingerprintingControlType(
      HostContentSettingsMapFactory::GetForProfile(profile),
      control_type,
      url,
      g_browser_process->local_state());

  return RespondNow(NoArguments());
}

ExtensionFunction::ResponseAction
HuhiShieldsGetFingerprintingControlTypeFunction::Run() {
  std::unique_ptr<huhi_shields::GetFingerprintingControlType::Params> params(
      huhi_shields::GetFingerprintingControlType::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  const GURL url(params->url);
  // we don't allow getting defaults from the extension
  if (url.is_empty() || !url.is_valid()) {
    return RespondNow(Error(kInvalidUrlError, params->url));
  }

  Profile* profile = Profile::FromBrowserContext(browser_context());
  auto type = ::huhi_shields::GetFingerprintingControlType(
      HostContentSettingsMapFactory::GetForProfile(profile),
      url);
  auto result =
      std::make_unique<base::Value>(ControlTypeToString(type));

  return RespondNow(OneArgument(std::move(result)));
}

ExtensionFunction::ResponseAction
HuhiShieldsSetHTTPSEverywhereEnabledFunction::Run() {
  std::unique_ptr<huhi_shields::SetHTTPSEverywhereEnabled::Params> params(
      huhi_shields::SetHTTPSEverywhereEnabled::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  const GURL url(params->url);
  // we don't allow setting defaults from the extension
  if (url.is_empty() || !url.is_valid()) {
    return RespondNow(Error(kInvalidUrlError, params->url));
  }

  Profile* profile = Profile::FromBrowserContext(browser_context());
  ::huhi_shields::SetHTTPSEverywhereEnabled(
      HostContentSettingsMapFactory::GetForProfile(profile),
      params->enabled,
      url,
      g_browser_process->local_state());

  return RespondNow(NoArguments());
}

ExtensionFunction::ResponseAction
HuhiShieldsGetHTTPSEverywhereEnabledFunction::Run() {
  std::unique_ptr<huhi_shields::GetHTTPSEverywhereEnabled::Params> params(
      huhi_shields::GetHTTPSEverywhereEnabled::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  const GURL url(params->url);
  // we don't allow getting defaults from the extension
  if (url.is_empty() || !url.is_valid()) {
    return RespondNow(Error(kInvalidUrlError, params->url));
  }

  Profile* profile = Profile::FromBrowserContext(browser_context());
  auto type = ::huhi_shields::GetHTTPSEverywhereEnabled(
      HostContentSettingsMapFactory::GetForProfile(profile),
      url);
  auto result = std::make_unique<base::Value>(type);

  return RespondNow(OneArgument(std::move(result)));
}

ExtensionFunction::ResponseAction
HuhiShieldsSetNoScriptControlTypeFunction::Run() {
  std::unique_ptr<huhi_shields::SetNoScriptControlType::Params> params(
      huhi_shields::SetNoScriptControlType::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  const GURL url(params->url);
  // we don't allow setting defaults from the extension
  if (url.is_empty() || !url.is_valid()) {
    return RespondNow(Error(kInvalidUrlError, params->url));
  }

  auto control_type = ControlTypeFromString(params->control_type);
  if (control_type == ControlType::INVALID) {
    return RespondNow(Error(kInvalidControlTypeError, params->control_type));
  }

  Profile* profile = Profile::FromBrowserContext(browser_context());
  ::huhi_shields::SetNoScriptControlType(
      HostContentSettingsMapFactory::GetForProfile(profile),
      control_type,
      url,
      g_browser_process->local_state());

  return RespondNow(NoArguments());
}

ExtensionFunction::ResponseAction
HuhiShieldsGetNoScriptControlTypeFunction::Run() {
  std::unique_ptr<huhi_shields::GetNoScriptControlType::Params> params(
      huhi_shields::GetNoScriptControlType::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  const GURL url(params->url);
  // we don't allow getting defaults from the extension
  if (url.is_empty() || !url.is_valid()) {
    return RespondNow(Error(kInvalidUrlError, params->url));
  }

  Profile* profile = Profile::FromBrowserContext(browser_context());
  auto type = ::huhi_shields::GetNoScriptControlType(
      HostContentSettingsMapFactory::GetForProfile(profile),
      url);
  auto result = std::make_unique<base::Value>(ControlTypeToString(type));

  return RespondNow(OneArgument(std::move(result)));
}

ExtensionFunction::ResponseAction
HuhiShieldsOnShieldsPanelShownFunction::Run() {
  ::huhi_shields::MaybeRecordShieldsUsageP3A(::huhi_shields::kClicked,
                                              g_browser_process->local_state());
  return RespondNow(NoArguments());
}

ExtensionFunction::ResponseAction HuhiShieldsReportBrokenSiteFunction::Run() {
  std::unique_ptr<huhi_shields::ReportBrokenSite::Params> params(
      huhi_shields::ReportBrokenSite::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  // Get web contents for this tab
  content::WebContents* contents = nullptr;
  if (!ExtensionTabUtil::GetTabById(
        params->tab_id,
        Profile::FromBrowserContext(browser_context()),
        false,
        nullptr,
        nullptr,
        &contents,
        nullptr)) {
    return RespondNow(Error(tabs_constants::kTabNotFoundError,
                            base::NumberToString(params->tab_id)));
  }

  OpenWebcompatReporterDialog(contents);

  return RespondNow(NoArguments());
}

}  // namespace api
}  // namespace extensions
