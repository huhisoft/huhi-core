/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

// It has caller in the same file
#define HUHI_GET_SETTINGS_URL \
GURL GetSettingsUrl_ChromiumImpl(const std::string& sub_page) {
// HUHI_GET_SETTINGS_URL

#include "../../../../../chrome/browser/ui/chrome_pages.cc"

#undef HUHI_GET_SETTINGS_URL

#include "huhi/common/webui_url_constants.h"

namespace chrome {

GURL GetSettingsUrl(const std::string& sub_page) {
  if (sub_page == chrome::kSyncSetupSubPage)
    return chrome::GetSettingsUrl(kHuhiSyncSetupPath);
  return GetSettingsUrl_ChromiumImpl(sub_page);
}

}  // namespace chrome
