/* Copyright (c) 2019 The Huhi Software Team. Distributed under the MPL2
 * license. This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_NOTIFICATIONS_HUHI_ALERT_DISPATCHER_MAC_H_
#define HUHI_BROWSER_NOTIFICATIONS_HUHI_ALERT_DISPATCHER_MAC_H_

#import <Foundation/Foundation.h>

#include <string>

#include "chrome/browser/notifications/alert_dispatcher_mac.h"

@interface HuhiAlertDispatcherMac : NSObject<AlertDispatcher>

- (void)dispatchNotification:(NSDictionary *)data;                               // NOLINT

- (void)closeNotificationWithId:(NSString *)notificationId                       // NOLINT
                  withProfileId:(NSString *)profileId;                           // NOLINT

- (void)closeAllNotifications;

- (void)
getDisplayedAlertsForProfileId:(NSString *)profileId                             // NOLINT
                     incognito:(BOOL)incognito
            notificationCenter:(NSUserNotificationCenter *)notificationCenter    // NOLINT
                      callback:(GetDisplayedNotificationsCallback)callback;      // NOLINT

@end

#endif  // HUHI_BROWSER_NOTIFICATIONS_HUHI_ALERT_DISPATCHER_MAC_H_
