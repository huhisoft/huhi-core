/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_THEMES_HUHI_THEME_SERVICE_H_
#define HUHI_BROWSER_THEMES_HUHI_THEME_SERVICE_H_

#include <memory>

#include "chrome/browser/themes/theme_service.h"

namespace extensions {
class HuhiThemeEventRouter;
}  // namespace extensions

class Profile;

class HuhiThemeService : public ThemeService {
 public:
  explicit HuhiThemeService(Profile* profile, const ThemeHelper& theme_helper);
  ~HuhiThemeService() override;

 private:
  FRIEND_TEST_ALL_PREFIXES(HuhiThemeEventRouterBrowserTest, ThemeChangeTest);

  // Own |mock_router|.
  void SetHuhiThemeEventRouterForTesting(
      extensions::HuhiThemeEventRouter* mock_router);

  std::unique_ptr<extensions::HuhiThemeEventRouter> huhi_theme_event_router_;
};

#endif  // HUHI_BROWSER_THEMES_HUHI_THEME_SERVICE_H_
