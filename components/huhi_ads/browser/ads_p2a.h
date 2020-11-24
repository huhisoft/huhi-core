/* Copyright 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_ADS_BROWSER_ADS_P2A_H_
#define HUHI_COMPONENTS_HUHI_ADS_BROWSER_ADS_P2A_H_

#include <string>

class PrefService;
class PrefRegistrySimple;

namespace huhi_ads {

void RegisterP2APrefs(PrefRegistrySimple* prefs);

void RecordEventInWeeklyStorage(
    PrefService* prefs,
    const std::string& pref_name);

void EmitConfirmationsCountMetric(int answer);

}  // namespace huhi_ads

#endif  // HUHI_COMPONENTS_HUHI_ADS_BROWSER_ADS_P2A_H_
