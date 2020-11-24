/* Copyright 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_HUHI_BROWSER_MAIN_LOOP_H_
#define HUHI_BROWSER_HUHI_BROWSER_MAIN_LOOP_H_

#include "base/macros.h"
#include "content/browser/browser_main_loop.h"

namespace huhi {

class HuhiBrowserMainLoop : public content::BrowserMainLoop {
 public:
  using BrowserMainLoop::BrowserMainLoop;
  ~HuhiBrowserMainLoop() override = default;

  void PreShutdown() override;

 private:
  DISALLOW_COPY_AND_ASSIGN(HuhiBrowserMainLoop);
};

}  // namespace huhi

#endif  // HUHI_BROWSER_HUHI_BROWSER_MAIN_LOOP_H_
