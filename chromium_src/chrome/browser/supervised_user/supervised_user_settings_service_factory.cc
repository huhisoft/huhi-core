/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "huhi/browser/profiles/profile_util.h"

// Use the same SupervisedUserSettingsService, which handles a part of
// preferences, as its parent profile. Chromium's incognito profile also shares
// it with its original profile.
#define HUHI_GET_KEY_TO_USE                                         \
  if (huhi::IsSessionProfilePath(key->GetPath())) {                 \
    return huhi::GetParentProfile(key->GetPath())->GetProfileKey(); \
  }

#include "../../../../../chrome/browser/supervised_user/supervised_user_settings_service_factory.cc"
