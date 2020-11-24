/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BAT_ADS_INTERNAL_STRING_UTIL_H_
#define BAT_ADS_INTERNAL_STRING_UTIL_H_

#include <stdint.h>

#include <string>
#include <vector>

namespace ads {

std::string BytesToHexString(
    const std::vector<uint8_t>& bytes);

}  // namespace ads

#endif  // BAT_ADS_INTERNAL_STRING_UTIL_H_
