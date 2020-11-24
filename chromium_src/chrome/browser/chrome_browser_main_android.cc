/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/chromium_src/chrome/browser/chrome_browser_main_android.h"

#include "huhi/browser/huhi_browser_main_parts.h"
#include "chrome/browser/chrome_browser_main.h"

#define ChromeBrowserMainParts HuhiBrowserMainParts
#include "../../../../chrome/browser/chrome_browser_main_android.cc"  // NOLINT
#undef ChromeBrowserMainParts
