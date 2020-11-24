/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BAT_ADS_INTERNAL_ELIGIBLE_ADS_ELIGIBLE_ADS_FILTER_H_
#define BAT_ADS_INTERNAL_ELIGIBLE_ADS_ELIGIBLE_ADS_FILTER_H_

#include "bat/ads/internal/bundle/creative_ad_notification_info.h"

namespace ads {

class EligibleAdsFilter {
 public:
  enum class Type {
    kPriority,
    kPacing
  };

  virtual ~EligibleAdsFilter() = default;

  virtual CreativeAdNotificationList Apply(
      const CreativeAdNotificationList& ads) const = 0;
};

}  // namespace ads

#endif  // BAT_ADS_INTERNAL_ELIGIBLE_ADS_ELIGIBLE_ADS_FILTER_H_
