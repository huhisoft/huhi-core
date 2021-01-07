/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_ADS_BROWSER_NOTIFICATION_HELPER_H_
#define HUHI_COMPONENTS_HUHI_ADS_BROWSER_NOTIFICATION_HELPER_H_

#include "base/macros.h"
#include "base/memory/singleton.h"
#include "build/build_config.h"

namespace huhi_ads {

class NotificationHelper {
 public:
  NotificationHelper(const NotificationHelper&) = delete;
  NotificationHelper& operator=(const NotificationHelper&) = delete;

  static NotificationHelper* GetInstance();

  void set_for_testing(
      NotificationHelper* notification_helper);

  virtual bool ShouldShowNotifications();

  virtual bool ShowMyFirstAdNotification();

  virtual bool CanShowBackgroundNotifications() const;

 protected:
  friend struct base::DefaultSingletonTraits<NotificationHelper>;

  NotificationHelper();
  virtual ~NotificationHelper();

  static NotificationHelper* GetInstanceImpl();
};

}  // namespace huhi_ads

#endif  // HUHI_COMPONENTS_HUHI_ADS_BROWSER_NOTIFICATION_HELPER_H_
