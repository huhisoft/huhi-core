/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_ADS_BROWSER_PREFS_UTIL_H_
#define HUHI_COMPONENTS_HUHI_ADS_BROWSER_PREFS_UTIL_H_

#include <string>

#include "base/values.h"
#include "components/prefs/pref_service.h"

namespace huhi_ads {
namespace prefs {

const base::Value* GetValue(
    PrefService* prefs,
    const std::string& path);

}  // namespace prefs
}  // namespace huhi_ads

#endif  // HUHI_COMPONENTS_HUHI_ADS_BROWSER_PREFS_UTIL_H_
