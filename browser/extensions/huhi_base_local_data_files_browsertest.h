/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_EXTENSIONS_HUHI_BASE_LOCAL_DATA_FILES_BROWSERTEST_H_
#define HUHI_BROWSER_EXTENSIONS_HUHI_BASE_LOCAL_DATA_FILES_BROWSERTEST_H_

#include "huhi/components/huhi_component_updater/browser/local_data_files_observer.h"
#include "chrome/browser/extensions/extension_browsertest.h"

using huhi_component_updater::LocalDataFilesObserver;
using extensions::ExtensionBrowserTest;

// This is an abstract base class that centralizes functions common to all
// LocalDataFiles-related extension browser tests.
class BaseLocalDataFilesBrowserTest : public ExtensionBrowserTest {
 public:
  BaseLocalDataFilesBrowserTest() {}

  // ExtensionBrowserTest overrides
  void SetUp() override;
  void SetUpOnMainThread() override;
  void PreRunTestOnMainThread() override;

 protected:
  virtual void WaitForService();
  void GetTestDataDir(base::FilePath* test_data_dir);
  void MaybeInitEmbeddedTestServer();
  void MaybeSetUpEmbeddedTestServerOnMainThread();
  bool InstallMockExtension();

  // Descendant classes must override these
  virtual const char* test_data_directory() = 0;
  virtual const char* embedded_test_server_directory() = 0;
  virtual LocalDataFilesObserver* service() = 0;
};

#endif  // HUHI_BROWSER_EXTENSIONS_HUHI_BASE_LOCAL_DATA_FILES_BROWSERTEST_H_
