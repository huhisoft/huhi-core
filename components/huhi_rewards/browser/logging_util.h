/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_LOGGING_UTIL_H_
#define HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_LOGGING_UTIL_H_

#include <string>

#include "base/files/file_util.h"
#include "base/time/time.h"

namespace huhi_rewards {

bool InitializeLog(
    base::File* file,
    const base::FilePath& path);

std::string FriendlyFormatLogEntry(
    const base::Time& time,
    const std::string& file,
    const int line,
    const int verbose_level,
    const std::string& message);

bool WriteToLog(
    base::File* file,
    const std::string& log_entry);

}  // namespace huhi_rewards

#endif  // HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_LOGGING_UTIL_H_
