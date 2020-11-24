/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BAT_ADS_INTERNAL_AD_EVENTS_AD_NOTIFICATION_EVENT_TIMED_OUT_H_
#define BAT_ADS_INTERNAL_AD_EVENTS_AD_NOTIFICATION_EVENT_TIMED_OUT_H_

#include "bat/ads/ad_notification_info.h"
#include "bat/ads/internal/ad_events/ad_event.h"

namespace ads {

class AdsImpl;

class AdNotificationEventTimedOut : public AdEvent<AdNotificationInfo> {
 public:
  AdNotificationEventTimedOut(
      AdsImpl* ads);

  ~AdNotificationEventTimedOut() override;

  void Trigger(
      const AdNotificationInfo& ad_notification) override;

 private:
  AdsImpl* ads_;  // NOT OWNED
};

}  // namespace ads

#endif  // BAT_ADS_INTERNAL_AD_EVENTS_AD_NOTIFICATION_EVENT_TIMED_OUT_H_
