/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_THEMES_HUHI_THEME_HELPER_WIN_H_
#define HUHI_BROWSER_THEMES_HUHI_THEME_HELPER_WIN_H_

#include "chrome/browser/themes/theme_helper_win.h"

class HuhiThemeHelperWin : public ThemeHelperWin {
 public:
  HuhiThemeHelperWin() = default;
  ~HuhiThemeHelperWin() override = default;

 private:
  // ThemeHelperWin overrides:
  SkColor GetDefaultColor(
      int id,
      bool incognito,
      const CustomThemeSupplier* theme_supplier) const override;

  DISALLOW_COPY_AND_ASSIGN(HuhiThemeHelperWin);
};

#endif  // HUHI_BROWSER_THEMES_HUHI_THEME_HELPER_WIN_H_
