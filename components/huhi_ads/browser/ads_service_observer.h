/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_ADS_BROWSER_ADS_SERVICE_OBSERVER_H_
#define HUHI_COMPONENTS_HUHI_ADS_BROWSER_ADS_SERVICE_OBSERVER_H_

#include "base/observer_list.h"

namespace huhi_ads {

class AdsServiceObserver : public base::CheckedObserver {
 public:
  virtual void OnAdRewardsChanged() = 0;

 protected:
  ~AdsServiceObserver() override = default;
};

}  // namespace huhi_ads

#endif  // HUHI_COMPONENTS_HUHI_ADS_BROWSER_ADS_SERVICE_OBSERVER_H_
