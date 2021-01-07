/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/ui/views/location_bar/huhi_location_bar_view.h"

#include <memory>

#include "huhi/browser/profiles/profile_util.h"
#include "huhi/browser/themes/huhi_theme_service.h"
#include "huhi/browser/ui/views/huhi_actions/huhi_actions_container.h"
#include "huhi/browser/ui/views/toolbar/huhi_toolbar_view.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/themes/theme_service_factory.h"
#include "chrome/browser/ui/layout_constants.h"
#include "chrome/browser/ui/omnibox/omnibox_theme.h"
#include "chrome/browser/ui/views/chrome_layout_provider.h"
#include "chrome/browser/ui/views/location_bar/location_bar_view.h"
#include "components/version_info/channel.h"
#include "ui/views/controls/highlight_path_generator.h"

#if BUILDFLAG(ENABLE_TOR)
#include "huhi/browser/ui/views/location_bar/onion_location_view.h"
#endif

namespace {

class HuhiLocationBarViewFocusRingHighlightPathGenerator
    : public views::HighlightPathGenerator {
 public:
  HuhiLocationBarViewFocusRingHighlightPathGenerator() = default;

  // HighlightPathGenerator
  SkPath GetHighlightPath(const views::View* view) override {
    return static_cast<const HuhiLocationBarView*>(view)
        ->GetFocusRingHighlightPath();
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(HuhiLocationBarViewFocusRingHighlightPathGenerator);
};

}  // namespace

void HuhiLocationBarView::Init() {
  // base method calls Update and Layout
  LocationBarView::Init();
  // Change focus ring highlight path
  if (focus_ring_) {
    focus_ring_->SetPathGenerator(
        std::make_unique<
            HuhiLocationBarViewFocusRingHighlightPathGenerator>());
  }
#if BUILDFLAG(ENABLE_TOR)
  onion_location_view_ = new OnionLocationView(browser_->profile());
  AddChildView(onion_location_view_);
#endif
  // huhi action buttons
  huhi_actions_ = new HuhiActionsContainer(browser_, profile());
  huhi_actions_->Init();
  AddChildView(huhi_actions_);
  // Call Update again to cause a Layout
  Update(nullptr);

  // Stop slide animation for all content settings views icon.
  for (auto* content_setting_view : content_setting_views_)
    content_setting_view->disable_animation();
}

void HuhiLocationBarView::Update(content::WebContents* contents) {
  // base Init calls update before our Init is run, so our children
  // may not be initialized yet
  if (huhi_actions_) {
    huhi_actions_->Update();
  }
#if BUILDFLAG(ENABLE_TOR)
  if (onion_location_view_)
    onion_location_view_->Update(contents);
#endif
  LocationBarView::Update(contents);
}

void HuhiLocationBarView::OnChanged() {
  if (huhi_actions_) {
    // Do not show actions whilst omnibar is open or url is being edited
    const bool should_hide =
        ShouldHidePageActionIcons() && !omnibox_view_->GetText().empty();
    huhi_actions_->SetShouldHide(should_hide);
  }
#if BUILDFLAG(ENABLE_TOR)
  if (onion_location_view_)
    onion_location_view_->Update(
        browser_->tab_strip_model()->GetActiveWebContents());
#endif

  // OnChanged calls Layout
  LocationBarView::OnChanged();
}

std::vector<views::View*> HuhiLocationBarView::GetTrailingViews() {
  std::vector<views::View*> views;
#if BUILDFLAG(ENABLE_TOR)
  if (onion_location_view_)
    views.push_back(onion_location_view_);
#endif
  if (huhi_actions_)
    views.push_back(huhi_actions_);

  return views;
}

gfx::Size HuhiLocationBarView::CalculatePreferredSize() const {
  gfx::Size min_size = LocationBarView::CalculatePreferredSize();
  if (huhi_actions_ && huhi_actions_->GetVisible()) {
    const int huhi_actions_min = huhi_actions_->GetMinimumSize().width();
    const int extra_width = huhi_actions_min +
                              GetLayoutConstant(LOCATION_BAR_ELEMENT_PADDING);
    min_size.Enlarge(extra_width, 0);
  }
#if BUILDFLAG(ENABLE_TOR)
  if (onion_location_view_ && onion_location_view_->GetVisible()) {
    const int extra_width = GetLayoutConstant(LOCATION_BAR_ELEMENT_PADDING) +
        onion_location_view_->GetMinimumSize().width();
    min_size.Enlarge(extra_width, 0);
  }
#endif
  return min_size;
}

void HuhiLocationBarView::OnThemeChanged() {
  LocationBarView::OnThemeChanged();

  if (!IsInitialized())
    return;

  Update(nullptr);
  RefreshBackground();
}

void HuhiLocationBarView::ChildPreferredSizeChanged(views::View* child) {
  LocationBarView::ChildPreferredSizeChanged(child);

  if (child != huhi_actions_)
    return;

  Layout();
}

int HuhiLocationBarView::GetBorderRadius() const {
  return ChromeLayoutProvider::Get()->GetCornerRadiusMetric(
      views::EMPHASIS_HIGH, size());
}

SkPath HuhiLocationBarView::GetFocusRingHighlightPath() const {
  const SkScalar radius = GetBorderRadius();
  return SkPath().addRoundRect(gfx::RectToSkRect(GetLocalBounds()),
                               radius, radius);
}

ContentSettingImageView*
HuhiLocationBarView::GetContentSettingsImageViewForTesting(size_t idx) {
  DCHECK(idx < content_setting_views_.size());
  return content_setting_views_[idx];
}
