// Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Huhi Software
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HUHI_CHROMIUM_SRC_COMPONENTS_SYNC_DEVICE_INFO_DEVICE_INFO_TRACKER_H_
#define HUHI_CHROMIUM_SRC_COMPONENTS_SYNC_DEVICE_INFO_DEVICE_INFO_TRACKER_H_

#define ForcePulseForTest                                 \
  DeleteDeviceInfo(const syncer::DeviceInfo* device_info, \
                   base::OnceClosure callback) {}         \
  virtual void ForcePulseForTest

#include "../../../../components/sync_device_info/device_info_tracker.h"

#undef ForcePulseForTest

#endif  // HUHI_CHROMIUM_SRC_COMPONENTS_SYNC_DEVICE_INFO_DEVICE_INFO_TRACKER_H_
