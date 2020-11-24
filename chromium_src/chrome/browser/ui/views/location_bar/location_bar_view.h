/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_LOCATION_BAR_LOCATION_BAR_VIEW_H_
#define HUHI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_LOCATION_BAR_LOCATION_BAR_VIEW_H_

#define HUHI_LOCATION_BAR_VIEW_H_   \
 private:                            \
  friend class HuhiLocationBarView; \
                                     \
 public:                             \
  void Layout(views::View* trailing_view);

#define GetBorderRadius virtual GetBorderRadius
#include "../../../../../../../chrome/browser/ui/views/location_bar/location_bar_view.h"
#undef GetBorderRadius
#undef HUHI_LOCATION_BAR_VIEW_H_

#endif  // HUHI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_LOCATION_BAR_LOCATION_BAR_VIEW_H_
