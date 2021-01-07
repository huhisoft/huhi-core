/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/ui/views/tabs/huhi_browser_tab_strip_controller.h"
#include "huhi/browser/ui/views/tabs/huhi_tab_strip.h"
#include "huhi/browser/ui/views/toolbar/huhi_toolbar_view.h"
#include "chrome/browser/ui/views/frame/tab_strip_region_view.h"

#define ToolbarView HuhiToolbarView
#define BrowserTabStripController HuhiBrowserTabStripController
#define TabStrip HuhiTabStrip
#include "../../../../../../../chrome/browser/ui/views/frame/browser_view.cc"  // NOLINT
#undef ToolbarView
#undef BrowserTabStripController
#undef TabStrip
