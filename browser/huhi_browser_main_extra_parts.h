/* Copyright 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_HUHI_BROWSER_MAIN_EXTRA_PARTS_H_
#define HUHI_BROWSER_HUHI_BROWSER_MAIN_EXTRA_PARTS_H_

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "chrome/browser/chrome_browser_main.h"
#include "chrome/browser/chrome_browser_main_extra_parts.h"

class HuhiBrowserMainExtraParts : public ChromeBrowserMainExtraParts {
 public:
  HuhiBrowserMainExtraParts();
  ~HuhiBrowserMainExtraParts() override;

  // ChromeBrowserMainExtraParts overrides.
  void PostBrowserStart() override;
  void PreMainMessageLoopRun() override;

 private:
  DISALLOW_COPY_AND_ASSIGN(HuhiBrowserMainExtraParts);
};

#endif  // HUHI_BROWSER_HUHI_BROWSER_MAIN_EXTRA_PARTS_H_
