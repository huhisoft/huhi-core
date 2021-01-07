/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_VIEWS_PROFILES_HUHI_AVATAR_TOOLBAR_BUTTON_H_
#define HUHI_BROWSER_UI_VIEWS_PROFILES_HUHI_AVATAR_TOOLBAR_BUTTON_H_

#include "chrome/browser/ui/views/profiles/avatar_toolbar_button.h"

class HuhiAvatarToolbarButton : public AvatarToolbarButton {
 public:
  using AvatarToolbarButton::AvatarToolbarButton;

  // ToolbarButton:
  void SetHighlight(const base::string16& highlight_text,
                    base::Optional<SkColor> highlight_color) override;

 private:
  ui::ImageModel GetAvatarIcon(
      ButtonState state,
      const gfx::Image& profile_identity_image) const override;
  DISALLOW_COPY_AND_ASSIGN(HuhiAvatarToolbarButton);
};

#endif  // HUHI_BROWSER_UI_VIEWS_PROFILES_HUHI_AVATAR_TOOLBAR_BUTTON_H_
