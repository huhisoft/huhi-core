/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/themes/huhi_dark_mode_utils.h"

#include "base/notreached.h"
#include "huhi/browser/themes/huhi_dark_mode_utils_internal.h"

namespace dark_mode {

void SetSystemDarkMode(HuhiDarkModeType type) {
  if (type == HuhiDarkModeType::HUHI_DARK_MODE_TYPE_DEFAULT) {
    // Linux doesn't support system dark theme so there is no chance to set
    // default type. Default is used for 'Same as Windows/MacOS'.
    NOTREACHED();
  }
  internal::SetSystemDarkModeForNonDefaultMode(
      type == HuhiDarkModeType::HUHI_DARK_MODE_TYPE_DARK);
}

}  // namespace dark_mode
