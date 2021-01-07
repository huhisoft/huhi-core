/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BAT_ADS_INTERNAL_FREQUENCY_CAPPING_PERMISSION_RULES_ALLOW_NOTIFICATIONS_FREQUENCY_CAP_H_  // NOLINT
#define BAT_ADS_INTERNAL_FREQUENCY_CAPPING_PERMISSION_RULES_ALLOW_NOTIFICATIONS_FREQUENCY_CAP_H_  // NOLINT

#include <string>

#include "bat/ads/internal/frequency_capping/permission_rules/permission_rule.h"

namespace ads {

class AdsImpl;

class AllowNotificationsFrequencyCap : public PermissionRule {
 public:
  AllowNotificationsFrequencyCap(
      AdsImpl* ads);

  ~AllowNotificationsFrequencyCap() override;

  AllowNotificationsFrequencyCap(
      const AllowNotificationsFrequencyCap&) = delete;
  AllowNotificationsFrequencyCap& operator=(
      const AllowNotificationsFrequencyCap&) = delete;

  bool ShouldAllow() override;

  std::string get_last_message() const override;

 private:
  AdsImpl* ads_;  // NOT OWNED

  std::string last_message_;

  bool DoesRespectCap();
};

}  // namespace ads

#endif  // BAT_ADS_INTERNAL_FREQUENCY_CAPPING_PERMISSION_RULES_ALLOW_NOTIFICATIONS_FREQUENCY_CAP_H_  // NOLINT