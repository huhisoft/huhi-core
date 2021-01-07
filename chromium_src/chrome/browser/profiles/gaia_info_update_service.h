/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_CHROME_BROWSER_PROFILES_GAIA_INFO_UPDATE_SERVICE_H_
#define HUHI_CHROMIUM_SRC_CHROME_BROWSER_PROFILES_GAIA_INFO_UPDATE_SERVICE_H_

#define ShouldUseGAIAProfileInfo                           \
  ShouldUseGAIAProfileInfo_ChromiumImpl(Profile* profile); \
  static bool ShouldUseGAIAProfileInfo
#include "../../../../../chrome/browser/profiles/gaia_info_update_service.h"
#undef ShouldUseGAIAProfileInfo

#endif  // HUHI_CHROMIUM_SRC_CHROME_BROWSER_PROFILES_GAIA_INFO_UPDATE_SERVICE_H_
