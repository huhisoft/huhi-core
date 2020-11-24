/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef CHROME_COMMON_CHROME_ICON_RESOURCES_WIN_H_
#define CHROME_COMMON_CHROME_ICON_RESOURCES_WIN_H_

namespace icon_resources {

// This file contains the indices of icon resources in huhi_exe.rc.

enum {
  // The main application icon is always index 0.
  kApplicationIndex = 0,

#if defined(OFFICIAL_BUILD)
  // Legacy indices that are no longer used.
  kApplication2Index = 1,
  kApplication3Index = 2,
  kApplication4Index = 3,

  // The Huhi Canary application icon.
  kSxSApplicationIndex = 4,

  // The Huhi App Launcher icon.
  kAppLauncherIndex = 5,

  // The Huhi App Launcher Canary icon.
  kSxSAppLauncherIndex = 6,

  // The Huhi incognito icon.
  kIncognitoIndex = 7,

  // The Huhi Dev application icon.
  kDevApplicationIndex = 8,

  // The Huhi Beta application icon.
  kBetaApplicationIndex = 9,
#else
  // The Huhi Developer App Launcher icon.
  kAppLauncherIndex = 1,

  // The Huhi Developer incognito icon.
  kIncognitoIndex = 2,
#endif
};

}  // namespace icon_resources

#endif  // CHROME_COMMON_CHROME_ICON_RESOURCES_WIN_H_
