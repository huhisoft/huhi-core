/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/ui/huhi_browser_command_controller.h"
#include "huhi/browser/ui/huhi_browser_content_setting_bubble_model_delegate.h"
#include "huhi/browser/ui/toolbar/huhi_location_bar_model_delegate.h"
#include "chrome/browser/ui/browser_command_controller.h"
#include "chrome/browser/ui/browser_content_setting_bubble_model_delegate.h"

#if !defined(OS_ANDROID)
#include "huhi/browser/ui/bookmark/huhi_bookmark_tab_helper.h"
#endif

#define BrowserContentSettingBubbleModelDelegate \
  HuhiBrowserContentSettingBubbleModelDelegate
#define BrowserCommandController HuhiBrowserCommandController
#define BrowserLocationBarModelDelegate HuhiLocationBarModelDelegate
#if !defined(OS_ANDROID)
#define BookmarkTabHelper HuhiBookmarkTabHelper
#endif

#include "../../../../../chrome/browser/ui/browser.cc"  // NOLINT
#undef BrowserLocationBarModelDelegate
#undef BrowserContentSettingBubbleModelDelegate
#undef BrowserCommandController

#if !defined(OS_ANDROID)
#undef BookmarkTabHelper
#endif
