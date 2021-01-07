/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_VIEWS_LOCATION_BAR_HUHI_STAR_VIEW_H_
#define HUHI_BROWSER_UI_VIEWS_LOCATION_BAR_HUHI_STAR_VIEW_H_

#include "chrome/browser/ui/views/location_bar/star_view.h"

class HuhiStarView : public StarView {
 public:
  using StarView::StarView;

 protected:
  // views::View:
  void UpdateImpl() override;

  DISALLOW_COPY_AND_ASSIGN(HuhiStarView);
};

#endif  // HUHI_BROWSER_UI_VIEWS_LOCATION_BAR_HUHI_STAR_VIEW_H_
