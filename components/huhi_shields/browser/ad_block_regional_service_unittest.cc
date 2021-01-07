/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/components/huhi_shields/browser/ad_block_service_helper.h"
#include "huhi/vendor/adblock_rust_ffi/src/wrapper.hpp"
#include "testing/gtest/include/gtest/gtest.h"

TEST(AdBlockRegionalServiceTest, UserModelLanguages) {
  std::vector<adblock::FilterList> catalog = std::vector<adblock::FilterList>();
  catalog.push_back(adblock::FilterList("uuid",
                                        "https://hnq.vn",
                                        "Testing Filter List",
                                        {"fr"},
                                        "https://support.hnq.vn",
                                        "componentid",
                                        "base64publickey",
                                        "Filter list for testing purposes"));

  std::vector<std::string> languages({ "fr", "fR", "fr-FR", "fr-ca" });
  std::for_each(languages.begin(), languages.end(),
      [&](const std::string& language) {
    EXPECT_TRUE(huhi_shields::FindAdBlockFilterListByLocale(catalog, language)
        != catalog.end());
  });
}
