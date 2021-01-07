/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/extensions/api/huhi_rewards_api.h"

#include <map>
#include <memory>
#include <string>
#include <utility>

#include "base/bind.h"
#include "base/strings/string_number_conversions.h"
#include "huhi/browser/huhi_rewards/rewards_service_factory.h"
#include "huhi/browser/huhi_rewards/tip_dialog.h"
#include "huhi/browser/extensions/api/huhi_action_api.h"
#include "huhi/browser/extensions/huhi_component_loader.h"
#include "huhi/browser/profiles/profile_util.h"
#include "huhi/common/extensions/api/huhi_rewards.h"
#include "huhi/components/huhi_ads/browser/ads_service.h"
#include "huhi/components/huhi_ads/browser/ads_service_factory.h"
#include "huhi/components/huhi_rewards/browser/rewards_service.h"
#include "chrome/browser/extensions/api/tabs/tabs_constants.h"
#include "chrome/browser/extensions/chrome_extension_function_details.h"
#include "chrome/browser/extensions/extension_service.h"
#include "chrome/browser/extensions/extension_tab_util.h"
#include "chrome/browser/profiles/profile.h"
#include "content/public/browser/web_contents.h"
#include "extensions/browser/extension_system.h"
#include "extensions/common/constants.h"

using huhi_ads::AdsService;
using huhi_ads::AdsServiceFactory;
using huhi_rewards::RewardsService;
using huhi_rewards::RewardsServiceFactory;

namespace extensions {
namespace api {

HuhiRewardsOpenBrowserActionUIFunction::
~HuhiRewardsOpenBrowserActionUIFunction() {
}

ExtensionFunction::ResponseAction
HuhiRewardsOpenBrowserActionUIFunction::Run() {
  std::unique_ptr<huhi_rewards::OpenBrowserActionUI::Params> params(
      huhi_rewards::OpenBrowserActionUI::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());
  std::string error;
  if (!HuhiActionAPI::ShowActionUI(this,
      huhi_rewards_extension_id,
      std::move(params->window_id),
      std::move(params->relative_path), &error)) {
    return RespondNow(Error(error));
  }
  return RespondNow(NoArguments());
}

HuhiRewardsUpdateMediaDurationFunction::
    ~HuhiRewardsUpdateMediaDurationFunction() {}

ExtensionFunction::ResponseAction
HuhiRewardsUpdateMediaDurationFunction::Run() {
  std::unique_ptr<huhi_rewards::UpdateMediaDuration::Params> params(
      huhi_rewards::UpdateMediaDuration::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
      RewardsServiceFactory::GetForProfile(profile);

  if (!rewards_service) {
    return RespondNow(NoArguments());
  }

  rewards_service->UpdateMediaDuration(
      params->window_id,
      params->publisher_key,
      params->duration,
      params->first_visit);

  return RespondNow(NoArguments());
}

HuhiRewardsGetPublisherInfoFunction::
~HuhiRewardsGetPublisherInfoFunction() {
}

ExtensionFunction::ResponseAction
HuhiRewardsGetPublisherInfoFunction::Run() {
  std::unique_ptr<huhi_rewards::GetPublisherInfo::Params> params(
      huhi_rewards::GetPublisherInfo::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
      RewardsServiceFactory::GetForProfile(profile);

  if (!rewards_service) {
    return RespondNow(Error("Rewards service is not initialized"));
  }

  rewards_service->GetPublisherInfo(
      params->publisher_key,
      base::Bind(
          &HuhiRewardsGetPublisherInfoFunction::OnGetPublisherInfo,
          this));

  return RespondLater();
}

void HuhiRewardsGetPublisherInfoFunction::OnGetPublisherInfo(
    const ledger::type::Result result,
    ledger::type::PublisherInfoPtr info) {
  if (!info) {
    Respond(
        OneArgument(std::make_unique<base::Value>(static_cast<int>(result))));
    return;
  }

  auto dict = std::make_unique<base::Value>(base::Value::Type::DICTIONARY);
  dict->SetStringKey("publisherKey", info->id);
  dict->SetStringKey("name", info->name);
  dict->SetIntKey("percentage", info->percent);
  dict->SetIntKey("status", static_cast<int>(info->status));
  dict->SetIntKey("excluded", static_cast<int>(info->excluded));
  dict->SetStringKey("url", info->url);
  dict->SetStringKey("provider", info->provider);
  dict->SetStringKey("favIconUrl", info->favicon_url);

  Respond(TwoArguments(
      std::make_unique<base::Value>(static_cast<int>(result)),
      std::move(dict)));
}

HuhiRewardsGetPublisherPanelInfoFunction::
    ~HuhiRewardsGetPublisherPanelInfoFunction() {}

ExtensionFunction::ResponseAction
HuhiRewardsGetPublisherPanelInfoFunction::Run() {
  std::unique_ptr<huhi_rewards::GetPublisherPanelInfo::Params> params(
      huhi_rewards::GetPublisherPanelInfo::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
      RewardsServiceFactory::GetForProfile(profile);

  if (!rewards_service) {
    return RespondNow(NoArguments());
  }

  rewards_service->GetPublisherPanelInfo(
      params->publisher_key,
      base::Bind(
          &HuhiRewardsGetPublisherPanelInfoFunction::OnGetPublisherPanelInfo,
          this));

  return RespondLater();
}

void HuhiRewardsGetPublisherPanelInfoFunction::OnGetPublisherPanelInfo(
    const ledger::type::Result result,
    ledger::type::PublisherInfoPtr info) {
  if (!info) {
    Respond(
        OneArgument(std::make_unique<base::Value>(static_cast<int>(result))));
    return;
  }

  auto dict = std::make_unique<base::Value>(base::Value::Type::DICTIONARY);
  dict->SetStringKey("publisherKey", info->id);
  dict->SetStringKey("name", info->name);
  dict->SetIntKey("percentage", info->percent);
  dict->SetIntKey("status", static_cast<int>(info->status));
  dict->SetIntKey("excluded", static_cast<int>(info->excluded));
  dict->SetStringKey("url", info->url);
  dict->SetStringKey("provider", info->provider);
  dict->SetStringKey("favIconUrl", info->favicon_url);

  Respond(TwoArguments(
      std::make_unique<base::Value>(static_cast<int>(result)),
      std::move(dict)));
}

HuhiRewardsSavePublisherInfoFunction::
    ~HuhiRewardsSavePublisherInfoFunction() {}

ExtensionFunction::ResponseAction
HuhiRewardsSavePublisherInfoFunction::Run() {
  std::unique_ptr<huhi_rewards::SavePublisherInfo::Params>
      params(huhi_rewards::SavePublisherInfo::Params::Create(
          *args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
      RewardsServiceFactory::GetForProfile(profile);

  if (!rewards_service) {
    return RespondNow(NoArguments());
  }

  auto publisher_info = ledger::type::PublisherInfo::New();
  publisher_info->id = params->publisher_key;
  publisher_info->name = params->publisher_name;
  publisher_info->url = params->url;
  publisher_info->provider = params->media_type;
  publisher_info->favicon_url = params->fav_icon_url;

  rewards_service->SavePublisherInfo(
      params->window_id,
      std::move(publisher_info),
      base::Bind(
          &HuhiRewardsSavePublisherInfoFunction::OnSavePublisherInfo,
          this));

  return RespondLater();
}

void HuhiRewardsSavePublisherInfoFunction::OnSavePublisherInfo(
    const ledger::type::Result result) {
  Respond(OneArgument(std::make_unique<base::Value>(static_cast<int>(result))));
}

HuhiRewardsTipSiteFunction::~HuhiRewardsTipSiteFunction() {
}

ExtensionFunction::ResponseAction HuhiRewardsTipSiteFunction::Run() {
  std::unique_ptr<huhi_rewards::TipSite::Params> params(
      huhi_rewards::TipSite::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  // Sanity check: don't allow tips in private / tor contexts,
  // although the command should not have been enabled in the first place.
  if (!huhi::IsRegularProfile(browser_context())) {
    return RespondNow(Error("Cannot tip to site in a private context"));
  }

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

  auto params_dict = std::make_unique<base::DictionaryValue>();
  params_dict->SetString("publisherKey", params->publisher_key);
  params_dict->SetString("entryPoint", params->entry_point);
  params_dict->SetString(
      "url", contents ? contents->GetLastCommittedURL().spec() : std::string());
  ::huhi_rewards::OpenTipDialog(contents, std::move(params_dict));

  return RespondNow(NoArguments());
}

HuhiRewardsTipUserFunction::HuhiRewardsTipUserFunction()
    : weak_factory_(this) {
}

HuhiRewardsTipUserFunction::~HuhiRewardsTipUserFunction() {
}

ExtensionFunction::ResponseAction HuhiRewardsTipUserFunction::Run() {
  std::unique_ptr<huhi_rewards::TipUser::Params> params(
      huhi_rewards::TipUser::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  // Sanity check: don't allow tips in private / tor contexts,
  // although the command should not have been enabled in the first place.
  if (!huhi::IsRegularProfile(browser_context())) {
    return RespondNow(Error("Cannot tip user in a private context"));
  }

  Profile* profile = Profile::FromBrowserContext(browser_context());
  auto* rewards_service = RewardsServiceFactory::GetForProfile(profile);
  if (!rewards_service) {
    return RespondNow(Error("Rewards service is not initialized"));
  }

  extensions::ExtensionService* extension_service =
      extensions::ExtensionSystem::Get(profile)->extension_service();
  if (!extension_service) {
    return RespondNow(Error("Extension service is not initialized"));
  }

  AddRef();

  extensions::ComponentLoader* component_loader =
      extension_service->component_loader();
  static_cast<extensions::HuhiComponentLoader*>(component_loader)
      ->AddRewardsExtension();

  rewards_service->StartProcess(
      base::BindOnce(
          &HuhiRewardsTipUserFunction::OnTipUserStartProcess,
          this,
          params->publisher_key));

  return RespondNow(NoArguments());
}

void HuhiRewardsTipUserFunction::OnTipUserStartProcess(
    const std::string& publisher_key,
    ledger::type::Result result) {
  if (result != ledger::type::Result::LEDGER_OK) {
    Release();
    return;
  }

  Profile* profile = Profile::FromBrowserContext(browser_context());
  auto* rewards_service = RewardsServiceFactory::GetForProfile(profile);
  if (!rewards_service) {
    Release();
    return;
  }

  rewards_service->GetPublisherInfo(
      publisher_key,
      base::Bind(&HuhiRewardsTipUserFunction::OnTipUserGetPublisherInfo,
                 this));
}

void HuhiRewardsTipUserFunction::OnTipUserGetPublisherInfo(
    const ledger::type::Result result,
    ledger::type::PublisherInfoPtr info) {
  if (result != ledger::type::Result::LEDGER_OK &&
      result != ledger::type::Result::NOT_FOUND) {
    Release();
    return;
  }

  if (result == ledger::type::Result::LEDGER_OK) {
    ShowTipDialog();
    Release();
    return;
  }

  std::unique_ptr<huhi_rewards::TipUser::Params> params(
      huhi_rewards::TipUser::Params::Create(*args_));

  auto publisher_info = ledger::type::PublisherInfo::New();
  publisher_info->id = params->publisher_key;
  publisher_info->name = params->publisher_name;
  publisher_info->url = params->url;
  publisher_info->provider = params->media_type;
  publisher_info->favicon_url = params->fav_icon_url;

  Profile* profile = Profile::FromBrowserContext(browser_context());
  auto* rewards_service = RewardsServiceFactory::GetForProfile(profile);
  if (!rewards_service) {
    Release();
    return;
  }

  rewards_service->SavePublisherInfo(
      0,
      std::move(publisher_info),
      base::Bind(&HuhiRewardsTipUserFunction::
                 OnTipUserSavePublisherInfo,
                 weak_factory_.GetWeakPtr()));
}

void HuhiRewardsTipUserFunction::OnTipUserSavePublisherInfo(
    const ledger::type::Result result) {
  if (result != ledger::type::Result::LEDGER_OK) {
    Release();
    return;
  }

  ShowTipDialog();
  Release();
}

void HuhiRewardsTipUserFunction::ShowTipDialog() {
  std::unique_ptr<huhi_rewards::TipUser::Params> params(
      huhi_rewards::TipUser::Params::Create(*args_));
  if (!params) {
    Release();
    return;
  }

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
    Release();
    return;
  }

  base::Value media_meta_data_dict(base::Value::Type::DICTIONARY);
  media_meta_data_dict.SetStringKey("mediaType", params->media_type);
  media_meta_data_dict.SetStringKey("publisherKey", params->publisher_key);
  media_meta_data_dict.SetStringKey("publisherName", params->publisher_name);
  media_meta_data_dict.SetStringKey(
      "publisherScreenName",
      params->publisher_screen_name);
  media_meta_data_dict.SetStringKey("postId", params->post_id);
  media_meta_data_dict.SetStringKey("postTimestamp", params->post_timestamp);
  media_meta_data_dict.SetStringKey("postText", params->post_text);

  auto params_dict = std::make_unique<base::DictionaryValue>();
  params_dict->SetString("publisherKey", params->publisher_key);
  params_dict->SetString("url", params->url);
  params_dict->SetPath("mediaMetaData", std::move(media_meta_data_dict));

  ::huhi_rewards::OpenTipDialog(contents, std::move(params_dict));
}

HuhiRewardsGetPublisherDataFunction::~HuhiRewardsGetPublisherDataFunction() {
}

HuhiRewardsIncludeInAutoContributionFunction::
  ~HuhiRewardsIncludeInAutoContributionFunction() {
}

ExtensionFunction::ResponseAction
  HuhiRewardsIncludeInAutoContributionFunction::Run() {
  std::unique_ptr<huhi_rewards::IncludeInAutoContribution::Params> params(
    huhi_rewards::IncludeInAutoContribution::Params::Create(*args_));
  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
    RewardsServiceFactory::GetForProfile(profile);
  if (rewards_service) {
    rewards_service->SetPublisherExclude(
      params->publisher_key,
      params->exclude);
  }
  return RespondNow(NoArguments());
}

ExtensionFunction::ResponseAction HuhiRewardsGetPublisherDataFunction::Run() {
  std::unique_ptr<huhi_rewards::GetPublisherData::Params> params(
      huhi_rewards::GetPublisherData::Params::Create(*args_));
  Profile* profile = Profile::FromBrowserContext(browser_context());
  auto* rewards_service = RewardsServiceFactory::GetForProfile(profile);
  if (rewards_service) {
    rewards_service->GetPublisherActivityFromUrl(params->window_id,
                                                  params->url,
                                                  params->favicon_url,
                                                  params->publisher_blob);
  }
  return RespondNow(NoArguments());
}

HuhiRewardsGetRewardsParametersFunction::
~HuhiRewardsGetRewardsParametersFunction() = default;

ExtensionFunction::ResponseAction
HuhiRewardsGetRewardsParametersFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());
  auto* rewards_service = RewardsServiceFactory::GetForProfile(profile);
  if (!rewards_service) {
    auto data = std::make_unique<base::Value>(base::Value::Type::DICTIONARY);
    return RespondNow(OneArgument(std::move(data)));
  }

  rewards_service->GetRewardsParameters(base::BindOnce(
      &HuhiRewardsGetRewardsParametersFunction::OnGet,
      this));
  return RespondLater();
}

void HuhiRewardsGetRewardsParametersFunction::OnGet(
    ledger::type::RewardsParametersPtr parameters) {
  auto data = std::make_unique<base::DictionaryValue>();

  if (!parameters) {
    return Respond(OneArgument(std::move(data)));
  }

  data->SetDouble("rate", parameters->rate);
  auto monthly_choices = std::make_unique<base::ListValue>();
  for (auto const& item : parameters->monthly_tip_choices) {
    monthly_choices->Append(base::Value(item));
  }
  data->SetList("monthlyTipChoices", std::move(monthly_choices));

  Respond(OneArgument(std::move(data)));
}

HuhiRewardsGetBalanceReportFunction::
~HuhiRewardsGetBalanceReportFunction() = default;

ExtensionFunction::ResponseAction HuhiRewardsGetBalanceReportFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());
  auto* rewards_service = RewardsServiceFactory::GetForProfile(profile);
  if (!rewards_service) {
    auto data = std::make_unique<base::Value>(base::Value::Type::DICTIONARY);
    return RespondNow(OneArgument(std::move(data)));
  }

  std::unique_ptr<huhi_rewards::GetBalanceReport::Params> params(
      huhi_rewards::GetBalanceReport::Params::Create(*args_));

  rewards_service->GetBalanceReport(
      params->month,
      params->year,
      base::BindOnce(
          &HuhiRewardsGetBalanceReportFunction::OnBalanceReport,
          this));
  return RespondLater();
}

void HuhiRewardsGetBalanceReportFunction::OnBalanceReport(
    const ledger::type::Result result,
    ledger::type::BalanceReportInfoPtr report) {
  auto data = std::make_unique<base::Value>(base::Value::Type::DICTIONARY);
  if (!report) {
    Respond(OneArgument(std::move(data)));
    return;
  }
  data->SetDoubleKey("ads", report->earning_from_ads);
  data->SetDoubleKey("contribute", report->auto_contribute);
  data->SetDoubleKey("grant", report->grants);
  data->SetDoubleKey("tips", report->one_time_donation);
  data->SetDoubleKey("monthly", report->recurring_donation);
  Respond(OneArgument(std::move(data)));
}

HuhiRewardsFetchPromotionsFunction::
~HuhiRewardsFetchPromotionsFunction() = default;

ExtensionFunction::ResponseAction HuhiRewardsFetchPromotionsFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
    RewardsServiceFactory::GetForProfile(profile);
  if (rewards_service) {
    rewards_service->FetchPromotions();
  }
  return RespondNow(NoArguments());
}

HuhiRewardsClaimPromotionFunction::
~HuhiRewardsClaimPromotionFunction() = default;

ExtensionFunction::ResponseAction HuhiRewardsClaimPromotionFunction::Run() {
  std::unique_ptr<huhi_rewards::ClaimPromotion::Params> params(
      huhi_rewards::ClaimPromotion::Params::Create(*args_));
  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
    RewardsServiceFactory::GetForProfile(profile);
  if (!rewards_service) {
    auto data = std::make_unique<base::Value>(base::Value::Type::DICTIONARY);
    data->SetIntKey("result", 1);
    return RespondNow(OneArgument(std::move(data)));
  }

  rewards_service->ClaimPromotion(
      params->promotion_id,
      base::BindOnce(
          &HuhiRewardsClaimPromotionFunction::OnClaimPromotion,
          this,
          params->promotion_id));
  return RespondLater();
}

void HuhiRewardsClaimPromotionFunction::OnClaimPromotion(
    const std::string& promotion_id,
    const ledger::type::Result result,
    const std::string& captcha_image,
    const std::string& hint,
    const std::string& captcha_id) {
  auto data = std::make_unique<base::Value>(base::Value::Type::DICTIONARY);
  data->SetIntKey("result", static_cast<int>(result));
  data->SetStringKey("promotionId", promotion_id);
  data->SetStringKey("captchaImage", captcha_image);
  data->SetStringKey("captchaId", captcha_id);
  data->SetStringKey("hint", hint);
  Respond(OneArgument(std::move(data)));
}

HuhiRewardsAttestPromotionFunction::
~HuhiRewardsAttestPromotionFunction() = default;

ExtensionFunction::ResponseAction HuhiRewardsAttestPromotionFunction::Run() {
  std::unique_ptr<huhi_rewards::AttestPromotion::Params> params(
      huhi_rewards::AttestPromotion::Params::Create(*args_));
  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
    RewardsServiceFactory::GetForProfile(profile);
  if (!rewards_service) {
    return RespondNow(OneArgument(std::make_unique<base::Value>(1)));
  }

  rewards_service->AttestPromotion(params->promotion_id, params->solution,
      base::BindOnce(
        &HuhiRewardsAttestPromotionFunction::OnAttestPromotion,
        this,
        params->promotion_id));
  return RespondLater();
}

void HuhiRewardsAttestPromotionFunction::OnAttestPromotion(
    const std::string& promotion_id,
    const ledger::type::Result result,
    ledger::type::PromotionPtr promotion) {
  auto data = std::make_unique<base::Value>(base::Value::Type::DICTIONARY);
  data->SetStringKey("promotionId", promotion_id);

  if (!promotion) {
    Respond(
        TwoArguments(
            std::make_unique<base::Value>(static_cast<int>(result)),
            std::move(data)));
    return;
  }

  data->SetIntKey("expiresAt", promotion->expires_at);
  data->SetDoubleKey("amount", promotion->approximate_value);
  data->SetIntKey("type", static_cast<int>(promotion->type));
  Respond(TwoArguments(
      std::make_unique<base::Value>(static_cast<int>(result)),
      std::move(data)));
}

HuhiRewardsGetPendingContributionsTotalFunction::
~HuhiRewardsGetPendingContributionsTotalFunction() {
}

ExtensionFunction::ResponseAction
HuhiRewardsGetPendingContributionsTotalFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
    RewardsServiceFactory::GetForProfile(profile);

  if (!rewards_service) {
    return RespondNow(OneArgument(
          std::make_unique<base::Value>(0.0)));
  }

  rewards_service->GetPendingContributionsTotal(base::Bind(
        &HuhiRewardsGetPendingContributionsTotalFunction::OnGetPendingTotal,
        this));
  return RespondLater();
}

void HuhiRewardsGetPendingContributionsTotalFunction::OnGetPendingTotal(
    double amount) {
  Respond(OneArgument(std::make_unique<base::Value>(amount)));
}

HuhiRewardsSaveAdsSettingFunction::~HuhiRewardsSaveAdsSettingFunction() {
}

ExtensionFunction::ResponseAction HuhiRewardsSaveAdsSettingFunction::Run() {
  std::unique_ptr<huhi_rewards::SaveAdsSetting::Params> params(
      huhi_rewards::SaveAdsSetting::Params::Create(*args_));
  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
      RewardsServiceFactory::GetForProfile(profile);
  AdsService* ads_service_ = AdsServiceFactory::GetForProfile(profile);

  if (!rewards_service || !ads_service_) {
    return RespondNow(Error("Service is not initialized"));
  }

  if (params->key == "adsEnabled") {
    const auto is_enabled =
        params->value == "true" && ads_service_->IsSupportedLocale();
    rewards_service->SetAdsEnabled(is_enabled);
  }

  return RespondNow(NoArguments());
}

HuhiRewardsSetAutoContributeEnabledFunction::
~HuhiRewardsSetAutoContributeEnabledFunction() {
}

ExtensionFunction::ResponseAction
HuhiRewardsSetAutoContributeEnabledFunction::Run() {
  std::unique_ptr<huhi_rewards::SetAutoContributeEnabled::Params> params(
      huhi_rewards::SetAutoContributeEnabled::Params::Create(*args_));
  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
      RewardsServiceFactory::GetForProfile(profile);

  if (!rewards_service) {
    return RespondNow(Error("Rewards service is not initialized"));
  }

  rewards_service->SetAutoContributeEnabled(params->enabled);
  return RespondNow(NoArguments());
}

HuhiRewardsGetACEnabledFunction::
~HuhiRewardsGetACEnabledFunction() {
}

ExtensionFunction::ResponseAction
HuhiRewardsGetACEnabledFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
    RewardsServiceFactory::GetForProfile(profile);

  if (!rewards_service) {
    return RespondNow(Error("Rewards service is not initialized"));
  }

  rewards_service->GetAutoContributeEnabled(base::BindOnce(
        &HuhiRewardsGetACEnabledFunction::OnGetACEnabled,
        this));
  return RespondLater();
}

void HuhiRewardsGetACEnabledFunction::OnGetACEnabled(bool enabled) {
  Respond(OneArgument(std::make_unique<base::Value>(enabled)));
}

HuhiRewardsSaveRecurringTipFunction::
~HuhiRewardsSaveRecurringTipFunction() {
}

ExtensionFunction::ResponseAction
HuhiRewardsSaveRecurringTipFunction::Run() {
  std::unique_ptr<huhi_rewards::SaveRecurringTip::Params> params(
    huhi_rewards::SaveRecurringTip::Params::Create(*args_));

  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service_ =
    RewardsServiceFactory::GetForProfile(profile);

  if (!rewards_service_) {
    return RespondNow(NoArguments());
  }

  rewards_service_->SaveRecurringTip(
      params->publisher_key,
      params->new_amount,
      base::Bind(
          &HuhiRewardsSaveRecurringTipFunction::OnSaveRecurringTip,
          this));

  return RespondLater();
}

void HuhiRewardsSaveRecurringTipFunction::OnSaveRecurringTip(bool success) {
  if (!success) {
    Respond(Error("Failed to save"));
    return;
  }
  Respond(NoArguments());
}

HuhiRewardsRemoveRecurringTipFunction::
~HuhiRewardsRemoveRecurringTipFunction() {
}

ExtensionFunction::ResponseAction
HuhiRewardsRemoveRecurringTipFunction::Run() {
  std::unique_ptr<huhi_rewards::RemoveRecurringTip::Params> params(
    huhi_rewards::RemoveRecurringTip::Params::Create(*args_));

  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service_ =
    RewardsServiceFactory::GetForProfile(profile);

  if (rewards_service_) {
    rewards_service_->RemoveRecurringTip(params->publisher_key);
  }

  return RespondNow(NoArguments());
}

HuhiRewardsGetRecurringTipsFunction::
~HuhiRewardsGetRecurringTipsFunction() {
}

ExtensionFunction::ResponseAction
HuhiRewardsGetRecurringTipsFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
    RewardsServiceFactory::GetForProfile(profile);

  if (!rewards_service) {
    return RespondNow(Error("Rewards service is not initialized"));
  }

  rewards_service->GetRecurringTips(base::Bind(
        &HuhiRewardsGetRecurringTipsFunction::OnGetRecurringTips,
        this));
  return RespondLater();
}

void HuhiRewardsGetRecurringTipsFunction::OnGetRecurringTips(
    ledger::type::PublisherInfoList list) {
  std::unique_ptr<base::DictionaryValue> result(new base::DictionaryValue());
  auto recurringTips = std::make_unique<base::ListValue>();

  if (!list.empty()) {
    for (const auto& item : list) {
      auto tip = std::make_unique<base::DictionaryValue>();
      tip->SetString("publisherKey", item->id);
      tip->SetDouble("amount", item->weight);
      recurringTips->Append(std::move(tip));
    }
  }

  result->SetList("recurringTips", std::move(recurringTips));
  Respond(OneArgument(std::move(result)));
}

HuhiRewardsGetPublisherBannerFunction::
~HuhiRewardsGetPublisherBannerFunction() {
}

ExtensionFunction::ResponseAction
HuhiRewardsGetPublisherBannerFunction::Run() {
  std::unique_ptr<huhi_rewards::GetPublisherBanner::Params> params(
    huhi_rewards::GetPublisherBanner::Params::Create(*args_));

  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
    RewardsServiceFactory::GetForProfile(profile);

  if (!rewards_service) {
    return RespondNow(Error("Rewards service is not initialized"));
  }

  rewards_service->GetPublisherBanner(
      params->publisher_key,
      base::BindOnce(
        &HuhiRewardsGetPublisherBannerFunction::OnPublisherBanner,
        this));
  return RespondLater();
}

void HuhiRewardsGetPublisherBannerFunction::OnPublisherBanner(
    ledger::type::PublisherBannerPtr banner) {
  std::unique_ptr<base::DictionaryValue> result(new base::DictionaryValue());

  if (banner) {
    result->SetString("publisherKey", banner->publisher_key);
    result->SetString("title", banner->title);
    result->SetString("name", banner->name);
    result->SetString("description", banner->description);
    result->SetString("background", banner->background);
    result->SetString("logo", banner->logo);
    result->SetString("provider", banner->provider);
    result->SetInteger("verified", static_cast<int>(banner->status));

    auto amounts = std::make_unique<base::ListValue>();
    for (auto const& value : banner->amounts) {
      amounts->AppendInteger(value);
    }
    result->SetList("amounts", std::move(amounts));

    auto links = std::make_unique<base::DictionaryValue>();
    for (auto const& item : banner->links) {
      links->SetString(item.first, item.second);
    }
    result->SetDictionary("links", std::move(links));
  }

  Respond(OneArgument(std::move(result)));
}

HuhiRewardsRefreshPublisherFunction::~HuhiRewardsRefreshPublisherFunction() {
}

ExtensionFunction::ResponseAction HuhiRewardsRefreshPublisherFunction::Run() {
  std::unique_ptr<huhi_rewards::RefreshPublisher::Params> params(
      huhi_rewards::RefreshPublisher::Params::Create(*args_));

  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
    RewardsServiceFactory::GetForProfile(profile);
  if (!rewards_service) {
    return RespondNow(TwoArguments(
        std::make_unique<base::Value>(false),
        std::make_unique<base::Value>(std::string())));
  }
  rewards_service->RefreshPublisher(
      params->publisher_key,
      base::BindOnce(
        &HuhiRewardsRefreshPublisherFunction::OnRefreshPublisher,
        this));
  return RespondLater();
}

void HuhiRewardsRefreshPublisherFunction::OnRefreshPublisher(
    const ledger::type::PublisherStatus status,
    const std::string& publisher_key) {
  Respond(TwoArguments(
      std::make_unique<base::Value>(static_cast<int>(status)),
      std::make_unique<base::Value>(publisher_key)));
}

HuhiRewardsGetAllNotificationsFunction::
~HuhiRewardsGetAllNotificationsFunction() {
}

ExtensionFunction::ResponseAction
HuhiRewardsGetAllNotificationsFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
    RewardsServiceFactory::GetForProfile(profile);

  auto list = std::make_unique<base::ListValue>();

  if (!rewards_service) {
    return RespondNow(OneArgument(std::move(list)));
  }

  auto notifications = rewards_service->GetAllNotifications();

  for (auto const& notification : notifications) {
    auto item = std::make_unique<base::DictionaryValue>();
    item->SetString("id", notification.second.id_);
    item->SetInteger("type", notification.second.type_);
    item->SetInteger("timestamp", notification.second.timestamp_);

    auto args = std::make_unique<base::ListValue>();
    for (auto const& arg : notification.second.args_) {
      args->AppendString(arg);
    }

    item->SetList("args", std::move(args));
    list->Append(std::move(item));
  }

  return RespondNow(OneArgument(std::move(list)));
}

HuhiRewardsGetInlineTippingPlatformEnabledFunction::
~HuhiRewardsGetInlineTippingPlatformEnabledFunction() {
}

ExtensionFunction::ResponseAction
HuhiRewardsGetInlineTippingPlatformEnabledFunction::Run() {
  std::unique_ptr<huhi_rewards::GetInlineTippingPlatformEnabled::Params>
      params(huhi_rewards::GetInlineTippingPlatformEnabled::Params::Create(
          *args_));

  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
    RewardsServiceFactory::GetForProfile(profile);
  if (!rewards_service) {
    return RespondNow(OneArgument(std::make_unique<base::Value>(false)));
  }

  rewards_service->GetInlineTippingPlatformEnabled(
      params->key,
      base::BindOnce(
          &HuhiRewardsGetInlineTippingPlatformEnabledFunction::
          OnInlineTipSetting,
          this));
  return RespondLater();
}

void HuhiRewardsGetInlineTippingPlatformEnabledFunction::OnInlineTipSetting(
    bool value) {
  Respond(OneArgument(std::make_unique<base::Value>(value)));
}

HuhiRewardsFetchBalanceFunction::
~HuhiRewardsFetchBalanceFunction() {
}

ExtensionFunction::ResponseAction
HuhiRewardsFetchBalanceFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
    RewardsServiceFactory::GetForProfile(profile);
  if (!rewards_service) {
    auto balance_value = std::make_unique<base::DictionaryValue>();
    return RespondNow(OneArgument(std::move(balance_value)));
  }

  rewards_service->FetchBalance(
      base::BindOnce(
          &HuhiRewardsFetchBalanceFunction::OnBalance,
          this));
  return RespondLater();
}

void HuhiRewardsFetchBalanceFunction::OnBalance(
    const ledger::type::Result result,
    ledger::type::BalancePtr balance) {
  auto balance_value = std::make_unique<base::Value>(
      base::Value::Type::DICTIONARY);
  if (result == ledger::type::Result::LEDGER_OK && balance) {
    balance_value->SetDoubleKey("total", balance->total);

    base::Value wallets(base::Value::Type::DICTIONARY);
    for (auto const& rate : balance->wallets) {
      wallets.SetDoubleKey(rate.first, rate.second);
    }
    balance_value->SetKey("wallets", std::move(wallets));
  } else {
    balance_value->SetDoubleKey("total", 0.0);
    base::Value wallets(base::Value::Type::DICTIONARY);
    balance_value->SetKey("wallets", std::move(wallets));
  }

  Respond(OneArgument(std::move(balance_value)));
}

HuhiRewardsGetExternalWalletFunction::
~HuhiRewardsGetExternalWalletFunction() {
}

ExtensionFunction::ResponseAction
HuhiRewardsGetExternalWalletFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
    RewardsServiceFactory::GetForProfile(profile);
  if (!rewards_service) {
  auto data = std::make_unique<base::Value>(
      base::Value::Type::DICTIONARY);
    return RespondNow(OneArgument(std::move(data)));
  }

  std::unique_ptr<huhi_rewards::GetExternalWallet::Params> params(
    huhi_rewards::GetExternalWallet::Params::Create(*args_));

  rewards_service->GetUpholdWallet(
      base::BindOnce(
          &HuhiRewardsGetExternalWalletFunction::OnGetUpholdWallet,
          this));
  return RespondLater();
}

void HuhiRewardsGetExternalWalletFunction::OnGetUpholdWallet(
    const ledger::type::Result result,
    ledger::type::UpholdWalletPtr wallet) {
  if (!wallet) {
    Respond(OneArgument(
        std::make_unique<base::Value>(static_cast<int>(result))));
    return;
  }

  auto data = std::make_unique<base::Value>(base::Value::Type::DICTIONARY);
  data->SetStringKey("token", wallet->token);
  data->SetStringKey("address", wallet->address);
  data->SetIntKey("status", static_cast<int>(wallet->status));
  data->SetStringKey("verifyUrl", wallet->verify_url);
  data->SetStringKey("addUrl", wallet->add_url);
  data->SetStringKey("withdrawUrl", wallet->withdraw_url);
  data->SetStringKey("userName", wallet->user_name);
  data->SetStringKey("accountUrl", wallet->account_url);
  data->SetStringKey("loginUrl", wallet->login_url);

  Respond(TwoArguments(
        std::make_unique<base::Value>(static_cast<int>(result)),
        std::move(data)));
}

HuhiRewardsDisconnectWalletFunction::
~HuhiRewardsDisconnectWalletFunction() {
}

ExtensionFunction::ResponseAction
HuhiRewardsDisconnectWalletFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
    RewardsServiceFactory::GetForProfile(profile);
  if (!rewards_service) {
    return RespondNow(NoArguments());
  }

  std::unique_ptr<huhi_rewards::DisconnectWallet::Params> params(
    huhi_rewards::DisconnectWallet::Params::Create(*args_));

  rewards_service->DisconnectWallet(params->type);
  return RespondNow(NoArguments());
}

HuhiRewardsOnlyAnonWalletFunction::
~HuhiRewardsOnlyAnonWalletFunction() {
}

ExtensionFunction::ResponseAction
HuhiRewardsOnlyAnonWalletFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
    RewardsServiceFactory::GetForProfile(profile);
  if (!rewards_service) {
    return RespondNow(OneArgument(std::make_unique<base::Value>(false)));
  }

  const auto only = rewards_service->OnlyAnonWallet();
  return RespondNow(OneArgument(std::make_unique<base::Value>(only)));
}

HuhiRewardsGetAdsEnabledFunction::
~HuhiRewardsGetAdsEnabledFunction() {
}

ExtensionFunction::ResponseAction
HuhiRewardsGetAdsEnabledFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());
  AdsService* ads_service_ =
      AdsServiceFactory::GetForProfile(profile);

  if (!ads_service_) {
    return RespondNow(Error("Ads service is not initialized"));
  }

  const bool enabled = ads_service_->IsEnabled();
  return RespondNow(
      OneArgument(std::make_unique<base::Value>(enabled)));
}

HuhiRewardsGetAdsEstimatedEarningsFunction::
~HuhiRewardsGetAdsEstimatedEarningsFunction() {
}

ExtensionFunction::ResponseAction
HuhiRewardsGetAdsEstimatedEarningsFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());
  AdsService* ads_service_ =
      AdsServiceFactory::GetForProfile(profile);

  if (!ads_service_) {
    return RespondNow(Error("Ads service is not initialized"));
  }

  ads_service_->GetTransactionHistory(base::Bind(
      &HuhiRewardsGetAdsEstimatedEarningsFunction::OnAdsEstimatedEarnings,
      this));
  return RespondLater();
}

void HuhiRewardsGetAdsEstimatedEarningsFunction::OnAdsEstimatedEarnings(
    const bool success,
    const double estimated_pending_rewards,
    const uint64_t next_payment_date_in_seconds,
    const uint64_t ad_notifications_received_this_month) {
  Respond(OneArgument(
      std::make_unique<base::Value>(estimated_pending_rewards)));
}

HuhiRewardsGetAdsSupportedFunction::
~HuhiRewardsGetAdsSupportedFunction() {
}

ExtensionFunction::ResponseAction
HuhiRewardsGetAdsSupportedFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());
  AdsService* ads_service_ =
      AdsServiceFactory::GetForProfile(profile);

  if (!ads_service_) {
    return RespondNow(Error("Ads service is not initialized"));
  }

  const bool supported = ads_service_->IsSupportedLocale();
  return RespondNow(
      OneArgument(std::make_unique<base::Value>(supported)));
}

HuhiRewardsGetAnonWalletStatusFunction::
~HuhiRewardsGetAnonWalletStatusFunction() = default;

ExtensionFunction::ResponseAction
HuhiRewardsGetAnonWalletStatusFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
    RewardsServiceFactory::GetForProfile(profile);

  if (!rewards_service) {
    return RespondNow(Error("Rewards service is not initialized"));
  }

  rewards_service->GetAnonWalletStatus(base::Bind(
        &HuhiRewardsGetAnonWalletStatusFunction::OnGetAnonWalletStatus,
        this));
  return RespondLater();
}

void HuhiRewardsGetAnonWalletStatusFunction::OnGetAnonWalletStatus(
    const ledger::type::Result result) {
  Respond(OneArgument(std::make_unique<base::Value>(static_cast<int>(result))));
}

HuhiRewardsIsInitializedFunction::
~HuhiRewardsIsInitializedFunction() = default;

ExtensionFunction::ResponseAction
HuhiRewardsIsInitializedFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());
  RewardsService* rewards_service =
    RewardsServiceFactory::GetForProfile(profile);

  if (!rewards_service) {
    return RespondNow(Error("Rewards service is not initialized"));
  }

  const bool initialized = rewards_service->IsInitialized();
  return RespondNow(
      OneArgument(std::make_unique<base::Value>(initialized)));
}

HuhiRewardsShouldShowOnboardingFunction::
~HuhiRewardsShouldShowOnboardingFunction() = default;

ExtensionFunction::ResponseAction
HuhiRewardsShouldShowOnboardingFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());
  auto* rewards_service = RewardsServiceFactory::GetForProfile(profile);
  if (!rewards_service) {
    return RespondNow(Error("Rewards service is not initialized"));
  }

  const bool should_show = rewards_service->ShouldShowOnboarding();
  return RespondNow(
      OneArgument(std::make_unique<base::Value>(should_show)));
}

HuhiRewardsSaveOnboardingResultFunction::
~HuhiRewardsSaveOnboardingResultFunction() = default;

ExtensionFunction::ResponseAction
HuhiRewardsSaveOnboardingResultFunction::Run() {
  using ::huhi_rewards::OnboardingResult;

  std::unique_ptr<huhi_rewards::SaveOnboardingResult::Params> params(
      huhi_rewards::SaveOnboardingResult::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  Profile* profile = Profile::FromBrowserContext(browser_context());
  auto* rewards_service = RewardsServiceFactory::GetForProfile(profile);
  if (!rewards_service) {
    return RespondNow(Error("Rewards service is not initialized"));
  }

  if (params->result == "opted-in") {
    rewards_service->SaveOnboardingResult(OnboardingResult::kOptedIn);
  } else if (params->result == "dismissed") {
    rewards_service->SaveOnboardingResult(OnboardingResult::kDismissed);
  } else {
    NOTREACHED();
  }

  return RespondNow(NoArguments());
}

}  // namespace api
}  // namespace extensions
