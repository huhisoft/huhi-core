/* Copyright 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_EXTENSIONS_HUHI_EXTENSION_FUNCTIONAL_TEST_H_
#define HUHI_BROWSER_EXTENSIONS_HUHI_EXTENSION_FUNCTIONAL_TEST_H_

#include "base/files/file_path.h"
#include "chrome/browser/extensions/extension_browsertest.h"
#include "chrome/browser/extensions/extension_service.h"

namespace extensions {

class ExtensionFunctionalTest : public ExtensionBrowserTest {
 public:
  scoped_refptr<const Extension> InstallExtensionSilently(
      ExtensionService* service,
      const base::FilePath& path);
  void SetUp() override;
  void InitEmbeddedTestServer();
  void GetTestDataDir(base::FilePath* test_data_dir);
};

}  // namespace extensions

#endif  // HUHI_BROWSER_EXTENSIONS_HUHI_EXTENSION_FUNCTIONAL_TEST_H_
