/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_SYNC_ENGINE_IMPL_HUHI_SYNC_MANAGER_IMPL_H_
#define HUHI_COMPONENTS_SYNC_ENGINE_IMPL_HUHI_SYNC_MANAGER_IMPL_H_

#include <string>

#include "components/sync/engine_impl/sync_manager_impl.h"

namespace syncer {

class HuhiSyncManagerImpl : public SyncManagerImpl {
 public:
  HuhiSyncManagerImpl(
      const std::string& name,
      network::NetworkConnectionTracker* network_connection_tracker);
  ~HuhiSyncManagerImpl() override;

  void StartSyncingNormally(base::Time last_poll_time) override;

 private:
  DISALLOW_COPY_AND_ASSIGN(HuhiSyncManagerImpl);
};

}  // namespace syncer

#endif  // HUHI_COMPONENTS_SYNC_ENGINE_IMPL_HUHI_SYNC_MANAGER_IMPL_H_
