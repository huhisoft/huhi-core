/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_NOTIFICATIONS_HUHI_NOTIFICATION_PLATFORM_BRIDGE_H_
#define HUHI_BROWSER_NOTIFICATIONS_HUHI_NOTIFICATION_PLATFORM_BRIDGE_H_

#include <memory>

#include "base/macros.h"

class NotificationPlatformBridge;

class HuhiNotificationPlatformBridge {
 public:
  static std::unique_ptr<NotificationPlatformBridge> Create();

 private:
  HuhiNotificationPlatformBridge() = default;
  ~HuhiNotificationPlatformBridge() = default;

  DISALLOW_COPY_AND_ASSIGN(HuhiNotificationPlatformBridge);
};

#endif  // HUHI_BROWSER_NOTIFICATIONS_HUHI_NOTIFICATION_PLATFORM_BRIDGE_H_
