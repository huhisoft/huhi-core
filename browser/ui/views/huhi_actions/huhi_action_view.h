/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_VIEWS_HUHI_ACTIONS_HUHI_ACTION_VIEW_H_
#define HUHI_BROWSER_UI_VIEWS_HUHI_ACTIONS_HUHI_ACTION_VIEW_H_

#include "chrome/browser/ui/views/toolbar/toolbar_action_view.h"

namespace gfx {
class Rect;
}

// Subclasses ToolbarActionViewc so that the notification badge can be painted
// outside the highlight bubble.
class HuhiActionView : public ToolbarActionView {
 public:
  HuhiActionView(ToolbarActionViewController* view_controller,
                  ToolbarActionView::Delegate* delegate);

  SkPath GetHighlightPath() const;

  DISALLOW_COPY_AND_ASSIGN(HuhiActionView);
};

#endif  // HUHI_BROWSER_UI_VIEWS_HUHI_ACTIONS_HUHI_ACTION_VIEW_H_
