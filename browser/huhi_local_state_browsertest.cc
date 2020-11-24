/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/tor/buildflags.h"
#include "chrome/browser/browser_process.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "content/public/test/browser_test.h"

#if BUILDFLAG(ENABLE_TOR)
#include "huhi/browser/tor/tor_profile_service.h"
#endif

using HuhiLocalStateBrowserTest = InProcessBrowserTest;

IN_PROC_BROWSER_TEST_F(HuhiLocalStateBrowserTest, BasicTest) {
#if BUILDFLAG(ENABLE_TOR)
    // Tor is enabled by default.
  EXPECT_FALSE(tor::TorProfileService::IsTorDisabled());
#endif
}
