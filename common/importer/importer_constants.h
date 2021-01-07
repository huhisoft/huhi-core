/* Copyright 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMMON_IMPORTER_IMPORTER_CONSTANTS_H_
#define HUHI_COMMON_IMPORTER_IMPORTER_CONSTANTS_H_

#include "build/build_config.h"

// Pref file that holds installed extension list.
constexpr char kChromeExtensionsPreferencesFile[] =
#if defined(OS_LINUX)
    "Preferences";
#else
    "Secure Preferences";
#endif
constexpr char kChromeExtensionsListPath[] = "extensions.settings";

#endif  // HUHI_COMMON_IMPORTER_IMPORTER_CONSTANTS_H_
