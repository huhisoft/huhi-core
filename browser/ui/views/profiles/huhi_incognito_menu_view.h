/* Copyright 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_VIEWS_PROFILES_HUHI_INCOGNITO_MENU_VIEW_H_
#define HUHI_BROWSER_UI_VIEWS_PROFILES_HUHI_INCOGNITO_MENU_VIEW_H_

#include "chrome/browser/ui/views/profiles/incognito_menu_view.h"

class HuhiIncognitoMenuView : public IncognitoMenuView {
 public:
  using IncognitoMenuView::IncognitoMenuView;
  ~HuhiIncognitoMenuView() override = default;

  // ProfileMenuViewBase:
  void BuildMenu() override;

 private:
  friend class IncognitoMenuView;

  // views::BubbleDialogDelegateView:
  base::string16 GetAccessibleWindowTitle() const override;

    // Button actions.
  void OnExitButtonClicked() override;

  void AddTorButton();
  void OnTorProfileButtonClicked();

  DISALLOW_COPY_AND_ASSIGN(HuhiIncognitoMenuView);
};

#endif  // HUHI_BROWSER_UI_VIEWS_PROFILES_HUHI_INCOGNITO_MENU_VIEW_H_
