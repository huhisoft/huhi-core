/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_REWARDS_SERVICE_OBSERVER_H_
#define HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_REWARDS_SERVICE_OBSERVER_H_

#include <memory>
#include <string>
#include <vector>

#include "base/observer_list_types.h"
#include "bat/ledger/mojom_structs.h"

namespace huhi_rewards {

class RewardsService;

class RewardsServiceObserver : public base::CheckedObserver {
 public:
  ~RewardsServiceObserver() override {}

  virtual void OnFetchPromotions(
      RewardsService* rewards_service,
      const ledger::type::Result result,
      const ledger::type::PromotionList& list) {}

  virtual void OnRecoverWallet(
      RewardsService* rewards_service,
      const ledger::type::Result result) {}

  virtual void OnPromotionFinished(
      RewardsService* rewards_service,
      const ledger::type::Result result,
      ledger::type::PromotionPtr promotion) {}

  virtual void OnExcludedSitesChanged(
      RewardsService* rewards_service,
      std::string publisher_id,
      bool excluded) {}

  virtual void OnReconcileComplete(
      RewardsService* rewards_service,
      const ledger::type::Result result,
      const std::string& contribution_id,
      const double amount,
      const ledger::type::RewardsType type,
      const ledger::type::ContributionProcessor processor) {}

  virtual void OnAdsEnabled(
      huhi_rewards::RewardsService* rewards_service,
      bool ads_enabled) {}

  virtual void OnPendingContributionSaved(
      huhi_rewards::RewardsService* rewards_service,
      const ledger::type::Result result) {}

  virtual void OnPublisherListNormalized(
      RewardsService* rewards_service,
      ledger::type::PublisherInfoList list) {}

  virtual void OnTransactionHistoryChanged(
      huhi_rewards::RewardsService* rewards_service) {}

  virtual void OnRecurringTipSaved(
      huhi_rewards::RewardsService* rewards_service,
      bool success) {}

  virtual void OnRecurringTipRemoved(
      huhi_rewards::RewardsService* rewards_service,
      bool success) {}

  virtual void OnPendingContributionRemoved(
      huhi_rewards::RewardsService* rewards_service,
      const ledger::type::Result result) {}

  virtual void OnDisconnectWallet(
      huhi_rewards::RewardsService* rewards_service,
      const ledger::type::Result result,
      const std::string& wallet_type) {}

  virtual void OnUnblindedTokensReady(
      huhi_rewards::RewardsService* rewards_service) {}

  virtual void ReconcileStampReset() {}

  virtual void OnCompleteReset(const bool success) {}

  // DO NOT ADD ANY MORE METHODS HERE UNLESS IT IS A BROADCAST NOTIFICATION
  // RewardsServiceObserver should not be used to return responses to the
  // caller. Method calls on RewardsService should use callbacks to return
  // responses. The observer is primarily for broadcast notifications of events
  // from the rewards service. OnPublisherInfoUpdated,
  // etc... are examples of events that all observers will be interested in.
};

}  // namespace huhi_rewards

#endif  // HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_REWARDS_SERVICE_OBSERVER_H_
