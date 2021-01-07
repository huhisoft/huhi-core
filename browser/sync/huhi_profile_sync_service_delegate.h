/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_SYNC_HUHI_PROFILE_SYNC_SERVICE_DELEGATE_H_
#define HUHI_BROWSER_SYNC_HUHI_PROFILE_SYNC_SERVICE_DELEGATE_H_

#include "huhi/components/sync/driver/profile_sync_service_delegate.h"

#include "base/memory/weak_ptr.h"
#include "base/scoped_observer.h"
#include "components/sync/driver/profile_sync_service.h"
#include "components/sync_device_info/device_info_tracker.h"

class Profile;

namespace syncer {

class DeviceInfoTracker;
class LocalDeviceInfoProvider;

// Helper class to prevent pass of profile pointer into HuhiProfileSyncService
// and to keep DeviceInfoSyncService
class HuhiProfileSyncServiceDelegate
    : public ProfileSyncServiceDelegate,
      public syncer::DeviceInfoTracker::Observer {
 public:
  explicit HuhiProfileSyncServiceDelegate(Profile* profile);
  ~HuhiProfileSyncServiceDelegate() override;

  void SuspendDeviceObserverForOwnReset() override;
  void ResumeDeviceObserver() override;

 private:
  // syncer::DeviceInfoTracker::Observer:
  void OnDeviceInfoChange() override;

  void OnSelfDeviceInfoDeleted(void);

  syncer::DeviceInfoTracker* device_info_tracker_;
  syncer::LocalDeviceInfoProvider* local_device_info_provider_;
  ScopedObserver<syncer::DeviceInfoTracker, syncer::DeviceInfoTracker::Observer>
      device_info_observer_{this};

  DeviceInfoSyncService* device_info_sync_service_;
  Profile* profile_;

  base::WeakPtrFactory<HuhiProfileSyncServiceDelegate> weak_ptr_factory_;

  HuhiProfileSyncServiceDelegate(const HuhiProfileSyncServiceDelegate&) =
      delete;
  HuhiProfileSyncServiceDelegate& operator=(
      const HuhiProfileSyncServiceDelegate&) = delete;
};

}  // namespace syncer

#endif  // HUHI_BROWSER_SYNC_HUHI_PROFILE_SYNC_SERVICE_DELEGATE_H_
