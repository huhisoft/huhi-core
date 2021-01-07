/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_VIEWS_INFOBARS_HUHI_WAYBACK_MACHINE_INFOBAR_BUTTON_CONTAINER_H_
#define HUHI_BROWSER_UI_VIEWS_INFOBARS_HUHI_WAYBACK_MACHINE_INFOBAR_BUTTON_CONTAINER_H_

#include "ui/views/view.h"

namespace views {
class ButtonListener;
}  // namespace views

class HuhiWaybackMachineInfoBarThrobber;

// This manages button and throbber controls.
// buttons occupies all this containers area and throbber runs over the button.
// When throbbing is requested, button extends its right inset and throbber runs
// on that area.
class HuhiWaybackMachineInfoBarButtonContainer : public views::View {
 public:
  explicit HuhiWaybackMachineInfoBarButtonContainer(
      views::ButtonListener* listener);
  ~HuhiWaybackMachineInfoBarButtonContainer() override;

  HuhiWaybackMachineInfoBarButtonContainer(
      const HuhiWaybackMachineInfoBarButtonContainer&) = delete;
  HuhiWaybackMachineInfoBarButtonContainer& operator=(
      const HuhiWaybackMachineInfoBarButtonContainer&) = delete;

  void StartThrobber();
  void StopThrobber();

  // views::View overrides:
  void Layout() override;
  gfx::Size CalculatePreferredSize() const override;

 private:
  void AdjustButtonInsets(bool add_insets);

  HuhiWaybackMachineInfoBarThrobber* throbber_ = nullptr;
  views::View* button_ = nullptr;
};

#endif  // HUHI_BROWSER_UI_VIEWS_INFOBARS_HUHI_WAYBACK_MACHINE_INFOBAR_BUTTON_CONTAINER_H_
