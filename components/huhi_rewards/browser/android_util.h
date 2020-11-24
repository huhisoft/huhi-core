/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_ANDROID_UTIL_H_
#define HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_ANDROID_UTIL_H_

#include <string>

#include "bat/ledger/ledger_client.h"

namespace android_util {

ledger::type::ClientInfoPtr GetAndroidClientInfo();

}  // namespace android_util

#endif  // HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_ANDROID_UTIL_H_
