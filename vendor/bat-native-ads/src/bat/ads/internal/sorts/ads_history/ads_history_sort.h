/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BAT_ADS_INTERNAL_SORTS_ADS_HISTORY_ADS_HISTORY_SORT_H_
#define BAT_ADS_INTERNAL_SORTS_ADS_HISTORY_ADS_HISTORY_SORT_H_

#include <deque>

#include "bat/ads/ad_history.h"

namespace ads {

class AdsHistorySort {
 public:
  virtual ~AdsHistorySort() = default;

  virtual std::deque<AdHistory> Apply(
      const std::deque<AdHistory>& history) const = 0;
};

}  // namespace ads

#endif  // BAT_ADS_INTERNAL_SORTS_ADS_HISTORY_SORT_H_
