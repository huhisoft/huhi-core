/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/ui/omnibox/huhi_omnibox_client_impl.h"

#define HUHI_LAYOUT_TRAILING_DECORATIONS     \
  if (right_most && right_most->GetVisible()) \
    trailing_decorations.AddDecoration(0, height(), false, 0, 0, right_most);

#define ChromeOmniboxClient HuhiOmniboxClientImpl
#include "../../../../../../../chrome/browser/ui/views/location_bar/location_bar_view.cc"
#undef ChromeOmniboxClient
#undef HUHI_LAYOUT_TRAILING_DECORATIONS
