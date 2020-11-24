/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_GCM_DRIVER_HUHI_GCM_CHANNEL_STATUS_H_
#define HUHI_BROWSER_GCM_DRIVER_HUHI_GCM_CHANNEL_STATUS_H_

#include "base/supports_user_data.h"

class Profile;

namespace gcm {

class HuhiGCMChannelStatus : public base::SupportsUserData::Data {
 public:
  explicit HuhiGCMChannelStatus(Profile* profile, bool enabled);
  static HuhiGCMChannelStatus* GetForProfile(Profile *profile);

  bool IsGCMEnabled() const;
  void UpdateGCMDriverStatus();

 private:
  Profile* profile_;
  bool gcm_enabled_;
};

}  // namespace gcm

#endif  // HUHI_BROWSER_GCM_DRIVER_HUHI_GCM_CHANNEL_STATUS_H_
