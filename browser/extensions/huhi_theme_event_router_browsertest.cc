/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/extensions/huhi_theme_event_router.h"
#include "huhi/browser/themes/huhi_dark_mode_utils.h"
#include "huhi/browser/themes/huhi_theme_service.h"
#include "huhi/common/pref_names.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/themes/theme_service_factory.h"
#include "chrome/browser/ui/browser.h"
#include "components/prefs/pref_service.h"
#include "content/public/test/browser_test.h"
#include "testing/gmock/include/gmock/gmock.h"

using HuhiThemeEventRouterBrowserTest = InProcessBrowserTest;

namespace extensions {

class MockHuhiThemeEventRouter : public HuhiThemeEventRouter {
 public:
  using HuhiThemeEventRouter::HuhiThemeEventRouter;
  ~MockHuhiThemeEventRouter() override {}

  MOCK_METHOD0(Notify, void());
};

}  // namespace extensions

IN_PROC_BROWSER_TEST_F(HuhiThemeEventRouterBrowserTest,
                       ThemeChangeTest) {
  dark_mode::SetHuhiDarkModeType(
      dark_mode::HuhiDarkModeType::HUHI_DARK_MODE_TYPE_DARK);

  extensions::MockHuhiThemeEventRouter* mock_router =
      new extensions::MockHuhiThemeEventRouter(browser()->profile());
  HuhiThemeService* service = static_cast<HuhiThemeService*>(
      ThemeServiceFactory::GetForProfile(browser()->profile()));
  service->SetHuhiThemeEventRouterForTesting(mock_router);

  EXPECT_CALL(*mock_router, Notify()).Times(1);
  dark_mode::SetHuhiDarkModeType(
      dark_mode::HuhiDarkModeType::HUHI_DARK_MODE_TYPE_LIGHT);

  EXPECT_CALL(*mock_router, Notify()).Times(1);
  dark_mode::SetHuhiDarkModeType(
      dark_mode::HuhiDarkModeType::HUHI_DARK_MODE_TYPE_DARK);

  EXPECT_CALL(*mock_router, Notify()).Times(0);
  dark_mode::SetHuhiDarkModeType(
      dark_mode::HuhiDarkModeType::HUHI_DARK_MODE_TYPE_DARK);
}
