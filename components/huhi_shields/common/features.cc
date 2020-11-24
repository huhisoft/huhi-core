// Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Huhi Software
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#include "huhi/components/huhi_shields/common/features.h"

#include "base/feature_list.h"

namespace huhi_shields {
namespace features {

const base::Feature kHuhiAdblockCosmeticFiltering{
    "HuhiAdblockCosmeticFiltering",
    base::FEATURE_ENABLED_BY_DEFAULT};

}  // namespace features
}  // namespace huhi_shields
