/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHILEDGER_LEGACY_BAT_UTIL_H_
#define HUHILEDGER_LEGACY_BAT_UTIL_H_

#include <string>

namespace huhiledger_bat_util {

std::string ConvertToProbi(const std::string& amount);

double ProbiToDouble(const std::string& probi);

}  // namespace huhiledger_bat_util

#endif  // HUHILEDGER_LEGACY_BAT_UTIL_H_
