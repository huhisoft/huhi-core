/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMMON_HUHI_FEATURES_H_
#define HUHI_COMMON_HUHI_FEATURES_H_

#include "base/component_export.h"
#include "base/feature_list.h"
#include "build/build_config.h"

namespace features {

#if defined(OS_ANDROID)
COMPONENT_EXPORT(CHROME_FEATURES)
extern const base::Feature kHuhiRewards;
#endif  // defined(OS_ANDROID)

}  // namespace features

#endif  // HUHI_COMMON_HUHI_FEATURES_H_
