/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/components/sync/driver/huhi_sync_profile_sync_service.h"

#include <utility>
#include <vector>

#include "base/logging.h"
#include "huhi/components/huhi_sync/crypto/crypto.h"
#include "huhi/components/sync/driver/huhi_sync_auth_manager.h"
#include "components/prefs/pref_service.h"
#include "components/sync_device_info/device_info_sync_service.h"
#include "components/sync_device_info/device_info_tracker.h"
#include "components/sync_device_info/local_device_info_provider.h"

namespace syncer {

class DeviceInfo;

HuhiProfileSyncService::HuhiProfileSyncService(InitParams init_params)
    : ProfileSyncService(std::move(init_params)),
      huhi_sync_prefs_(sync_client_->GetPrefService()),
      weak_ptr_factory_(this) {
  huhi_sync_prefs_change_registrar_.Init(sync_client_->GetPrefService());
  huhi_sync_prefs_change_registrar_.Add(
      huhi_sync::Prefs::GetSeedPath(),
      base::Bind(&HuhiProfileSyncService::OnHuhiSyncPrefsChanged,
                 base::Unretained(this)));
  GetHuhiSyncAuthManager()->DeriveSigningKeys(huhi_sync_prefs_.GetSeed());
  if (!huhi_sync_prefs_.IsSyncV1Migrated()) {
    StopImpl(CLEAR_DATA);
    huhi_sync_prefs_.SetSyncV1Migrated(true);
  }
}

HuhiProfileSyncService::~HuhiProfileSyncService() {
  huhi_sync_prefs_change_registrar_.RemoveAll();
}

bool HuhiProfileSyncService::IsSetupInProgress() const {
  return ProfileSyncService::IsSetupInProgress() &&
         !user_settings_->IsFirstSetupComplete();
}

std::string HuhiProfileSyncService::GetOrCreateSyncCode() {
  std::string sync_code = huhi_sync_prefs_.GetSeed();
  if (sync_code.empty()) {
    std::vector<uint8_t> seed = huhi_sync::crypto::GetSeed();
    sync_code = huhi_sync::crypto::PassphraseFromBytes32(seed);
  }
  return sync_code;
}

bool HuhiProfileSyncService::SetSyncCode(const std::string& sync_code) {
  std::vector<uint8_t> seed;
  if (!huhi_sync::crypto::PassphraseToBytes32(sync_code, &seed))
    return false;
  if (!huhi_sync_prefs_.SetSeed(sync_code))
    return false;
  return true;
}

void HuhiProfileSyncService::ResetSync(
    DeviceInfoSyncService* device_info_service, base::OnceClosure cb) {
  DCHECK(device_info_service);
  // Do not send self deleted commit if engine is not up and running
  if (GetTransportState() != SyncService::TransportState::ACTIVE) {
    std::move(cb).Run();
    return;
  }
  syncer::DeviceInfoTracker* tracker =
    device_info_service->GetDeviceInfoTracker();
  DCHECK(tracker);

  const syncer::DeviceInfo* local_device_info =
      device_info_service->GetLocalDeviceInfoProvider()->GetLocalDeviceInfo();

  tracker->DeleteDeviceInfo(
      local_device_info,
      base::BindOnce(&HuhiProfileSyncService::OnSelfDeleted,
                     weak_ptr_factory_.GetWeakPtr(), std::move(cb)));
}

HuhiSyncAuthManager* HuhiProfileSyncService::GetHuhiSyncAuthManager() {
  return static_cast<HuhiSyncAuthManager*>(auth_manager_.get());
}

void HuhiProfileSyncService::OnHuhiSyncPrefsChanged(const std::string& path) {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  if (path == huhi_sync::Prefs::GetSeedPath()) {
    const std::string seed = huhi_sync_prefs_.GetSeed();
    if (!seed.empty()) {
      GetHuhiSyncAuthManager()->DeriveSigningKeys(seed);
      // Default enabled types: Bookmarks
      syncer::UserSelectableTypeSet selected_types;
      selected_types.Put(UserSelectableType::kBookmarks);
      GetUserSettings()->SetSelectedTypes(false, selected_types);
    } else {
      VLOG(1) << "Huhi sync seed cleared";
      GetHuhiSyncAuthManager()->ResetKeys();
    }
  }
}

void HuhiProfileSyncService::OnSelfDeleted(base::OnceClosure cb) {
  // This function will follow normal reset process and set SyncRequested to
  // false
  StopAndClear();
  huhi_sync_prefs_.Clear();
  // Sync prefs will be clear in ProfileSyncService::StopImpl
  std::move(cb).Run();
}

}  // namespace syncer
