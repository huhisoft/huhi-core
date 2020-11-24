// Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Huhi Software
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HUHI_CHROMIUM_SRC_CHROME_BROWSER_PROFILES_PROFILE_METRICS_H_
#define HUHI_CHROMIUM_SRC_CHROME_BROWSER_PROFILES_PROFILE_METRICS_H_

#define LogProfileAvatarSelection \
    LogProfileAvatarSelection_ChromiumImpl(size_t index); \
    static void LogProfileAvatarSelection
#include "../../../../../chrome/browser/profiles/profile_metrics.h"
#undef LogProfileAvatarSelection

#endif  // HUHI_CHROMIUM_SRC_CHROME_BROWSER_PROFILES_PROFILE_METRICS_H_
