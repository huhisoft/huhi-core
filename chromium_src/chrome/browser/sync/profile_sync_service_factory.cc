/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/sync/huhi_profile_sync_service_delegate.h"
#include "huhi/components/sync/driver/huhi_sync_profile_sync_service.h"
#include "chrome/browser/sync/device_info_sync_service_factory.h"

#define HUHI_BUILD_SERVICE_INSTANCE_FOR             \
  std::make_unique<syncer::HuhiProfileSyncService>( \
      std::move(init_params),                        \
      std::make_unique<syncer::HuhiProfileSyncServiceDelegate>(profile));

#include "../../../../../chrome/browser/sync/profile_sync_service_factory.cc"

#undef HUHI_BUILD_SERVICE_INSTANCE_FOR
