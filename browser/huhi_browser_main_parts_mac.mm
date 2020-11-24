/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/huhi_browser_main_parts_mac.h"

#include "huhi/browser/sparkle_buildflags.h"

#if BUILDFLAG(ENABLE_SPARKLE)
#import "huhi/browser/mac/sparkle_glue.h"
#endif

void HuhiBrowserMainPartsMac::PreMainMessageLoopStart() {
  ChromeBrowserMainPartsMac::PreMainMessageLoopStart();

#if BUILDFLAG(ENABLE_SPARKLE)
  // It would be no-op if udpate is disabled.
  [[SparkleGlue sharedSparkleGlue] registerWithSparkle];
#endif
}
