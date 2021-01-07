/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_SYNC_DRIVER_HUHI_SYNC_PROFILE_SYNC_SERVICE_H_
#define HUHI_COMPONENTS_SYNC_DRIVER_HUHI_SYNC_PROFILE_SYNC_SERVICE_H_

#include <memory>
#include <string>

#include "base/memory/weak_ptr.h"
#include "huhi/components/huhi_sync/huhi_sync_prefs.h"
#include "components/prefs/pref_change_registrar.h"
#include "components/sync/driver/profile_sync_service.h"

class Profile;

namespace syncer {

class HuhiSyncAuthManager;
class ProfileSyncServiceDelegate;

class HuhiProfileSyncService : public ProfileSyncService {
 public:
  explicit HuhiProfileSyncService(
      InitParams init_params,
      std::unique_ptr<ProfileSyncServiceDelegate> profile_service_delegate);
  ~HuhiProfileSyncService() override;

  // SyncService implementation
  bool IsSetupInProgress() const override;

  std::string GetOrCreateSyncCode();
  bool SetSyncCode(const std::string& sync_code);

  // This should only be called by helper function, huhi_sync::ResetSync, or by
  // OnDeviceInfoChange internally
  void OnSelfDeviceInfoDeleted(base::OnceClosure cb);

  // These functions are for disabling device_info_observer_ from firing
  // when the device is doing own reset sync operation, to prevent early call
  // of StopAndClear prior to device sends delete record
  void SuspendDeviceObserverForOwnReset();
  void ResumeDeviceObserver();

 private:
  HuhiSyncAuthManager* GetHuhiSyncAuthManager();

  void OnHuhiSyncPrefsChanged(const std::string& path);

  huhi_sync::Prefs huhi_sync_prefs_;

  PrefChangeRegistrar huhi_sync_prefs_change_registrar_;

  std::unique_ptr<ProfileSyncServiceDelegate> profile_service_delegate_;

  base::WeakPtrFactory<HuhiProfileSyncService> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(HuhiProfileSyncService);
};
}  // namespace syncer

#endif  // HUHI_COMPONENTS_SYNC_DRIVER_HUHI_SYNC_PROFILE_SYNC_SERVICE_H_
