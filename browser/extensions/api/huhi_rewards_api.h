/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
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

class HuhiRewardsCreateWalletFunction : public ExtensionFunction {
 public:
  HuhiRewardsCreateWalletFunction();
  DECLARE_EXTENSION_FUNCTION("huhiRewards.createWallet", UNKNOWN)

 protected:
  ~HuhiRewardsCreateWalletFunction() override;

  ResponseAction Run() override;
 private:
  base::WeakPtrFactory<HuhiRewardsCreateWalletFunction> weak_factory_;
  void OnCreateWallet(const ledger::type::Result result);
};

class HuhiRewardsOpenBrowserActionUIFunction :
    public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.openBrowserActionUI", UNKNOWN)

 protected:
  ~HuhiRewardsOpenBrowserActionUIFunction() override;

  ResponseAction Run() override;
};

class HuhiRewardsTipSiteFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.tipSite", UNKNOWN)

 protected:
  ~HuhiRewardsTipSiteFunction() override;

  ResponseAction Run() override;
};

class HuhiRewardsTipTwitterUserFunction
    : public ExtensionFunction {
 public:
  HuhiRewardsTipTwitterUserFunction();
  DECLARE_EXTENSION_FUNCTION("huhiRewards.tipTwitterUser", UNKNOWN)

 protected:
  ~HuhiRewardsTipTwitterUserFunction() override;

  ResponseAction Run() override;

 private:
  base::WeakPtrFactory<HuhiRewardsTipTwitterUserFunction> weak_factory_;
  void OnTwitterPublisherInfoSaved(ledger::type::PublisherInfoPtr publisher);
};

class HuhiRewardsTipGitHubUserFunction : public ExtensionFunction {
 public:
  HuhiRewardsTipGitHubUserFunction();
  DECLARE_EXTENSION_FUNCTION("huhiRewards.tipGitHubUser", UNKNOWN)

 protected:
  ~HuhiRewardsTipGitHubUserFunction() override;

  ResponseAction Run() override;
 private:
  base::WeakPtrFactory<HuhiRewardsTipGitHubUserFunction> weak_factory_;
  void OnGitHubPublisherInfoSaved(ledger::type::PublisherInfoPtr publisher);
};

class HuhiRewardsTipRedditUserFunction : public ExtensionFunction {
 public:
  HuhiRewardsTipRedditUserFunction();
  DECLARE_EXTENSION_FUNCTION("huhiRewards.tipRedditUser", UNKNOWN)

 protected:
  ~HuhiRewardsTipRedditUserFunction() override;

  ResponseAction Run() override;
 private:
  base::WeakPtrFactory<HuhiRewardsTipRedditUserFunction> weak_factory_;
  void OnRedditPublisherInfoSaved(ledger::type::PublisherInfoPtr publisher);
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

class HuhiRewardsGetRewardsMainEnabledFunction
    : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.getRewardsMainEnabled", UNKNOWN)

 protected:
  ~HuhiRewardsGetRewardsMainEnabledFunction() override;

  ResponseAction Run() override;

 private:
  void OnGetRewardsMainEnabled(bool enabled);
};

class HuhiRewardsSaveAdsSettingFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.saveAdsSetting", UNKNOWN)

 protected:
  ~HuhiRewardsSaveAdsSettingFunction() override;

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

class HuhiRewardsSaveSettingFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.saveSetting", UNKNOWN)

 protected:
  ~HuhiRewardsSaveSettingFunction() override;

  ResponseAction Run() override;
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
  void OnExternalWalet(
      const ledger::type::Result result,
      ledger::type::ExternalWalletPtr wallet);
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

class HuhiRewardsGetWalletExistsFunction
    : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiRewards.getWalletExists", UNKNOWN)

 protected:
  ~HuhiRewardsGetWalletExistsFunction() override;

  ResponseAction Run() override;

 private:
  void OnGetWalletExists(const bool exists);
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

}  // namespace api
}  // namespace extensions

#endif  // HUHI_BROWSER_EXTENSIONS_API_HUHI_REWARDS_API_H_
