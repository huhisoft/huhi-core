/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_USER_MODEL_BROWSER_COMPONENT_UTIL_H_
#define HUHI_COMPONENTS_HUHI_USER_MODEL_BROWSER_COMPONENT_UTIL_H_

#include <string>

#include "base/optional.h"
#include "huhi/components/huhi_user_model/browser/component_info.h"

namespace huhi_user_model {

base::Optional<ComponentInfo> GetComponentInfo(
    const std::string& id);

}  // namespace huhi_user_model

#endif  // HUHI_COMPONENTS_HUHI_USER_MODEL_BROWSER_COMPONENT_UTIL_H_
