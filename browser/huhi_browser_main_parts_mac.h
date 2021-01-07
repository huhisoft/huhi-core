/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_HUHI_BROWSER_MAIN_PARTS_MAC_H_
#define HUHI_BROWSER_HUHI_BROWSER_MAIN_PARTS_MAC_H_

#include "chrome/browser/chrome_browser_main_mac.h"

class HuhiBrowserMainPartsMac : public ChromeBrowserMainPartsMac {
 public:
  using ChromeBrowserMainPartsMac::ChromeBrowserMainPartsMac;
  ~HuhiBrowserMainPartsMac() override = default;

 private:
  // ChromeBrowserMainPartsMac overrides:
  void PreMainMessageLoopStart() override;
};

#endif  // HUHI_BROWSER_HUHI_BROWSER_MAIN_PARTS_MAC_H_
