/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_CHROME_BROWSER_CHROME_BROWSER_MAIN_ANDROID_H_
#define HUHI_CHROMIUM_SRC_CHROME_BROWSER_CHROME_BROWSER_MAIN_ANDROID_H_

#include "huhi/browser/huhi_browser_main_parts.h"
#include "chrome/browser/chrome_browser_main.h"

#define ChromeBrowserMainParts HuhiBrowserMainParts
#include "../../../../chrome/browser/chrome_browser_main_android.h"  // NOLINT
#undef ChromeBrowserMainParts

#endif  // HUHI_CHROMIUM_SRC_CHROME_BROWSER_CHROME_BROWSER_MAIN_ANDROID_H_
