// Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Huhi Software
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#include "chrome/browser/profiles/profile_metrics.h"

#define LogProfileAvatarSelection LogProfileAvatarSelection_ChromiumImpl
#include "../../../../../chrome/browser/profiles/profile_metrics.cc"
#undef LogProfileAvatarSelection

// Chromium attempts to log profile icons which do not include
// Huhi's additions in profile_avatar_icon_util.cc
// Huhi does not need this histogram, so we don't do anything here.
// If we do want this histogram in the future then we can handle if the index
// is greater than chromium's max.
void ProfileMetrics::LogProfileAvatarSelection(size_t icon_index) { }
