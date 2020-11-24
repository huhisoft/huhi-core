/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/ui/views/profiles/huhi_avatar_toolbar_button.h"

#include "huhi/app/vector_icons/vector_icons.h"
#include "huhi/browser/profiles/profile_util.h"
#include "chrome/app/vector_icons/vector_icons.h"
#include "chrome/browser/themes/theme_properties.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/views/profiles/avatar_toolbar_button.h"
#include "ui/base/pointer/touch_ui_controller.h"
#include "ui/base/theme_provider.h"
#include "ui/gfx/image/image.h"
#include "ui/gfx/paint_vector_icon.h"

void HuhiAvatarToolbarButton::SetHighlight(
    const base::string16& highlight_text,
    base::Optional<SkColor> highlight_color) {
  // We only want the icon for Tor and Guest profiles.
  AvatarToolbarButton::SetHighlight((huhi::IsTorProfile(browser_->profile()) ||
                                     browser_->profile()->IsGuestSession())
                                        ? base::string16()
                                        : highlight_text,
                                    highlight_color);
}

ui::ImageModel HuhiAvatarToolbarButton::GetAvatarIcon(
    ButtonState state,
    const gfx::Image& gaia_account_image) const {
  if (huhi::IsTorProfile(browser_->profile()) ||
      browser_->profile()->IsGuestSession()) {
    const int icon_size = ui::TouchUiController::Get()->touch_ui() ? 24 : 20;
    const SkColor icon_color = GetForegroundColor(state);
    return ui::ImageModel::FromVectorIcon(
        huhi::IsTorProfile(browser_->profile()) ? kTorProfileIcon
                                                 : kUserMenuGuestIcon,
        icon_color, icon_size);
  }
  return AvatarToolbarButton::GetAvatarIcon(state, gaia_account_image);
}
