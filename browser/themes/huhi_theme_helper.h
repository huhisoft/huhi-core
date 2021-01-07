/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_THEMES_HUHI_THEME_HELPER_H_
#define HUHI_BROWSER_THEMES_HUHI_THEME_HELPER_H_

#include "base/optional.h"
#include "chrome/browser/themes/theme_helper.h"

class Profile;

class HuhiThemeHelper : public ThemeHelper {
 public:
  HuhiThemeHelper() = default;
  ~HuhiThemeHelper() override;

  HuhiThemeHelper(const HuhiThemeHelper&) = delete;
  HuhiThemeHelper& operator=(const HuhiThemeHelper&) = delete;

  void SetTorOrGuest();

 protected:
  // ThemeHelper overrides:
  SkColor GetDefaultColor(
      int id,
      bool incognito,
      const CustomThemeSupplier* theme_supplier) const override;

  base::Optional<SkColor> GetOmniboxColor(
      int id,
      bool incognito,
      const CustomThemeSupplier* theme_supplier,
      bool* has_custom_color) const override;

 private:
  bool is_tor_or_guest_ = false;
};

#endif  // HUHI_BROWSER_THEMES_HUHI_THEME_HELPER_H_
