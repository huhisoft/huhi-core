/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "extensions/buildflags/buildflags.h"

#if BUILDFLAG(ENABLE_EXTENSIONS)
#include "chrome/browser/ui/views/location_bar/location_bar_view.h"
#include "huhi/browser/ui/views/location_bar/huhi_location_bar_view.h"
#include "chrome/browser/ui/views/profiles/avatar_toolbar_button.h"
#include "huhi/browser/ui/views/profiles/huhi_avatar_toolbar_button.h"

#define LocationBarView HuhiLocationBarView
#include "../../../../../../../chrome/browser/ui/views/toolbar/toolbar_view.cc" // NOLINT
#undef LocationBarView
#endif
