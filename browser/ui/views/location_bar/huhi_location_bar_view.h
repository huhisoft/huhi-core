/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_VIEWS_LOCATION_BAR_HUHI_LOCATION_BAR_VIEW_H_
#define HUHI_BROWSER_UI_VIEWS_LOCATION_BAR_HUHI_LOCATION_BAR_VIEW_H_

#include <vector>

#include "huhi/components/tor/buildflags/buildflags.h"
#include "chrome/browser/ui/views/location_bar/location_bar_view.h"

class HuhiActionsContainer;
class HuhiActionsContainerTest;
class RewardsBrowserTest;
class SkPath;

#if BUILDFLAG(ENABLE_TOR)
class OnionLocationView;
#endif

// The purposes of this subclass are to:
// - Add the HuhiActionsContainer to the location bar
class HuhiLocationBarView : public LocationBarView {
 public:
  using LocationBarView::LocationBarView;
  void Init() override;
  void Update(content::WebContents* contents) override;
  void OnChanged() override;
  HuhiActionsContainer* GetHuhiActionsContainer() { return huhi_actions_; }
#if BUILDFLAG(ENABLE_TOR)
  OnionLocationView* GetOnionLocationView() { return onion_location_view_; }
#endif

  // LocationBarView:
  std::vector<views::View*> GetTrailingViews() override;

  // views::View:
  gfx::Size CalculatePreferredSize() const override;
  void OnThemeChanged() override;
  void ChildPreferredSizeChanged(views::View* child) override;

  int GetBorderRadius() const override;

  SkPath GetFocusRingHighlightPath() const;
  ContentSettingImageView* GetContentSettingsImageViewForTesting(size_t idx);

 private:
  friend class ::HuhiActionsContainerTest;
  friend class ::RewardsBrowserTest;
  HuhiActionsContainer* huhi_actions_ = nullptr;
#if BUILDFLAG(ENABLE_TOR)
  OnionLocationView* onion_location_view_ = nullptr;
#endif

  DISALLOW_COPY_AND_ASSIGN(HuhiLocationBarView);
};

#endif  // HUHI_BROWSER_UI_VIEWS_LOCATION_BAR_HUHI_LOCATION_BAR_VIEW_H_
