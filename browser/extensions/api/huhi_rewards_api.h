/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_EXTENSIONS_API_HUHI_REWARDS_API_H_
#define HUHI_BROWSER_EXTENSIONS_API_HUHI_REWARDS_API_H_

#include <map>
#include <memory>
#include <string>

#include "base/memory/weak_ptr.h"
#include "huhi/vendor/bat-native-ledger/include/bat/ledger/mojom_structs.h"
#include "extensions/browser/extension_function.h"

namespace extensions {
namespace api {

class HuhiRewardsOpenBrowserActionUIFunction :
    public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.openBrowserActionUI", UNKNOWN)

 protected:
  ~HuhiRewardsOpenBrowserActionUIFunction() override;

  ResponseAction Run() override;
};

class HuhiRewardsUpdateMediaDurationFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.updateMediaDuration", UNKNOWN)

 protected:
  ~HuhiRewardsUpdateMediaDurationFunction() override;

  ResponseAction Run() override;
};

class HuhiRewardsGetPublisherInfoFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.getPublisherInfo", UNKNOWN)

 protected:
  ~HuhiRewardsGetPublisherInfoFunction() override;

  ResponseAction Run() override;

 private:
  void OnGetPublisherInfo(
      const ledger::type::Result result,
      ledger::type::PublisherInfoPtr info);
};

class HuhiRewardsGetPublisherPanelInfoFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.getPublisherPanelInfo", UNKNOWN)

 protected:
  ~HuhiRewardsGetPublisherPanelInfoFunction() override;

  ResponseAction Run() override;

 private:
  void OnGetPublisherPanelInfo(
      const ledger::type::Result result,
      ledger::type::PublisherInfoPtr info);
};

class HuhiRewardsSavePublisherInfoFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.savePublisherInfo", UNKNOWN)

 protected:
  ~HuhiRewardsSavePublisherInfoFunction() override;

  ResponseAction Run() override;

 private:
  void OnSavePublisherInfo(const ledger::type::Result result);
};

class HuhiRewardsTipSiteFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.tipSite", UNKNOWN)

 protected:
  ~HuhiRewardsTipSiteFunction() override;

  ResponseAction Run() override;
};

class HuhiRewardsTipUserFunction : public ExtensionFunction {
 public:
  HuhiRewardsTipUserFunction();
  DECLARE_EXTENSION_FUNCTION("huhiRewards.tipUser", UNKNOWN)

 protected:
  ~HuhiRewardsTipUserFunction() override;

  ResponseAction Run() override;

 private:
  void OnTipUserStartProcess(
      const std::string& publisher_key,
      ledger::type::Result result);
  void OnTipUserGetPublisherInfo(
      const ledger::type::Result result,
      ledger::type::PublisherInfoPtr info);
  void OnTipUserSavePublisherInfo(const ledger::type::Result result);
  void ShowTipDialog();

  base::WeakPtrFactory<HuhiRewardsTipUserFunction> weak_factory_;
};

class HuhiRewardsGetPublisherDataFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.getPublisherData", UNKNOWN)

 protected:
  ~HuhiRewardsGetPublisherDataFunction() override;

  ResponseAction Run() override;
};

class HuhiRewardsGetRewardsParametersFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.getRewardsParameters", UNKNOWN)

 protected:
  ~HuhiRewardsGetRewardsParametersFunction() override;

  ResponseAction Run() override;

 private:
  void OnGet(ledger::type::RewardsParametersPtr parameters);
};

class HuhiRewardsGetBalanceReportFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.getBalanceReport", UNKNOWN)

 protected:
  ~HuhiRewardsGetBalanceReportFunction() override;

  ResponseAction Run() override;

 private:
  void OnBalanceReport(
      const ledger::type::Result result,
      ledger::type::BalanceReportInfoPtr report);
};

class HuhiRewardsIncludeInAutoContributionFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.includeInAutoContribution", UNKNOWN)

 protected:
  ~HuhiRewardsIncludeInAutoContributionFunction() override;

  ResponseAction Run() override;
};

class HuhiRewardsFetchPromotionsFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.fetchPromotions", UNKNOWN)

 protected:
  ~HuhiRewardsFetchPromotionsFunction() override;

  ResponseAction Run() override;
};

class HuhiRewardsClaimPromotionFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.claimPromotion", UNKNOWN)

 protected:
  ~HuhiRewardsClaimPromotionFunction() override;

  ResponseAction Run() override;

 private:
  void OnClaimPromotion(
      const std::string& promotion_id,
      const ledger::type::Result result,
      const std::string& captcha_image,
      const std::string& hint,
      const std::string& captcha_id);
};

class HuhiRewardsAttestPromotionFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.attestPromotion", UNKNOWN)

 protected:
  ~HuhiRewardsAttestPromotionFunction() override;

  ResponseAction Run() override;

 private:
  void OnAttestPromotion(
      const std::string& promotion_id,
      const ledger::type::Result result,
      ledger::type::PromotionPtr promotion);
};

class HuhiRewardsGetPendingContributionsTotalFunction
    : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION(
      "huhiRewards.getPendingContributionsTotal", UNKNOWN)

 protected:
  ~HuhiRewardsGetPendingContributionsTotalFunction() override;

  ResponseAction Run() override;

 private:
  void OnGetPendingTotal(double amount);
};

class HuhiRewardsSaveAdsSettingFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.saveAdsSetting", UNKNOWN)

 protected:
  ~HuhiRewardsSaveAdsSettingFunction() override;

  ResponseAction Run() override;
};

class HuhiRewardsSetAutoContributeEnabledFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.setAutoContributeEnabled", UNKNOWN)

 protected:
  ~HuhiRewardsSetAutoContributeEnabledFunction() override;

  ResponseAction Run() override;
};

class HuhiRewardsGetACEnabledFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.getACEnabled", UNKNOWN)

 protected:
  ~HuhiRewardsGetACEnabledFunction() override;

  ResponseAction Run() override;

 private:
  void OnGetACEnabled(bool enabled);
};

class HuhiRewardsSaveRecurringTipFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.saveRecurringTip", UNKNOWN)

 protected:
  ~HuhiRewardsSaveRecurringTipFunction() override;

  ResponseAction Run() override;

 private:
  void OnSaveRecurringTip(bool success);
};

class HuhiRewardsRemoveRecurringTipFunction :
  public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.removeRecurringTip", UNKNOWN)

 protected:
  ~HuhiRewardsRemoveRecurringTipFunction() override;

  ResponseAction Run() override;
};

class HuhiRewardsGetRecurringTipsFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.getRecurringTips", UNKNOWN)

 protected:
  ~HuhiRewardsGetRecurringTipsFunction() override;

  ResponseAction Run() override;

 private:
    void OnGetRecurringTips(ledger::type::PublisherInfoList list);
};

class HuhiRewardsGetPublisherBannerFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION(
      "huhiRewards.getPublisherBanner", UNKNOWN)

 protected:
  ~HuhiRewardsGetPublisherBannerFunction() override;

  ResponseAction Run() override;

 private:
  void OnPublisherBanner(ledger::type::PublisherBannerPtr banner);
};

class HuhiRewardsRefreshPublisherFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.refreshPublisher", UNKNOWN)

 protected:
  ~HuhiRewardsRefreshPublisherFunction() override;

  ResponseAction Run() override;

 private:
  void OnRefreshPublisher(
      const ledger::type::PublisherStatus status,
      const std::string& publisher_key);
};

class HuhiRewardsGetAllNotificationsFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.getAllNotifications", UNKNOWN)

 protected:
  ~HuhiRewardsGetAllNotificationsFunction() override;

  ResponseAction Run() override;
};

class HuhiRewardsGetInlineTippingPlatformEnabledFunction :
    public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION(
      "huhiRewards.getInlineTippingPlatformEnabled",
      UNKNOWN)

 protected:
  ~HuhiRewardsGetInlineTippingPlatformEnabledFunction() override;

  ResponseAction Run() override;

 private:
  void OnInlineTipSetting(bool value);
};

class HuhiRewardsFetchBalanceFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.fetchBalance", UNKNOWN)

 protected:
  ~HuhiRewardsFetchBalanceFunction() override;

  ResponseAction Run() override;

 private:
  void OnBalance(
      const ledger::type::Result result,
      ledger::type::BalancePtr balance);
};

class HuhiRewardsGetExternalWalletFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.getExternalWallet", UNKNOWN)

 protected:
  ~HuhiRewardsGetExternalWalletFunction() override;

  ResponseAction Run() override;

 private:
  void OnGetUpholdWallet(
      const ledger::type::Result result,
      ledger::type::UpholdWalletPtr wallet);
};

class HuhiRewardsDisconnectWalletFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.disconnectWallet", UNKNOWN)

 protected:
  ~HuhiRewardsDisconnectWalletFunction() override;

  ResponseAction Run() override;
};

class HuhiRewardsOnlyAnonWalletFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.onlyAnonWallet", UNKNOWN)

 protected:
  ~HuhiRewardsOnlyAnonWalletFunction() override;

  ResponseAction Run() override;
};

class HuhiRewardsGetAdsEnabledFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.getAdsEnabled", UNKNOWN)

 protected:
  ~HuhiRewardsGetAdsEnabledFunction() override;

  ResponseAction Run() override;
};

class HuhiRewardsGetAdsEstimatedEarningsFunction
    : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.getAdsEstimatedEarnings", UNKNOWN)

 protected:
  ~HuhiRewardsGetAdsEstimatedEarningsFunction() override;

  ResponseAction Run() override;

 private:
  void OnAdsEstimatedEarnings(
      const bool success,
      const double estimated_pending_rewards,
      const uint64_t next_payment_date_in_seconds,
      const uint64_t ad_notifications_received_this_month);
};

class HuhiRewardsGetAdsSupportedFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.getAdsSupported", UNKNOWN)

 protected:
  ~HuhiRewardsGetAdsSupportedFunction() override;

  ResponseAction Run() override;
};

class HuhiRewardsGetAnonWalletStatusFunction
    : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.getAnonWalletStatus", UNKNOWN)

 protected:
  ~HuhiRewardsGetAnonWalletStatusFunction() override;

  ResponseAction Run() override;

 private:
  void OnGetAnonWalletStatus(const ledger::type::Result result);
};

class HuhiRewardsIsInitializedFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.isInitialized", UNKNOWN)

 protected:
  ~HuhiRewardsIsInitializedFunction() override;

  ResponseAction Run() override;
};

class HuhiRewardsShouldShowOnboardingFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.shouldShowOnboarding", UNKNOWN)

 protected:
  ~HuhiRewardsShouldShowOnboardingFunction() override;

  ResponseAction Run() override;
};

class HuhiRewardsSaveOnboardingResultFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.saveOnboardingResult", UNKNOWN)

 protected:
  ~HuhiRewardsSaveOnboardingResultFunction() override;

  ResponseAction Run() override;
};

}  // namespace api
}  // namespace extensions

#endif  // HUHI_BROWSER_EXTENSIONS_API_HUHI_REWARDS_API_H_
