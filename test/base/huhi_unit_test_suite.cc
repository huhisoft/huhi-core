/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/test/base/huhi_unit_test_suite.h"

#include "base/logging.h"
#include "huhi/common/huhi_paths.h"
#include "huhi/common/resource_bundle_helper.h"
#include "chrome/install_static/product_install_details.h"
#include "chrome/test/base/chrome_unit_test_suite.h"

HuhiUnitTestSuite::HuhiUnitTestSuite(int argc, char** argv)
    : ChromeUnitTestSuite(argc, argv) {}

void HuhiUnitTestSuite::Initialize() {
#if defined(OS_WIN) && defined(OFFICIAL_BUILD)
  // When ChromeExtensionsBrowserClient is initialized, it needs
  install_static::InitializeProductDetailsForPrimaryModule();
#endif
  ChromeUnitTestSuite::Initialize();

  huhi::InitializeResourceBundle();

  huhi::RegisterPathProvider();
}
