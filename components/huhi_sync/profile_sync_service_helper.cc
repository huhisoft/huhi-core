/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/components/huhi_sync/profile_sync_service_helper.h"

#include <string>
#include <utility>

#include "huhi/components/sync/driver/huhi_sync_profile_sync_service.h"
#include "components/sync_device_info/device_info_sync_service.h"
#include "components/sync_device_info/device_info_tracker.h"
#include "components/sync_device_info/local_device_info_provider.h"

namespace huhi_sync {

void ResetSync(syncer::HuhiProfileSyncService* sync_service,
               syncer::DeviceInfoSyncService* device_info_service,
               base::OnceClosure on_reset_done) {
  if (sync_service->GetTransportState() !=
      syncer::SyncService::TransportState::ACTIVE) {
    std::move(on_reset_done).Run();
    return;
  }
  syncer::DeviceInfoTracker* tracker =
      device_info_service->GetDeviceInfoTracker();
  DCHECK(tracker);

  const syncer::DeviceInfo* local_device_info =
      device_info_service->GetLocalDeviceInfoProvider()->GetLocalDeviceInfo();

  sync_service->SuspendDeviceObserverForOwnReset();

  tracker->DeleteDeviceInfo(
      local_device_info->guid(),
      base::BindOnce(
          [](syncer::HuhiProfileSyncService* sync_service,
             base::OnceClosure on_reset_done) {
            sync_service->OnSelfDeviceInfoDeleted(std::move(on_reset_done));
            sync_service->ResumeDeviceObserver();
          },
          sync_service, std::move(on_reset_done)));
}

void DeleteDevice(syncer::HuhiProfileSyncService* sync_service,
                  syncer::DeviceInfoSyncService* device_info_service,
                  const std::string& device_guid) {
  if (sync_service->GetTransportState() !=
      syncer::SyncService::TransportState::ACTIVE) {
    return;
  }
  syncer::DeviceInfoTracker* tracker =
      device_info_service->GetDeviceInfoTracker();
  DCHECK(tracker);

  tracker->DeleteDeviceInfo(device_guid, base::DoNothing());
}

}  // namespace huhi_sync
