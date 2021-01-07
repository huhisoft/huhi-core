/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_HUHI_BROWSER_WINDOW_H_
#define HUHI_BROWSER_UI_HUHI_BROWSER_WINDOW_H_

#include "chrome/browser/ui/browser_window.h"

class HuhiBrowserWindow : public BrowserWindow {
 public:
  ~HuhiBrowserWindow() override {}

  virtual void StartTabCycling() = 0;
};

#endif  // HUHI_BROWSER_UI_HUHI_BROWSER_WINDOW_H_
