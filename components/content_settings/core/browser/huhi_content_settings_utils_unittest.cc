/*  Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <memory>

#include "base/macros.h"
#include "base/optional.h"
#include "huhi/components/content_settings/core/browser/huhi_content_settings_utils.h"
#include "chrome/test/base/testing_profile.h"
#include "components/content_settings/core/common/content_settings_pattern.h"
#include "content/public/test/browser_task_environment.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"

using content_settings::ConvertPatternToWildcardSchemeAndPort;

class HuhiContentSettingsUtilsTest : public testing::Test {
 public:
  HuhiContentSettingsUtilsTest() = default;
  ~HuhiContentSettingsUtilsTest() override = default;

  void SetUp() override { profile_ = std::make_unique<TestingProfile>(); }

  TestingProfile* profile() { return profile_.get(); }

 private:
  content::BrowserTaskEnvironment task_environment_;
  std::unique_ptr<TestingProfile> profile_;

  DISALLOW_COPY_AND_ASSIGN(HuhiContentSettingsUtilsTest);
};

TEST_F(HuhiContentSettingsUtilsTest,
       TestConvertPatternToWildcardSchemeAndPort) {
  // Full wildcard pattern.
  EXPECT_EQ(base::nullopt, ConvertPatternToWildcardSchemeAndPort(
                               ContentSettingsPattern::Wildcard()));

  // Huhi first party placeholder pattern.
  EXPECT_EQ(base::nullopt,
            ConvertPatternToWildcardSchemeAndPort(
                ContentSettingsPattern::FromString("https://firstParty/*")));

  // file:// scheme pattern.
  EXPECT_EQ(base::nullopt,
            ConvertPatternToWildcardSchemeAndPort(
                ContentSettingsPattern::FromString("file:///a/b/c.zip")));

  // Wildcard host pattern.
  EXPECT_EQ(base::nullopt,
            ConvertPatternToWildcardSchemeAndPort(
                ContentSettingsPattern::FromString("http://*:8080/*")));

  // Wildcard scheme, no port.
  EXPECT_EQ(base::nullopt,
            ConvertPatternToWildcardSchemeAndPort(
                ContentSettingsPattern::FromString("*://huhisoft.com/*")));
  EXPECT_EQ(base::nullopt,
            ConvertPatternToWildcardSchemeAndPort(
                ContentSettingsPattern::FromString("*://huhisoft.com:*/")));

  // Wildcard scheme, has port.
  auto pattern = ConvertPatternToWildcardSchemeAndPort(
      ContentSettingsPattern::FromString("*://huhisoft.com:8080/*"));
  EXPECT_NE(base::nullopt, pattern);
  EXPECT_EQ(pattern->ToString(), "huhisoft.com");
  EXPECT_TRUE(pattern->Matches(GURL("http://huhisoft.com:80/path1")));
  EXPECT_TRUE(pattern->Matches(GURL("https://huhisoft.com/path2")));
  EXPECT_FALSE(pattern->Matches(GURL("http://huhisoft.com:8080")));
  pattern.reset();

  // Scheme, no port.
  pattern = ConvertPatternToWildcardSchemeAndPort(
      ContentSettingsPattern::FromString("http://huhisoft.com/"));
  EXPECT_NE(base::nullopt, pattern);
  EXPECT_EQ(pattern->ToString(), "huhisoft.com");
  EXPECT_TRUE(pattern->Matches(GURL("ftp://huhisoft.com:80/path1")));
  EXPECT_TRUE(pattern->Matches(GURL("https://huhisoft.com/path2")));
  EXPECT_FALSE(pattern->Matches(GURL("http://huhisoft.com:8080")));
  pattern.reset();

  // Scheme and port.
  pattern = ConvertPatternToWildcardSchemeAndPort(
      ContentSettingsPattern::FromString("https://huhisoft.com:56558/"));
  EXPECT_NE(base::nullopt, pattern);
  EXPECT_EQ(pattern->ToString(), "huhisoft.com");
  EXPECT_TRUE(pattern->Matches(GURL("wss://huhisoft.com:80/path1")));
  EXPECT_TRUE(pattern->Matches(GURL("https://huhisoft.com/path2")));
  EXPECT_FALSE(pattern->Matches(GURL("http://huhisoft.com:8080")));
}
