/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_CHROME_BROWSER_UI_BROWSER_H_
#define HUHI_CHROMIUM_SRC_CHROME_BROWSER_UI_BROWSER_H_

#define HUHI_BROWSER_H \
 private: \
  friend class BookmarkPrefsService;

#include "../../../../../chrome/browser/ui/browser.h"  // NOLINT

#undef HUHI_BROWSER_H

#endif  // HUHI_CHROMIUM_SRC_CHROME_BROWSER_UI_BROWSER_H_
