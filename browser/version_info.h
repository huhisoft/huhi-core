/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_VERSION_INFO_H_
#define HUHI_BROWSER_VERSION_INFO_H_

#include <string>

namespace version_info {
std::string GetHuhiVersionWithoutChromiumMajorVersion();
std::string GetHuhiVersionNumberForDisplay();
std::string GetHuhiChromiumVersionNumber();
}  // namespace version_info

#endif  // HUHI_BROWSER_VERSION_INFO_H_
