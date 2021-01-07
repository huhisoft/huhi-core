/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_REWARDS_SERVICE_PRIVATE_OBSERVER_H_
#define HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_REWARDS_SERVICE_PRIVATE_OBSERVER_H_

#include "base/observer_list_types.h"
#include "bat/ledger/mojom_structs.h"

namespace huhi_rewards {

class RewardsService;

class RewardsServicePrivateObserver : public base::CheckedObserver {
 public:
  ~RewardsServicePrivateObserver() override {}

  virtual void OnPanelPublisherInfo(
      RewardsService* rewards_service,
      const ledger::type::Result result,
      const ledger::type::PublisherInfo* info,
      uint64_t windowId) {}
};

}  // namespace huhi_rewards

#endif  // HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_REWARDS_SERVICE_PRIVATE_OBSERVER_H_
