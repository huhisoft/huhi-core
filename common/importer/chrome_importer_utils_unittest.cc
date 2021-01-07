/* Copyright 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "base/files/file_path.h"
#include "base/files/file_util.h"
#include "base/json/json_reader.h"
#include "base/path_service.h"
#include "huhi/common/huhi_paths.h"
#include "huhi/common/importer/chrome_importer_utils.h"
#include "huhi/common/importer/importer_constants.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace {
// This sample prefs file is fetched after installing two extensions and one
// theme from webstore with fresh profile.
base::FilePath GetTestPreferencesPath() {
  base::FilePath test_dir;
  base::PathService::Get(huhi::DIR_TEST_DATA, &test_dir);
  return test_dir.AppendASCII("import").AppendASCII("chrome")
      .AppendASCII("default").AppendASCII(kChromeExtensionsPreferencesFile);
}
}  // namespace

TEST(ChromeImporterUtilsTest, BasicTest) {
  base::FilePath data_path;
  ASSERT_TRUE(base::PathService::Get(huhi::DIR_TEST_DATA, &data_path));
  base::FilePath secured_preference_path = GetTestPreferencesPath();

  std::string secured_preference_content;
  base::ReadFileToString(secured_preference_path, &secured_preference_content);
  base::Optional<base::Value> secured_preference =
      base::JSONReader::Read(secured_preference_content);
  auto* extensions = secured_preference->FindPath(kChromeExtensionsListPath);
  auto extensions_list =
      GetImportableListFromChromeExtensionsList(*extensions);
  // Only 2 extensions installed from webstore are importing target extensions.
  // We don't import theme, pre-installed extensions and installed by default.
  EXPECT_EQ(2UL, extensions_list.size());
}
