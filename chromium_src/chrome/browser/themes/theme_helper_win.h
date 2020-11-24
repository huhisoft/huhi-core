/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_CHROME_BROWSER_THEMES_THEME_HELPER_WIN_H_
#define HUHI_CHROMIUM_SRC_CHROME_BROWSER_THEMES_THEME_HELPER_WIN_H_

#include "huhi/browser/themes/huhi_theme_helper.h"

#undef ThemeHelper
#define ThemeHelper HuhiThemeHelper

#define HUHI_THEME_HELPER_WIN_H_   \
 private:                           \
  friend class HuhiThemeHelperWin; \
                                    \
 public:
#include "../../../../../chrome/browser/themes/theme_helper_win.h"

#undef HUHI_THEME_HELPER_WIN_H_
#undef ThemeHelper
#define ThemeHelper ThemeHelper

#endif  // HUHI_CHROMIUM_SRC_CHROME_BROWSER_THEMES_THEME_HELPER_WIN_H_
