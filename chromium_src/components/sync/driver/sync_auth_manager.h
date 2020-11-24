/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_COMPONENTS_SYNC_DRIVER_SYNC_AUTH_MANAGER_H_
#define HUHI_CHROMIUM_SRC_COMPONENTS_SYNC_DRIVER_SYNC_AUTH_MANAGER_H_

namespace syncer {
class HuhiSyncAuthManager;
}  // namespace syncer

// Header guard to prevent DetermineAccountToUse from getting overriden in it
#include "components/sync/driver/sync_auth_util.h"

#define RequestAccessToken virtual RequestAccessToken
#define DetermineAccountToUse                                  \
  DetermineAccountToUse_Unused() { return SyncAccountInfo(); } \
  friend HuhiSyncAuthManager;                                 \
  virtual SyncAccountInfo DetermineAccountToUse

#include "../../../../../components/sync/driver/sync_auth_manager.h"

#undef HUHI_SYNC_AUTH_MANAGER_H_
#undef RequestAccessToken
#undef DetermineAccountToUse
#endif  // HUHI_CHROMIUM_SRC_COMPONENTS_SYNC_DRIVER_SYNC_AUTH_MANAGER_H_
