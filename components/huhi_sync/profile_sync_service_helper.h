/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_SYNC_PROFILE_SYNC_SERVICE_HELPER_H_
#define HUHI_COMPONENTS_HUHI_SYNC_PROFILE_SYNC_SERVICE_HELPER_H_

#include <string>

#include "base/callback.h"

namespace syncer {
class HuhiProfileSyncService;
class DeviceInfoSyncService;
}  // namespace syncer

namespace huhi_sync {

// Helper function to break circular dependency between //components/sync/driver
// and //component/sync_device_info
void ResetSync(syncer::HuhiProfileSyncService* sync_service,
               syncer::DeviceInfoSyncService* device_info_service,
               base::OnceClosure on_reset_done);

void DeleteDevice(syncer::HuhiProfileSyncService* sync_service,
                  syncer::DeviceInfoSyncService* device_info_service,
                  const std::string& device_guid);

}  // namespace huhi_sync

#endif  // HUHI_COMPONENTS_HUHI_SYNC_PROFILE_SYNC_SERVICE_HELPER_H_
