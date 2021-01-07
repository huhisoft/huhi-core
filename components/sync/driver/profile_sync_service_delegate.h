/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_SYNC_DRIVER_PROFILE_SYNC_SERVICE_DELEGATE_H_
#define HUHI_COMPONENTS_SYNC_DRIVER_PROFILE_SYNC_SERVICE_DELEGATE_H_

namespace syncer {

class DeviceInfoSyncService;

class ProfileSyncServiceDelegate {
 public:
  virtual ~ProfileSyncServiceDelegate() {}
  virtual void SuspendDeviceObserverForOwnReset() = 0;
  virtual void ResumeDeviceObserver() = 0;
};

}  // namespace syncer

#endif  // HUHI_COMPONENTS_SYNC_DRIVER_PROFILE_SYNC_SERVICE_DELEGATE_H_
