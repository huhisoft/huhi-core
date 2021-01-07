/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_USER_MODEL_BROWSER_COMPONENT_INFO_H_
#define HUHI_COMPONENTS_HUHI_USER_MODEL_BROWSER_COMPONENT_INFO_H_

#include <string>

namespace huhi_user_model {

struct ComponentInfo {
  ComponentInfo();
  ComponentInfo(
      const std::string& id,
      const std::string& public_key);
  ~ComponentInfo();

  std::string id;
  std::string public_key;
};

}  // namespace huhi_user_model

#endif  // HUHI_COMPONENTS_HUHI_USER_MODEL_BROWSER_COMPONENT_INFO_H_
