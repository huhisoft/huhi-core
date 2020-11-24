/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_PROFILES_INCOGNITO_MENU_VIEW_H_
#define HUHI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_PROFILES_INCOGNITO_MENU_VIEW_H_

#define HUHI_INCOGNITO_MENU_VIEW_H_   \
 private:                              \
  friend class HuhiIncognitoMenuView; \
                                       \
 public:
#define OnExitButtonClicked virtual OnExitButtonClicked
#include "../../../../../../../chrome/browser/ui/views/profiles/incognito_menu_view.h"
#undef OnExitButtonClicked
#undef HUHI_INCOGNITO_MENU_VIEW_H_

#endif  // HUHI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_PROFILES_INCOGNITO_MENU_VIEW_H_
