/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_HUHI_BROWSER_MAIN_PARTS_H_
#define HUHI_BROWSER_HUHI_BROWSER_MAIN_PARTS_H_

#include "base/macros.h"
#include "chrome/browser/chrome_browser_main.h"

class HuhiBrowserMainParts : public ChromeBrowserMainParts {
 public:
  using ChromeBrowserMainParts::ChromeBrowserMainParts;
  ~HuhiBrowserMainParts() override = default;

  void PostBrowserStart() override;
  void PreShutdown() override;
  void PreProfileInit() override;
  void PostProfileInit() override;

 private:
  friend class ChromeBrowserMainExtraPartsTor;

  DISALLOW_COPY_AND_ASSIGN(HuhiBrowserMainParts);
};

#endif  // HUHI_BROWSER_HUHI_BROWSER_MAIN_PARTS_H_
