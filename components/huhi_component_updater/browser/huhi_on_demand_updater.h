/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_COMPONENT_UPDATER_BROWSER_HUHI_ON_DEMAND_UPDATER_H_
#define HUHI_COMPONENTS_HUHI_COMPONENT_UPDATER_BROWSER_HUHI_ON_DEMAND_UPDATER_H_

#include <string>

#include "base/callback.h"
#include "base/macros.h"

namespace base {
template <typename T>
struct DefaultSingletonTraits;
}  // namespace base

namespace huhi_component_updater {

class HuhiOnDemandUpdater {
 public:
  using Callback = base::RepeatingCallback<void(const std::string&)>;
  static HuhiOnDemandUpdater* GetInstance();

  ~HuhiOnDemandUpdater();
  void OnDemandUpdate(const std::string& id);

  void RegisterOnDemandUpdateCallback(Callback callback);

 private:
  friend struct base::DefaultSingletonTraits<HuhiOnDemandUpdater>;
  HuhiOnDemandUpdater();

  Callback on_demand_update_callback_;

  DISALLOW_COPY_AND_ASSIGN(HuhiOnDemandUpdater);
};

}  // namespace huhi_component_updater

#endif  // HUHI_COMPONENTS_HUHI_COMPONENT_UPDATER_BROWSER_HUHI_ON_DEMAND_UPDATER_H_
