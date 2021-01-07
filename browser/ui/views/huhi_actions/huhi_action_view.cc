/* Copyright 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/ui/views/huhi_actions/huhi_action_view.h"

#include <memory>

#include "chrome/browser/themes/theme_properties.h"
#include "chrome/browser/ui/layout_constants.h"
#include "chrome/browser/ui/views/chrome_layout_provider.h"
#include "chrome/browser/ui/views/toolbar/toolbar_action_view.h"
#include "chrome/browser/ui/views/toolbar/toolbar_ink_drop_util.h"
#include "extensions/common/constants.h"
#include "third_party/skia/include/core/SkPath.h"
#include "ui/gfx/geometry/insets.h"
#include "ui/gfx/geometry/rect.h"
#include "ui/gfx/geometry/size.h"
#include "ui/views/controls/button/menu_button.h"
#include "ui/views/controls/highlight_path_generator.h"
#include "ui/views/view.h"
#include "ui/views/view_class_properties.h"

namespace {

class HuhiActionViewHighlightPathGenerator
    : public views::HighlightPathGenerator {
 public:
  HuhiActionViewHighlightPathGenerator() = default;

  // HighlightPathGenerator
  SkPath GetHighlightPath(const views::View* view) override {
    return static_cast<const HuhiActionView*>(view)->GetHighlightPath();
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(HuhiActionViewHighlightPathGenerator);
};

}  // namespace

HuhiActionView::HuhiActionView(ToolbarActionViewController* view_controller,
                                 ToolbarActionView::Delegate* delegate)
    : ToolbarActionView(view_controller, delegate) {
  views::HighlightPathGenerator::Install(
      this, std::make_unique<HuhiActionViewHighlightPathGenerator>());
}

SkPath HuhiActionView::GetHighlightPath() const {
  // Set the highlight path for the toolbar button,
  // making it inset so that the badge can show outside it in the
  // fake margin on the right that we are creating.
  SkPath path;
  gfx::Insets highlight_insets(0, 0, 0, kHuhiActionRightMargin);
  gfx::Rect rect(size());
  rect.Inset(highlight_insets);
  const int radii = ChromeLayoutProvider::Get()->GetCornerRadiusMetric(
      views::EMPHASIS_MAXIMUM, rect.size());
  path.addRoundRect(gfx::RectToSkRect(rect), radii, radii);
  return path;
}
