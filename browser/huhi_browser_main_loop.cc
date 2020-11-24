/* Copyright 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/huhi_browser_main_loop.h"

#include "huhi/browser/huhi_browser_main_parts.h"

namespace huhi {

void HuhiBrowserMainLoop::PreShutdown() {
  parts()->PreShutdown();
  content::BrowserMainLoop::PreShutdown();
}

}  // namespace huhi
