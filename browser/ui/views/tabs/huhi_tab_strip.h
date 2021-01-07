/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_VIEWS_TABS_HUHI_TAB_STRIP_H_
#define HUHI_BROWSER_UI_VIEWS_TABS_HUHI_TAB_STRIP_H_

#include "chrome/browser/ui/views/tabs/tab_strip.h"

class HuhiTabStrip : public TabStrip {
 public:
  using TabStrip::TabStrip;
  ~HuhiTabStrip() override;
  HuhiTabStrip(const HuhiTabStrip&) = delete;
  HuhiTabStrip& operator=(const HuhiTabStrip&) = delete;

 private:
  // TabStrip overrides:
  bool ShouldHideCloseButtonForTab(Tab* tab) const override;
  SkColor GetTabSeparatorColor() const override;
};

#endif  // HUHI_BROWSER_UI_VIEWS_TABS_HUHI_TAB_STRIP_H_
