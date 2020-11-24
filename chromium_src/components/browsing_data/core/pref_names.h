/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_COMPONENTS_BROWSING_DATA_CORE_PREF_NAMES_H_
#define HUHI_CHROMIUM_SRC_COMPONENTS_BROWSING_DATA_CORE_PREF_NAMES_H_

#include "../../../../../components/browsing_data/core/pref_names.h"

namespace browsing_data {

namespace prefs {

extern const char kDeleteBrowsingHistoryOnExit[];
extern const char kDeleteDownloadHistoryOnExit[];
extern const char kDeleteCacheOnExit[];
extern const char kDeleteCookiesOnExit[];
extern const char kDeletePasswordsOnExit[];
extern const char kDeleteFormDataOnExit[];
extern const char kDeleteHostedAppsDataOnExit[];
extern const char kDeleteSiteSettingsOnExit[];

}  // namespace prefs

}  // namespace browsing_data

#endif  // HUHI_CHROMIUM_SRC_COMPONENTS_BROWSING_DATA_CORE_PREF_NAMES_H_
