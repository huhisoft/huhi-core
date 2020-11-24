/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_ADS_BROWSER_NOTIFICATION_HELPER_MOCK_H_
#define HUHI_COMPONENTS_HUHI_ADS_BROWSER_NOTIFICATION_HELPER_MOCK_H_

#include "huhi/components/huhi_ads/browser/notification_helper.h"

#include "testing/gmock/include/gmock/gmock.h"

namespace huhi_ads {

class NotificationHelperMock : public NotificationHelper {
 public:
  NotificationHelperMock();
  ~NotificationHelperMock() override;

  NotificationHelperMock(const NotificationHelperMock&) = delete;
  NotificationHelperMock& operator=(const NotificationHelperMock&) = delete;

  MOCK_METHOD0(ShouldShowNotifications, bool());
  MOCK_METHOD0(ShowMyFirstAdNotification, bool());
  MOCK_CONST_METHOD0(CanShowBackgroundNotifications, bool());
};

}  // namespace huhi_ads

#endif  // HUHI_COMPONENTS_HUHI_ADS_BROWSER_NOTIFICATION_HELPER_MOCK_H_
