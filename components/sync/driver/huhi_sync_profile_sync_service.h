/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_SYNC_DRIVER_HUHI_SYNC_PROFILE_SYNC_SERVICE_H_
#define HUHI_COMPONENTS_SYNC_DRIVER_HUHI_SYNC_PROFILE_SYNC_SERVICE_H_

#include <string>

#include "base/callback.h"
#include "base/memory/weak_ptr.h"
#include "huhi/components/huhi_sync/huhi_sync_prefs.h"
#include "components/prefs/pref_change_registrar.h"
#include "components/sync/driver/profile_sync_service.h"

namespace syncer {

class HuhiSyncAuthManager;
class DeviceInfoSyncService;

class HuhiProfileSyncService : public ProfileSyncService {
 public:
  explicit HuhiProfileSyncService(InitParams init_params);
  ~HuhiProfileSyncService() override;

  // SyncService implementation
  bool IsSetupInProgress() const override;

  std::string GetOrCreateSyncCode();
  bool SetSyncCode(const std::string& sync_code);
  void ResetSync(DeviceInfoSyncService* device_info_service,
                 base::OnceClosure cb);

 private:
  HuhiSyncAuthManager* GetHuhiSyncAuthManager();

  void OnHuhiSyncPrefsChanged(const std::string& path);

  void OnSelfDeleted(base::OnceClosure cb);

  huhi_sync::Prefs huhi_sync_prefs_;

  PrefChangeRegistrar huhi_sync_prefs_change_registrar_;

  base::WeakPtrFactory<HuhiProfileSyncService> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(HuhiProfileSyncService);
};
}  // namespace syncer

#endif  // HUHI_COMPONENTS_SYNC_DRIVER_HUHI_SYNC_PROFILE_SYNC_SERVICE_H_
