/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_CHROME_TEST_VIEWS_ACCESSIBILITY_CHECKER_H_
#define HUHI_CHROMIUM_SRC_CHROME_TEST_VIEWS_ACCESSIBILITY_CHECKER_H_

#include "chrome/browser/ui/views/chrome_views_delegate.h"

#if defined(OS_LINUX)
#include "huhi/browser/ui/views/huhi_views_delegate_linux.h"
#define ChromeViewsDelegate HuhiViewsDelegateLinux
#endif
#include "../../../../../chrome/test/views/accessibility_checker.h"
#if defined(OS_LINUX)
#undef ChromeViewsDelegate
#endif

#endif  // HUHI_CHROMIUM_SRC_CHROME_TEST_VIEWS_ACCESSIBILITY_CHECKER_H_
