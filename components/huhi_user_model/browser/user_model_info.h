/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_USER_MODEL_BROWSER_USER_MODEL_INFO_H_
#define HUHI_COMPONENTS_HUHI_USER_MODEL_BROWSER_USER_MODEL_INFO_H_

#include <stdint.h>

#include <string>

#include "base/files/file_path.h"

namespace huhi_user_model {

struct UserModelInfo {
  std::string id;
  uint16_t version;
  base::FilePath path;
};

}  // namespace huhi_user_model

#endif  // HUHI_COMPONENTS_HUHI_USER_MODEL_BROWSER_USER_MODEL_INFO_H_
