/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/components/huhi_ads/browser/notification_helper_linux.h"

#include "base/logging.h"
#include "chrome/browser/fullscreen.h"

namespace huhi_ads {

NotificationHelperLinux::NotificationHelperLinux() = default;

NotificationHelperLinux::~NotificationHelperLinux() = default;

bool NotificationHelperLinux::ShouldShowNotifications() {
  if (IsFullScreenMode()) {
    LOG(WARNING) << "Notification not made: Full screen mode";
    return false;
  }

  // TODO(https://github.com/huhisoft/huhi-browser/issues/5542): Investigate how
  // we can detect if notifications are enabled within the Linux operating
  // system

  return true;
}

bool NotificationHelperLinux::ShowMyFirstAdNotification() {
  return false;
}

bool NotificationHelperLinux::CanShowBackgroundNotifications() const {
  return true;
}

NotificationHelperLinux* NotificationHelperLinux::GetInstanceImpl() {
  return base::Singleton<NotificationHelperLinux>::get();
}

NotificationHelper* NotificationHelper::GetInstanceImpl() {
  return NotificationHelperLinux::GetInstanceImpl();
}

}  // namespace huhi_ads
