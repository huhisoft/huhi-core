// Copyright 2020 The Huhi Software Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Huhi Software
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#include "huhi/components/huhi_ads/browser/ads_notification_handler.h"

#define HUHI_ADD_HUHI_ADS_NOTIFICATION_HANDLER \
  AddNotificationHandler(                        \
      NotificationHandler::Type::HUHI_ADS,      \
      std::make_unique<huhi_ads::AdsNotificationHandler>(profile));
#include "../../../../../chrome/browser/notifications/notification_display_service_impl.cc"
#undef HUHI_ADD_HUHI_ADS_NOTIFICATION_HANDLER
