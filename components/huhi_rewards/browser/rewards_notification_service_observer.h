/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_REWARDS_NOTIFICATION_SERVICE_OBSERVER_
#define HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_REWARDS_NOTIFICATION_SERVICE_OBSERVER_

#include "base/observer_list_types.h"
#include "huhi/components/huhi_rewards/browser/rewards_notification_service.h"

namespace huhi_rewards {

class RewardsNotificationService;

class RewardsNotificationServiceObserver : public base::CheckedObserver {
 public:
  ~RewardsNotificationServiceObserver() override {}

  virtual void OnNotificationAdded(
      RewardsNotificationService* rewards_notification_service,
      const RewardsNotificationService::RewardsNotification& notification) {}
  virtual void OnNotificationDeleted(
      RewardsNotificationService* rewards_notification_service,
      const RewardsNotificationService::RewardsNotification& notification) {}
  virtual void OnAllNotificationsDeleted(
      RewardsNotificationService* rewards_notification_service) {}
  virtual void OnGetNotification(
      RewardsNotificationService* rewards_notification_service,
      const RewardsNotificationService::RewardsNotification& notification) {}
  virtual void OnGetAllNotifications(
      RewardsNotificationService* rewards_notification_service,
      const RewardsNotificationService::RewardsNotificationsList&
          notifications_list) {}
};

}  // namespace huhi_rewards

#endif  // HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_REWARDS_NOTIFICATION_SERVICE_OBSERVER_
