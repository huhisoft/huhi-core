/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_ADS_BROWSER_NOTIFICATION_HELPER_ANDROID_H_
#define HUHI_COMPONENTS_HUHI_ADS_BROWSER_NOTIFICATION_HELPER_ANDROID_H_

#include <memory>

#include "base/memory/weak_ptr.h"

#include "huhi/components/huhi_ads/browser/notification_helper.h"

namespace huhi_ads {

class NotificationHelperAndroid
    : public NotificationHelper,
      public base::SupportsWeakPtr<NotificationHelperAndroid> {
 public:
  NotificationHelperAndroid(const NotificationHelperAndroid&) = delete;
  NotificationHelperAndroid& operator=(
      const NotificationHelperAndroid&) = delete;

  static NotificationHelperAndroid* GetInstanceImpl();

 private:
  friend struct base::DefaultSingletonTraits<NotificationHelperAndroid>;

  NotificationHelperAndroid();
  ~NotificationHelperAndroid() override;

  // |foreground_channel|: foreground or background channel
  bool IsHuhiAdsNotificationChannelEnabled(bool foreground_channel) const;

  int GetOperatingSystemVersion() const;

  // NotificationHelper impl
  bool ShouldShowNotifications() override;

  bool ShowMyFirstAdNotification() override;

  bool CanShowBackgroundNotifications() const override;
};

}  // namespace huhi_ads

#endif  // HUHI_COMPONENTS_HUHI_ADS_BROWSER_NOTIFICATION_HELPER_ANDROID_H_
