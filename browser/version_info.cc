/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/version_info.h"

namespace version_info {

std::string GetHuhiVersionWithoutChromiumMajorVersion() {
  return std::string(HUHI_BROWSER_VERSION);
}

std::string GetHuhiVersionNumberForDisplay() {
  return std::string(HUHI_BROWSER_VERSION) +
      "  Chromium: " + HUHI_CHROMIUM_VERSION;
}

std::string GetHuhiChromiumVersionNumber() {
  return std::string(HUHI_CHROMIUM_VERSION);
}

}  // namespace version_info
