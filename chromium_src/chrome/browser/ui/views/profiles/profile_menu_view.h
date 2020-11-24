/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_PROFILES_PROFILE_MENU_VIEW_H_
#define HUHI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_PROFILES_PROFILE_MENU_VIEW_H_

#define HUHI_PROFILE_MENU_VIEW_H    \
  friend class HuhiProfileMenuView; \

#define OnExitProfileButtonClicked virtual OnExitProfileButtonClicked
#define BuildAutofillButtons virtual BuildAutofillButtons
#define BuildIdentity virtual BuildIdentity
#define BuildSyncInfo virtual BuildSyncInfo
#define BuildFeatureButtons virtual BuildFeatureButtons

#include "../../../../../../../chrome/browser/ui/views/profiles/profile_menu_view.h"
#undef BuildFeatureButtons
#undef BuildSyncInfo
#undef BuildIdentity
#undef BuildAutofillButtons
#undef OnExitProfileButtonClicked
#undef HUHI_PROFILE_MENU_VIEW_H

#endif  // HUHI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_PROFILES_PROFILE_MENU_VIEW_H_
