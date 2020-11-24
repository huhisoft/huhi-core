/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/components/huhi_user_model/browser/component_util.h"

#include "huhi/components/huhi_user_model/browser/components.h"

namespace huhi_user_model {

base::Optional<ComponentInfo> GetComponentInfo(
    const std::string& id) {
  const auto iter = components.find(id);
  if (iter == components.end()) {
    return base::nullopt;
  }

  return iter->second;
}

}  // namespace huhi_user_model
