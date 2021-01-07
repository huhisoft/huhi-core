/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/components/huhi_sync/features.h"

#include "base/feature_list.h"
#include "huhi/components/huhi_sync/buildflags/buildflags.h"

namespace huhi_sync {
namespace features {

#if BUILDFLAG(ENABLE_HUHI_SYNC)
const base::Feature kHuhiSync{"HuhiSync", base::FEATURE_ENABLED_BY_DEFAULT};
#else
const base::Feature kHuhiSync{"HuhiSync", base::FEATURE_DISABLED_BY_DEFAULT};
#endif

}  // namespace features
}  // namespace huhi_sync
