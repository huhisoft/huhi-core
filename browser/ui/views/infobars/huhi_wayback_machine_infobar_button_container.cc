/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/ui/views/infobars/huhi_wayback_machine_infobar_button_container.h"

#include <memory>

#include "huhi/browser/ui/views/infobars/huhi_wayback_machine_infobar_throbber.h"
#include "huhi/grit/huhi_generated_resources.h"
#include "chrome/browser/ui/views/chrome_layout_provider.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/views/controls/button/md_text_button.h"
#include "ui/views/view_class_properties.h"

namespace {
constexpr int kThrobberDiameter = 16;
constexpr int kInsetOffsetsForThrobber = kThrobberDiameter;
}  // namespace

HuhiWaybackMachineInfoBarButtonContainer::
HuhiWaybackMachineInfoBarButtonContainer(views::ButtonListener* listener) {
  auto button = std::make_unique<views::MdTextButton>(
      listener,
      l10n_util::GetStringUTF16(IDS_HUHI_WAYBACK_MACHINE_CHECK_BUTTON_TEXT));
  button_ = button.get();
  button->SetProminent(true);
  button->SizeToPreferredSize();
  AddChildView(button.release());

  throbber_ = new HuhiWaybackMachineInfoBarThrobber;
  throbber_->SetSize(gfx::Size(kThrobberDiameter, kThrobberDiameter));
  throbber_->SetVisible(false);
  button_->AddChildView(throbber_);
}

HuhiWaybackMachineInfoBarButtonContainer::
~HuhiWaybackMachineInfoBarButtonContainer() {
}

void HuhiWaybackMachineInfoBarButtonContainer::Layout() {
  if (throbber_->GetVisible()) {
    int x = button_->width() - throbber_->width() - kThrobberDiameter / 2;
    int y = (button_->height() - throbber_->height()) / 2;
    throbber_->SetPosition(gfx::Point(x, y));
  }
}

gfx::Size
HuhiWaybackMachineInfoBarButtonContainer::CalculatePreferredSize() const {
  // This container doesn't need more space than button because throbber is
  // drawn over the button.
  return button_->GetPreferredSize();
}

void HuhiWaybackMachineInfoBarButtonContainer::StartThrobber() {
  AdjustButtonInsets(true);
  throbber_->SetVisible(true);
  throbber_->Start();
  Layout();
}

void HuhiWaybackMachineInfoBarButtonContainer::StopThrobber() {
  AdjustButtonInsets(false);
  throbber_->SetVisible(false);
  throbber_->Stop();
  Layout();
}

void HuhiWaybackMachineInfoBarButtonContainer::AdjustButtonInsets(
    bool add_insets) {
  const gfx::Insets insets_offset =
      gfx::Insets(0, 0, 0, kInsetOffsetsForThrobber);
  const gfx::Insets button_insets =
      add_insets ? button_->GetInsets() + insets_offset
                 : button_->GetInsets() - insets_offset;
  button_->SetBorder(views::CreateEmptyBorder(button_insets));
  button_->SizeToPreferredSize();
}
