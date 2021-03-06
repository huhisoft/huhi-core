/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/browser/ui/startup/google_api_keys_infobar_delegate.h"
#include "components/infobars/core/confirm_infobar_delegate.h"

#define GoogleApiKeysInfoBarDelegate HuhiGoogleKeysInfoBarDelegate

class HuhiGoogleKeysInfoBarDelegate {
 public:
  static void Create(InfoBarService* infobar_service) {
    // lulz
  }
};

#define HUHI_STARTUPBROWSERCREATORIMPL_DETERMINEURLSANDLAUNCH \
  welcome_enabled = true;

#include "../../../../../../chrome/browser/ui/startup/startup_browser_creator_impl.cc"  // NOLINT

#undef HUHI_STARTUPBROWSERCREATORIMPL_DETERMINEURLSANDLAUNCH
#undef GoogleApiKeysInfoBarDelegate
