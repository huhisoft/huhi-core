/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_TEST_BASE_HUHI_TEST_LAUNCHER_H_
#define HUHI_TEST_BASE_HUHI_TEST_LAUNCHER_H_

#include "chrome/test/base/chrome_test_launcher.h"
#include "base/macros.h"

class HuhiTestLauncherDelegate : public ChromeTestLauncherDelegate {
 public:
  // Does not take ownership of ChromeTestSuiteRunner.
  explicit HuhiTestLauncherDelegate(ChromeTestSuiteRunner* runner);
  ~HuhiTestLauncherDelegate() override;

 private:
  // ChromeLauncherDelegate:
  content::ContentMainDelegate* CreateContentMainDelegate() override;

  DISALLOW_COPY_AND_ASSIGN(HuhiTestLauncherDelegate);
};

#endif  // HUHI_TEST_BASE_HUHI_TEST_LAUNCHER_H_
