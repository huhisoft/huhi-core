/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_VIEWS_INFOBARS_HUHI_WAYBACK_MACHINE_INFOBAR_CONTENTS_VIEW_H_
#define HUHI_BROWSER_UI_VIEWS_INFOBARS_HUHI_WAYBACK_MACHINE_INFOBAR_CONTENTS_VIEW_H_

#include <vector>

#include "huhi/components/huhi_wayback_machine/wayback_machine_url_fetcher.h"
#include "ui/views/controls/button/button.h"

namespace content {
class WebContents;
}  // namespace content

namespace views {
class ImageView;
class Label;
}  // namespace views

class HuhiWaybackMachineInfoBarButtonContainer;
class GURL;

// Includes all view controls except close button that managed by InfoBarView.
class HuhiWaybackMachineInfoBarContentsView
    : public views::View,
      public views::ButtonListener,
      public WaybackMachineURLFetcher::Client {
 public:
  explicit HuhiWaybackMachineInfoBarContentsView(
      content::WebContents* contents);
  ~HuhiWaybackMachineInfoBarContentsView() override;

  HuhiWaybackMachineInfoBarContentsView(
      const HuhiWaybackMachineInfoBarContentsView&) = delete;
  HuhiWaybackMachineInfoBarContentsView& operator=(
      const HuhiWaybackMachineInfoBarContentsView&) = delete;

 private:
  using Labels = std::vector<views::Label*>;
  using Views = std::vector<views::View*>;

  // views::View overrides:
  void OnThemeChanged() override;
  void ButtonPressed(views::Button* sender, const ui::Event& event) override;

  // WaybackMachineURLFetcher::Client overrides:
  void OnWaybackURLFetched(const GURL& latest_wayback_url) override;

  void InitializeChildren();
  views::Label* CreateLabel(const base::string16& text);
  SkColor GetColor(int id) const;
  void UpdateChildrenVisibility(bool show_before_checking_views);
  void FetchWaybackURL();
  void LoadURL(const GURL& url);
  void HideInfobar();

  // Used for labels theme changing all together.
  Labels labels_;
  Views views_visible_before_checking_;
  Views views_visible_after_checking_;
  content::WebContents* contents_;
  WaybackMachineURLFetcher wayback_machine_url_fetcher_;

  HuhiWaybackMachineInfoBarButtonContainer* button_ = nullptr;
  views::ImageView* wayback_spot_graphic_ = nullptr;
  bool wayback_url_fetch_requested_ = false;
};

#endif  // HUHI_BROWSER_UI_VIEWS_INFOBARS_HUHI_WAYBACK_MACHINE_INFOBAR_CONTENTS_VIEW_H_
