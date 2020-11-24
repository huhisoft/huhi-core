/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_TEST_COMMON_REWARDS_BROWSERTEST_CONTRIBUTION_H_
#define HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_TEST_COMMON_REWARDS_BROWSERTEST_CONTRIBUTION_H_

#include <memory>
#include <string>
#include <vector>

#include "base/run_loop.h"
#include "bat/ledger/mojom_structs.h"
#include "huhi/components/huhi_rewards/browser/rewards_service_impl.h"
#include "huhi/components/huhi_rewards/browser/rewards_service_observer.h"
#include "huhi/components/huhi_rewards/browser/test/common/rewards_browsertest_util.h"
#include "chrome/browser/ui/browser.h"

namespace rewards_browsertest {

class RewardsBrowserTestContribution
    : public huhi_rewards::RewardsServiceObserver {
 public:
  RewardsBrowserTestContribution();
  ~RewardsBrowserTestContribution() override;

  void Initialize(
      Browser* browser,
      huhi_rewards::RewardsServiceImpl* rewards_service);

  void TipViaCode(
      const std::string& publisher_key,
      const double amount,
      const ledger::type::PublisherStatus status,
      const int32_t number_of_contributions = 0,
      const bool recurring = false);

  void TipPublisher(
      const GURL& url,
      rewards_browsertest_util::ContributionType type,
      const int32_t number_of_contributions = 0,
      const int32_t selection = 0);

  void VerifyTip(
      const double amount,
      const bool should_contribute,
      const bool monthly,
      const bool via_code = false);

  void AddBalance(const double balance);

  double GetBalance();

  std::string GetExternalBalance();

  double GetReconcileTipTotal();

  void WaitForTipReconcileCompleted();

  void UpdateContributionBalance(
      const double amount,
      const bool verified = false,
      const ledger::type::ContributionProcessor processor =
          ledger::type::ContributionProcessor::HUHI_TOKENS);

  void WaitForMultipleTipReconcileCompleted(const int32_t needed);

  void WaitForACReconcileCompleted();

  void IsBalanceCorrect();

  void IsPendingBalanceCorrect();

  void WaitForMultipleACReconcileCompleted(
    const int32_t needed);

  ledger::type::Result GetACStatus();

  std::vector<ledger::type::Result> GetMultipleACStatus();

  void SetUpUpholdWallet(
    const double balance,
    const ledger::type::WalletStatus status =
        ledger::type::WalletStatus::VERIFIED);

  std::vector<ledger::type::Result> GetMultipleTipStatus();

  ledger::type::Result GetTipStatus();

 private:
  content::WebContents* contents();

  void WaitForPendingTipToBeSaved();

  void OnPendingContributionSaved(
      huhi_rewards::RewardsService* rewards_service,
      const ledger::type::Result result) override;

  void OnReconcileComplete(
      huhi_rewards::RewardsService* rewards_service,
      const ledger::type::Result result,
      const std::string& contribution_id,
      const double amount,
      const ledger::type::RewardsType type,
      const ledger::type::ContributionProcessor processor) override;

  void WaitForRecurringTipToBeSaved();

  void OnRecurringTipSaved(
      huhi_rewards::RewardsService* rewards_service,
      const bool success) override;

  std::string GetStringBalance();

  std::string GetStringPendingBalance();

  double balance_ = 0;
  double external_balance_ = 0;
  double pending_balance_ = 0;
  double reconciled_tip_total_ = 0;

  bool tip_reconcile_completed_ = false;
  std::unique_ptr<base::RunLoop> wait_for_tip_completed_loop_;
  ledger::type::Result tip_reconcile_status_ =
      ledger::type::Result::LEDGER_ERROR;
  bool pending_tip_saved_ = false;
  std::unique_ptr<base::RunLoop> wait_for_pending_tip_saved_loop_;
  bool recurring_tip_saved_ = false;
  std::unique_ptr<base::RunLoop> wait_for_recurring_tip_saved_loop_;
  bool multiple_tip_reconcile_completed_ = false;
  std::unique_ptr<base::RunLoop> wait_for_multiple_tip_completed_loop_;
  int32_t multiple_tip_reconcile_count_ = 0;
  int32_t multiple_tip_reconcile_needed_ = 0;
  std::vector<ledger::type::Result> multiple_tip_reconcile_status_ = {};
  bool multiple_ac_reconcile_completed_ = false;
  std::unique_ptr<base::RunLoop> wait_for_multiple_ac_completed_loop_;
  int32_t multiple_ac_reconcile_count_ = 0;
  int32_t multiple_ac_reconcile_needed_ = 0;
  std::vector<ledger::type::Result> multiple_ac_reconcile_status_ = {};
  bool ac_reconcile_completed_ = false;
  std::unique_ptr<base::RunLoop> wait_for_ac_completed_loop_;
  ledger::type::Result ac_reconcile_status_ =
      ledger::type::Result::LEDGER_ERROR;

  Browser* browser_;  // NOT OWNED
  huhi_rewards::RewardsServiceImpl* rewards_service_;  // NOT OWNED
};

}  // namespace rewards_browsertest
#endif  // HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_TEST_COMMON_REWARDS_BROWSERTEST_CONTRIBUTION_H_