/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/ui/views/profiles/huhi_incognito_menu_view.h"
#include "huhi/browser/ui/views/profiles/huhi_profile_menu_view.h"

#include "chrome/browser/ui/views/profiles/incognito_menu_view.h"
#include "chrome/browser/ui/views/profiles/profile_menu_view.h"

#define IncognitoMenuView HuhiIncognitoMenuView
#define ProfileMenuView HuhiProfileMenuView
#include "../../../../../../../chrome/browser/ui/views/profiles/profile_menu_view_base.cc"  // NOLINT
#undef IncognitoMenuView
#undef ProfileMenuView
