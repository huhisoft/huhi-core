/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/themes/huhi_theme_service.h"

#include "base/no_destructor.h"
#include "huhi/browser/themes/huhi_theme_helper.h"
#include "huhi/browser/extensions/huhi_theme_event_router.h"
#include "chrome/browser/profiles/profile.h"
#include "huhi/browser/profiles/profile_util.h"

#if defined(OS_WIN)
#include "huhi/browser/themes/huhi_theme_helper_win.h"
#endif

namespace {

const ThemeHelper& GetHuhiThemeHelper(Profile* profile) {
#if defined(OS_WIN)
  using HuhiThemeHelper = HuhiThemeHelperWin;
#endif
  // Because the helper is created as a NoDestructor static, we need separate
  // instances for regular vs tor/guest profiles.
  if (huhi::IsTorProfile(profile) || huhi::IsGuestProfile(profile)) {
    static base::NoDestructor<std::unique_ptr<ThemeHelper>> dark_theme_helper(
        std::make_unique<HuhiThemeHelper>());
    (static_cast<HuhiThemeHelper*>(dark_theme_helper.get()->get()))
        ->SetTorOrGuest();
    return **dark_theme_helper;
  } else {
    static base::NoDestructor<std::unique_ptr<ThemeHelper>> theme_helper(
        std::make_unique<HuhiThemeHelper>());
    return **theme_helper;
  }
}

}  // namespace

// Replace Chromium's ThemeHelper with HuhiThemeHelper that is appropriate for
// the given profile. There should only be 3 static ThemeHelpers at most: the
// original Chromium one, and 2 Huhi ones.
HuhiThemeService::HuhiThemeService(Profile* profile,
                                     const ThemeHelper& theme_helper)
    : ThemeService(profile, GetHuhiThemeHelper(profile)) {
  huhi_theme_event_router_.reset(
      new extensions::HuhiThemeEventRouter(profile));
}

HuhiThemeService::~HuhiThemeService() = default;

void HuhiThemeService::SetHuhiThemeEventRouterForTesting(
    extensions::HuhiThemeEventRouter* mock_router) {
  huhi_theme_event_router_.reset(mock_router);
}
