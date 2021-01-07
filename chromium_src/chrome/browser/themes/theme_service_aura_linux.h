/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_CHROME_BROWSER_THEMES_THEME_SERVICE_AURA_LINUX_H_
#define HUHI_CHROMIUM_SRC_CHROME_BROWSER_THEMES_THEME_SERVICE_AURA_LINUX_H_

#include "huhi/browser/themes/huhi_theme_service.h"

#undef ThemeService
#define ThemeService HuhiThemeService
#include "../../../../../chrome/browser/themes/theme_service_aura_linux.h"
#undef ThemeService

#endif  // HUHI_CHROMIUM_SRC_CHROME_BROWSER_THEMES_THEME_SERVICE_AURA_LINUX_H_
