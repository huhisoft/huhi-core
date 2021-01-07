/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_VIEWS_TABS_HUHI_ALERT_INDICATOR_H_
#define HUHI_BROWSER_UI_VIEWS_TABS_HUHI_ALERT_INDICATOR_H_

#include "chrome/browser/ui/views/tabs/alert_indicator.h"

class HuhiAlertIndicator : public AlertIndicator {
 public:
  explicit HuhiAlertIndicator(Tab* parent_tab);

 private:
  class HuhiAlertBackground;

  // views::View overrides:
  bool OnMousePressed(const ui::MouseEvent& event) override;
  void OnMouseReleased(const ui::MouseEvent& event) override;
  void OnMouseEntered(const ui::MouseEvent& event) override;
  void OnMouseExited(const ui::MouseEvent& event) override;
  bool OnMouseDragged(const ui::MouseEvent& event) override;

  SkColor GetBackgroundColor() const;

  bool IsTabAudioToggleable() const;

  bool mouse_pressed_ = false;

  DISALLOW_COPY_AND_ASSIGN(HuhiAlertIndicator);
};

#endif  // HUHI_BROWSER_UI_VIEWS_TABS_HUHI_ALERT_INDICATOR_H_
