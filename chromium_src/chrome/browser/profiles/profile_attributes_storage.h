/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_CHROME_BROWSER_PROFILES_PROFILE_ATTRIBUTES_STORAGE_H_
#define HUHI_CHROMIUM_SRC_CHROME_BROWSER_PROFILES_PROFILE_ATTRIBUTES_STORAGE_H_

#include "huhi/browser/profiles/huhi_profile_avatar_downloader.h"

#define ProfileAvatarDownloader HuhiProfileAvatarDownloader
#include "../../../../../chrome/browser/profiles/profile_attributes_storage.h"
#undef ProfileAvatarDownloader

#endif  // HUHI_CHROMIUM_SRC_CHROME_BROWSER_PROFILES_PROFILE_ATTRIBUTES_STORAGE_H_
