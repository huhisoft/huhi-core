/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_FILE_UTIL_H_
#define HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_FILE_UTIL_H_

#include <string>

#include "base/files/file.h"

namespace huhi_rewards {

bool TailFile(
    base::File* file,
    const int num_lines);

bool TailFileAsString(
    base::File* file,
    const int num_lines,
    std::string* value);

std::string GetLastFileError(
    base::File* file);

}  // namespace huhi_rewards

#endif  // HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_FILE_UTIL_H_
