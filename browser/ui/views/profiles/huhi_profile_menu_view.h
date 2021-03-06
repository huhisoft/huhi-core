/* Copyright 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_VIEWS_PROFILES_HUHI_PROFILE_MENU_VIEW_H_
#define HUHI_BROWSER_UI_VIEWS_PROFILES_HUHI_PROFILE_MENU_VIEW_H_

#include "chrome/browser/ui/views/profiles/profile_menu_view.h"

class HuhiProfileMenuView : public ProfileMenuView {
 private:
  friend class ProfileMenuView;

  using ProfileMenuView::ProfileMenuView;
  ~HuhiProfileMenuView() override = default;

  // Button/link actions.
  void OnExitProfileButtonClicked() override;

  // Helper methods for building the menu.
  void BuildIdentity() override;
  void BuildAutofillButtons() override;
  void BuildSyncInfo() override;
  void BuildFeatureButtons() override;
  gfx::ImageSkia GetSyncIcon() const override;

  DISALLOW_COPY_AND_ASSIGN(HuhiProfileMenuView);
};

#endif  // HUHI_BROWSER_UI_VIEWS_PROFILES_HUHI_PROFILE_MENU_VIEW_H_
