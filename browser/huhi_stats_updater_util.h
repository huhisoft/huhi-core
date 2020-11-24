/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_HUHI_STATS_UPDATER_UTIL_H_
#define HUHI_BROWSER_HUHI_STATS_UPDATER_UTIL_H_

#include <string>

#include "base/time/time.h"
#include "base/system/sys_info.h"
#include "components/prefs/pref_service.h"

namespace huhi {

std::string GetDateAsYMD(const base::Time& time);

base::Time GetFirstRunTime(PrefService *pref_service);

std::string GetPlatformIdentifier();

int GetIsoWeekNumber(const base::Time& time);

base::Time GetYMDAsDate(const base::StringPiece& ymd);

std::string GetAPIKey();

}  // namespace huhi

#endif  // HUHI_BROWSER_HUHI_STATS_UPDATER_UTIL_H_
