/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/components/huhi_component_updater/browser/huhi_on_demand_updater.h"

#include <string>

#include "base/memory/singleton.h"

namespace huhi_component_updater {

HuhiOnDemandUpdater* HuhiOnDemandUpdater::GetInstance() {
  return base::Singleton<HuhiOnDemandUpdater>::get();
}

HuhiOnDemandUpdater::HuhiOnDemandUpdater() {}

HuhiOnDemandUpdater::~HuhiOnDemandUpdater() {}

void HuhiOnDemandUpdater::OnDemandUpdate(const std::string& id) {
  DCHECK(!on_demand_update_callback_.is_null());
  on_demand_update_callback_.Run(id);
}

void HuhiOnDemandUpdater::RegisterOnDemandUpdateCallback(Callback callback) {
  on_demand_update_callback_ = callback;
}


}  // namespace huhi_component_updater
