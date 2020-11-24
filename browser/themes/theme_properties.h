/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_THEMES_THEME_PROPERTIES_H_
#define HUHI_BROWSER_THEMES_THEME_PROPERTIES_H_

#include "base/optional.h"
#include "huhi/browser/themes/huhi_dark_mode_utils.h"
#include "third_party/skia/include/core/SkColor.h"

namespace HuhiThemeProperties {

const SkColor kPrivateColorForTest = SkColorSetRGB(0xFF, 0x00, 0x00);
const SkColor kLightColorForTest = SkColorSetRGB(0xFF, 0xFF, 0xFF);
const SkColor kDarkColorForTest = SkColorSetRGB(0x00, 0x00, 0x00);

enum TestProperty {
  COLOR_FOR_TEST = 9000
};

enum ThemeProperties {
  HUHI_THEME_PROPERTIES_START = 10000,
  COLOR_BOOKMARK_BAR_INSTRUCTIONS_TEXT = HUHI_THEME_PROPERTIES_START,
  HUHI_THEME_PROPERTIES_LAST = COLOR_BOOKMARK_BAR_INSTRUCTIONS_TEXT,
};

bool IsHuhiThemeProperties(int id);

}  // namespace HuhiThemeProperties

base::Optional<SkColor> MaybeGetDefaultColorForHuhiUi(
    int id, bool incognito, dark_mode::HuhiDarkModeType dark_mode);

#endif  // HUHI_BROWSER_THEMES_THEME_PROPERTIES_H_
