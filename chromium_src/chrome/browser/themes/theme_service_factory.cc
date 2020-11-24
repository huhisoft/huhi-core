/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/browser/themes/theme_service_factory.h"

#include "huhi/browser/themes/huhi_theme_service.h"

#if !defined(OS_LINUX)
#define HUHI_THEMESERVICEFACTORY_BUILDSERVICEINSTANCEFOR \
  using ThemeService = HuhiThemeService;
#else
// On Linux ThemeServiceAuraLinux derives from HuhiThemeService instead.
#define HUHI_THEMESERVICEFACTORY_BUILDSERVICEINSTANCEFOR
#endif

#include "../../../../../chrome/browser/themes/theme_service_factory.cc"
#undef HUHI_THEMESERVICEFACTORY_BUILDSERVICEINSTANCEFOR
