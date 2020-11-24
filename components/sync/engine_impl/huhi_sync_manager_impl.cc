/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/components/sync/engine_impl/huhi_sync_manager_impl.h"

namespace syncer {

HuhiSyncManagerImpl::HuhiSyncManagerImpl(
    const std::string& name,
    network::NetworkConnectionTracker* network_connection_tracker)
  : SyncManagerImpl(name, network_connection_tracker) {}

HuhiSyncManagerImpl::~HuhiSyncManagerImpl() {}

void HuhiSyncManagerImpl::StartSyncingNormally(base::Time last_poll_time) {
  SyncManagerImpl::StartSyncingNormally(last_poll_time);
  // Remove this hack when we have FCM invalidation integrated.
  // We only enable BOOKMARKS by default so only force refresh it
  RefreshTypes(ModelTypeSet(BOOKMARKS));
}

}  // namespace syncer
