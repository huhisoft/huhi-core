// /* Copyright (c) 2020 The Huhi Authors. All rights reserved.
//  * This Source Code Form is subject to the terms of the Mozilla Public
//  * License, v. 2.0. If a copy of the MPL was not distributed with this file,
//  * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_VIEW_H_
#define HUHI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_VIEW_H_

#include "huhi/browser/ui/huhi_browser_window.h"

#define BrowserWindow HuhiBrowserWindow
#include "../../../../../../../chrome/browser/ui/views/frame/browser_view.h"  // NOLINT
#undef BrowserWindow

#endif  // HUHI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_VIEW_H_
