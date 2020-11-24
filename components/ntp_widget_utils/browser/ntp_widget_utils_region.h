/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_NTP_WIDGET_UTILS_BROWSER_NTP_WIDGET_UTILS_REGION_H_
#define HUHI_COMPONENTS_NTP_WIDGET_UTILS_BROWSER_NTP_WIDGET_UTILS_REGION_H_

#include <string>
#include <vector>

class PrefService;

namespace ntp_widget_utils {

bool IsRegionSupported(PrefService* pref_service,
    const std::vector<std::string>& regions,
    bool allow_list);

}  // namespace ntp_widget_utils

#endif  // HUHI_COMPONENTS_NTP_WIDGET_UTILS_BROWSER_NTP_WIDGET_UTILS_REGION_H_