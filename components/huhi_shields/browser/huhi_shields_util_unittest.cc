/*  Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <memory>

#include "base/macros.h"
#include "huhi/components/huhi_shields/browser/huhi_shields_util.h"
#include "huhi/components/huhi_shields/common/huhi_shield_constants.h"
#include "build/build_config.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/test/base/testing_profile.h"
#include "components/content_settings/core/browser/host_content_settings_map.h"
#include "components/content_settings/core/common/content_settings_types.h"
#include "content/public/test/browser_task_environment.h"
#include "testing/gtest/include/gtest/gtest.h"

using huhi_shields::ControlType;
using huhi_shields::ControlTypeFromString;
using huhi_shields::ControlTypeToString;
using huhi_shields::GetPatternFromURL;

class HuhiShieldsUtilTest : public testing::Test {
 public:
  HuhiShieldsUtilTest() = default;
  ~HuhiShieldsUtilTest() override = default;

  void SetUp() override { profile_ = std::make_unique<TestingProfile>(); }

  TestingProfile* profile() { return profile_.get(); }

 private:
  content::BrowserTaskEnvironment task_environment_;
  std::unique_ptr<TestingProfile> profile_;

  DISALLOW_COPY_AND_ASSIGN(HuhiShieldsUtilTest);
};

TEST_F(HuhiShieldsUtilTest, GetPatternFromURL) {
  // wildcard
  auto pattern = GetPatternFromURL(GURL());
  EXPECT_EQ(ContentSettingsPattern::Wildcard(), pattern);

  // scheme is a wildcard, should match any scheme
  pattern = GetPatternFromURL(GURL("http://huhisoft.com"));
  EXPECT_TRUE(pattern.Matches(GURL("http://huhisoft.com")));
  EXPECT_TRUE(pattern.Matches(GURL("http://huhisoft.com/path1")));
  EXPECT_TRUE(pattern.Matches(GURL("http://huhisoft.com/path2")));
  EXPECT_TRUE(pattern.Matches(GURL("https://huhisoft.com")));
  EXPECT_TRUE(pattern.Matches(GURL("ftp://huhisoft.com")));
  EXPECT_FALSE(pattern.Matches(GURL("http://subdomain.huhisoft.com")));
  EXPECT_FALSE(pattern.Matches(GURL("http://huhisoft.com")));

  // path is a wildcard
  pattern = GetPatternFromURL(GURL("http://huhisoft.com/path1"));
  EXPECT_TRUE(pattern.Matches(GURL("http://huhisoft.com")));
  EXPECT_TRUE(pattern.Matches(GURL("http://huhisoft.com/path1")));
  EXPECT_TRUE(pattern.Matches(GURL("http://huhisoft.com/path2")));
  EXPECT_FALSE(pattern.Matches(GURL("http://subdomain.huhisoft.com")));
  EXPECT_FALSE(pattern.Matches(GURL("http://huhisoft.com")));

  // port is a wildcard
  pattern = GetPatternFromURL(GURL("http://huhisoft.com:8080"));
  EXPECT_TRUE(pattern.Matches(GURL("http://huhisoft.com")));
  EXPECT_TRUE(pattern.Matches(GURL("http://huhisoft.com:8080")));
  EXPECT_TRUE(pattern.Matches(GURL("http://huhisoft.com:8080/path1")));
  EXPECT_TRUE(pattern.Matches(GURL("http://huhisoft.com:8080/path2")));
  EXPECT_TRUE(pattern.Matches(GURL("http://huhisoft.com:5555")));
  EXPECT_TRUE(pattern.Matches(GURL("https://huhisoft.com")));
  EXPECT_TRUE(pattern.Matches(GURL("https://huhisoft.com:8080")));
  EXPECT_FALSE(pattern.Matches(GURL("http://subdomain.huhisoft.com")));
  EXPECT_FALSE(pattern.Matches(GURL("http://huhisoft.com")));

  // with implied port
  pattern = GetPatternFromURL(GURL("https://brianbondy.com"));
  EXPECT_EQ(pattern.ToString(), "brianbondy.com");
  pattern = GetPatternFromURL(GURL("http://brianbondy.com"));
  EXPECT_EQ(pattern.ToString(), "brianbondy.com");
  // with specified port
  pattern = GetPatternFromURL(GURL("http://brianbondy.com:8080"));
  EXPECT_EQ(pattern.ToString(), "brianbondy.com");
}

TEST_F(HuhiShieldsUtilTest, ControlTypeToString) {
  EXPECT_EQ("block", ControlTypeToString(ControlType::BLOCK));
  EXPECT_EQ("allow", ControlTypeToString(ControlType::ALLOW));
  EXPECT_EQ("block_third_party",
            ControlTypeToString(ControlType::BLOCK_THIRD_PARTY));
}

TEST_F(HuhiShieldsUtilTest, ControlTypeFromString) {
  EXPECT_EQ(ControlType::BLOCK, ControlTypeFromString("block"));
  EXPECT_EQ(ControlType::ALLOW, ControlTypeFromString("allow"));
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY,
            ControlTypeFromString("block_third_party"));
}

/* HUHI_SHIELDS CONTROL */
TEST_F(HuhiShieldsUtilTest, SetHuhiShieldsEnabled_ForOrigin) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  huhi_shields::SetHuhiShieldsEnabled(map,
                                        true,
                                        GURL("http://huhisoft.com"));
  // setting should apply to origin
  auto setting = map->GetContentSetting(GURL("http://huhisoft.com"), GURL(),
                                        ContentSettingsType::PLUGINS,
                                        huhi_shields::kHuhiShields);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  // setting should apply to different scheme
  setting = map->GetContentSetting(GURL("https://huhisoft.com"), GURL(),
                                   ContentSettingsType::PLUGINS,
                                   huhi_shields::kHuhiShields);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  // setting should not apply to default
  setting =
      map->GetContentSetting(GURL(), GURL(), ContentSettingsType::PLUGINS,
                             huhi_shields::kHuhiShields);
  EXPECT_EQ(CONTENT_SETTING_DEFAULT, setting);
}

TEST_F(HuhiShieldsUtilTest, SetHuhiShieldsEnabled_IsNotHttpHttps) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  auto setting = huhi_shields::GetHuhiShieldsEnabled(
      map, GURL("chrome://preferences"));
  EXPECT_EQ(false, setting);
  huhi_shields::SetHuhiShieldsEnabled(map,
                                        ControlType::ALLOW,
                                        GURL("chrome://preferences"));
  setting = huhi_shields::GetHuhiShieldsEnabled(map,
                                                  GURL("chrome://preferences"));
  EXPECT_EQ(false, setting);

  setting = huhi_shields::GetHuhiShieldsEnabled(map, GURL("about:blank"));
  EXPECT_EQ(false, setting);
  huhi_shields::SetHuhiShieldsEnabled(map,
                                        ControlType::ALLOW,
                                        GURL("about:blank"));
  setting =
      huhi_shields::GetHuhiShieldsEnabled(map, GURL("about:blank"));
  EXPECT_EQ(false, setting);
}

TEST_F(HuhiShieldsUtilTest, GetHuhiShieldsEnabled_ForOrigin) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  auto setting = huhi_shields::GetHuhiShieldsEnabled(map, GURL());
  EXPECT_EQ(true, setting);
  setting = huhi_shields::GetHuhiShieldsEnabled(map,
                                                  GURL("http://huhisoft.com"));
  EXPECT_EQ(true, setting);
  setting = huhi_shields::GetHuhiShieldsEnabled(map,
                                                  GURL("https://huhisoft.com"));
  EXPECT_EQ(true, setting);

  /* BLOCK */
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("http://huhisoft.com/*"),
      ContentSettingsPattern::Wildcard(), ContentSettingsType::PLUGINS,
      huhi_shields::kHuhiShields, CONTENT_SETTING_BLOCK);
  setting = huhi_shields::GetHuhiShieldsEnabled(map,
                                                  GURL("http://huhisoft.com/*"));
  EXPECT_EQ(false, setting);
  // https in unchanged
  setting = huhi_shields::GetHuhiShieldsEnabled(map,
                                                  GURL("https://huhisoft.com"));
  EXPECT_EQ(true, setting);
  // default is unchanged
  setting = huhi_shields::GetHuhiShieldsEnabled(map, GURL());
  EXPECT_EQ(true, setting);
}

TEST_F(HuhiShieldsUtilTest, GetHuhiShieldsEnabled_IsNotHttpHttps) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  auto setting = huhi_shields::GetHuhiShieldsEnabled(
      map, GURL("chrome://preferences"));
  EXPECT_EQ(false, setting);

  setting = huhi_shields::GetHuhiShieldsEnabled(map, GURL("about:blank"));
  EXPECT_EQ(false, setting);
}

/* AD CONTROL */
TEST_F(HuhiShieldsUtilTest, SetAdControlType_Default) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  // settings should be default
  auto setting = map->GetContentSetting(
      GURL(), GURL(), ContentSettingsType::PLUGINS, huhi_shields::kAds);
  EXPECT_EQ(CONTENT_SETTING_DEFAULT, setting);
  setting = map->GetContentSetting(GURL("http://huhisoft.com"), GURL(),
                                   ContentSettingsType::PLUGINS,
                                   huhi_shields::kAds);
  EXPECT_EQ(CONTENT_SETTING_DEFAULT, setting);

  /* ALLOW */
  huhi_shields::SetAdControlType(map, ControlType::ALLOW, GURL());
  setting = map->GetContentSetting(
      GURL(), GURL(), ContentSettingsType::PLUGINS, huhi_shields::kAds);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  // override should apply to all origins
  setting = map->GetContentSetting(GURL("http://huhisoft.com"), GURL(),
                                   ContentSettingsType::PLUGINS,
                                   huhi_shields::kAds);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  /* BLOCK */
  huhi_shields::SetAdControlType(map, ControlType::BLOCK, GURL());
  setting = map->GetContentSetting(
      GURL(), GURL(), ContentSettingsType::PLUGINS, huhi_shields::kAds);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);

  // override should apply to all origins
  setting = map->GetContentSetting(GURL("http://huhisoft.com"), GURL(),
                                   ContentSettingsType::PLUGINS,
                                   huhi_shields::kAds);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);
}

TEST_F(HuhiShieldsUtilTest, SetAdControlType_ForOrigin) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  huhi_shields::SetAdControlType(map, ControlType::ALLOW,
                                  GURL("http://huhisoft.com"));
  // setting should apply to origin
  auto setting = map->GetContentSetting(GURL("http://huhisoft.com"), GURL(),
                                        ContentSettingsType::PLUGINS,
                                        huhi_shields::kAds);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  // setting should also apply to different scheme
  setting = map->GetContentSetting(GURL("https://huhisoft.com"), GURL(),
                                   ContentSettingsType::PLUGINS,
                                   huhi_shields::kAds);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  // setting should not apply to default
  setting = map->GetContentSetting(
      GURL(), GURL(), ContentSettingsType::PLUGINS, huhi_shields::kAds);
  EXPECT_EQ(CONTENT_SETTING_DEFAULT, setting);
}

TEST_F(HuhiShieldsUtilTest, GetAdControlType_Default) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  auto setting = huhi_shields::GetAdControlType(map, GURL());
  EXPECT_EQ(ControlType::BLOCK, setting);

  /* ALLOW */
  map->SetContentSettingCustomScope(ContentSettingsPattern::Wildcard(),
                                    ContentSettingsPattern::Wildcard(),
                                    ContentSettingsType::PLUGINS,
                                    huhi_shields::kAds, CONTENT_SETTING_ALLOW);
  setting = huhi_shields::GetAdControlType(map, GURL());
  EXPECT_EQ(ControlType::ALLOW, setting);

  /* BLOCK */
  map->SetContentSettingCustomScope(ContentSettingsPattern::Wildcard(),
                                    ContentSettingsPattern::Wildcard(),
                                    ContentSettingsType::PLUGINS,
                                    huhi_shields::kAds, CONTENT_SETTING_BLOCK);
  setting = huhi_shields::GetAdControlType(map, GURL());
  EXPECT_EQ(ControlType::BLOCK, setting);
}

TEST_F(HuhiShieldsUtilTest, GetAdControlType_ForOrigin) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  auto setting = huhi_shields::GetAdControlType(map, GURL());
  EXPECT_EQ(ControlType::BLOCK, setting);
  setting = huhi_shields::GetAdControlType(map, GURL("http://huhisoft.com"));
  EXPECT_EQ(ControlType::BLOCK, setting);
  setting = huhi_shields::GetAdControlType(map, GURL("https://huhisoft.com"));
  EXPECT_EQ(ControlType::BLOCK, setting);

  /* ALLOW */
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("http://huhisoft.com/*"),
      ContentSettingsPattern::Wildcard(), ContentSettingsType::PLUGINS,
      huhi_shields::kAds, CONTENT_SETTING_ALLOW);
  setting =
      huhi_shields::GetAdControlType(map, GURL("http://huhisoft.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);

  // https in unchanged
  setting = huhi_shields::GetAdControlType(map, GURL("https://huhisoft.com"));
  EXPECT_EQ(ControlType::BLOCK, setting);
  // default is unchanged
  setting = huhi_shields::GetAdControlType(map, GURL());
  EXPECT_EQ(ControlType::BLOCK, setting);

  /* BLOCK */
  // change default to allow
  map->SetContentSettingCustomScope(ContentSettingsPattern::Wildcard(),
                                    ContentSettingsPattern::Wildcard(),
                                    ContentSettingsType::PLUGINS,
                                    huhi_shields::kAds, CONTENT_SETTING_ALLOW);
  setting =
      huhi_shields::GetAdControlType(map, GURL("http://huhisoft.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);
  setting =
      huhi_shields::GetAdControlType(map, GURL("https://huhisoft.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);
  setting = huhi_shields::GetAdControlType(map, GURL());
  EXPECT_EQ(ControlType::ALLOW, setting);

  // set override to block
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("http://huhisoft.com/*"),
      ContentSettingsPattern::Wildcard(), ContentSettingsType::PLUGINS,
      huhi_shields::kAds, CONTENT_SETTING_BLOCK);
  setting =
      huhi_shields::GetAdControlType(map, GURL("http://huhisoft.com/*"));
  EXPECT_EQ(ControlType::BLOCK, setting);
  // https in unchanged
  setting =
      huhi_shields::GetAdControlType(map, GURL("https://huhisoft.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);
  // default is unchanged
  setting = huhi_shields::GetAdControlType(map, GURL());
  EXPECT_EQ(ControlType::ALLOW, setting);
}

/* COOKIE CONTROL */
TEST_F(HuhiShieldsUtilTest, SetCookieControlType_Default) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  // setting should be default to start with
  auto setting = map->GetContentSetting(
      GURL(), GURL(), ContentSettingsType::PLUGINS, huhi_shields::kCookies);
  EXPECT_EQ(CONTENT_SETTING_DEFAULT, setting);
  setting = map->GetContentSetting(GURL(), GURL("https://firstParty"),
                                   ContentSettingsType::PLUGINS,
                                   huhi_shields::kCookies);
  EXPECT_EQ(CONTENT_SETTING_DEFAULT, setting);
  setting = map->GetContentSetting(GURL("http://huhisoft.com"), GURL(),
                                   ContentSettingsType::PLUGINS,
                                   huhi_shields::kCookies);
  setting = map->GetContentSetting(
      GURL("http://huhisoft.com"), GURL("https://firstParty"),
      ContentSettingsType::PLUGINS, huhi_shields::kCookies);
  EXPECT_EQ(CONTENT_SETTING_DEFAULT, setting);

  /* ALLOW */
  huhi_shields::SetCookieControlType(map, ControlType::ALLOW, GURL());
  setting = map->GetContentSetting(
      GURL(), GURL(), ContentSettingsType::PLUGINS, huhi_shields::kCookies);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);
  setting = map->GetContentSetting(GURL(), GURL("https://firstParty"),
                                   ContentSettingsType::PLUGINS,
                                   huhi_shields::kCookies);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);
  // setting should apply to all urls
  setting = map->GetContentSetting(GURL("http://huhisoft.com"), GURL(),
                                   ContentSettingsType::PLUGINS,
                                   huhi_shields::kCookies);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);
  setting = map->GetContentSetting(
      GURL("http://huhisoft.com"), GURL("https://firstParty"),
      ContentSettingsType::PLUGINS, huhi_shields::kCookies);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  /* BLOCK */
  huhi_shields::SetCookieControlType(map, ControlType::BLOCK, GURL());
  setting = map->GetContentSetting(
      GURL(), GURL(), ContentSettingsType::PLUGINS, huhi_shields::kCookies);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);
  setting = map->GetContentSetting(GURL(), GURL("https://firstParty"),
                                   ContentSettingsType::PLUGINS,
                                   huhi_shields::kCookies);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);
  // setting should apply to all urls
  setting = map->GetContentSetting(GURL("http://huhisoft.com"), GURL(),
                                   ContentSettingsType::PLUGINS,
                                   huhi_shields::kCookies);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);
  setting = map->GetContentSetting(
      GURL("http://huhisoft.com"), GURL("https://firstParty"),
      ContentSettingsType::PLUGINS, huhi_shields::kCookies);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);

  /* BLOCK_THIRD_PARTY */
  huhi_shields::SetCookieControlType(map,
                                      ControlType::BLOCK_THIRD_PARTY,
                                      GURL());
  setting = map->GetContentSetting(
      GURL(), GURL(), ContentSettingsType::PLUGINS, huhi_shields::kCookies);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);
  setting = map->GetContentSetting(GURL(), GURL("https://firstParty"),
                                   ContentSettingsType::PLUGINS,
                                   huhi_shields::kCookies);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  // setting should apply to all urls
  setting = map->GetContentSetting(GURL("http://huhisoft.com"), GURL(),
                                   ContentSettingsType::PLUGINS,
                                   huhi_shields::kCookies);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);
  setting = map->GetContentSetting(
      GURL("http://huhisoft.com"), GURL("https://firstParty"),
      ContentSettingsType::PLUGINS, huhi_shields::kCookies);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);
}

TEST_F(HuhiShieldsUtilTest, SetCookieControlType_ForOrigin) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  huhi_shields::SetCookieControlType(map,
                                      ControlType::ALLOW,
                                      GURL("http://huhisoft.com"));
  // override should apply to origin
  auto setting = map->GetContentSetting(GURL("http://huhisoft.com"), GURL(),
                                        ContentSettingsType::PLUGINS,
                                        huhi_shields::kCookies);
  setting = map->GetContentSetting(
      GURL("http://huhisoft.com"), GURL("https://firstParty"),
      ContentSettingsType::PLUGINS, huhi_shields::kCookies);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  // override should also apply to different scheme
  setting = map->GetContentSetting(GURL("https://huhisoft.com"), GURL(),
                                   ContentSettingsType::PLUGINS,
                                   huhi_shields::kCookies);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);
  setting = map->GetContentSetting(
      GURL("https://huhisoft.com"), GURL("https://firstParty"),
      ContentSettingsType::PLUGINS, huhi_shields::kCookies);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  // override should not apply to default
  setting = map->GetContentSetting(
      GURL(), GURL(), ContentSettingsType::PLUGINS, huhi_shields::kCookies);
  EXPECT_EQ(CONTENT_SETTING_DEFAULT, setting);
  // override should not apply to default
  setting = map->GetContentSetting(GURL(), GURL("https://firstParty"),
                                   ContentSettingsType::PLUGINS,
                                   huhi_shields::kCookies);
  EXPECT_EQ(CONTENT_SETTING_DEFAULT, setting);
}

TEST_F(HuhiShieldsUtilTest, GetCookieControlType_Default) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  auto setting = huhi_shields::GetCookieControlType(map, GURL());
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY, setting);
  setting =
      huhi_shields::GetCookieControlType(map, GURL("http://huhisoft.com"));
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY, setting);

  /* ALLOW */
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(), ContentSettingsPattern::Wildcard(),
      ContentSettingsType::PLUGINS, huhi_shields::kCookies,
      CONTENT_SETTING_ALLOW);
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(),
      ContentSettingsPattern::FromString("https://firstParty/*"),
      ContentSettingsType::PLUGINS, huhi_shields::kCookies,
      CONTENT_SETTING_ALLOW);
  setting = huhi_shields::GetCookieControlType(map, GURL());
  EXPECT_EQ(ControlType::ALLOW, setting);
  setting = huhi_shields::GetCookieControlType(map, GURL("http://huhisoft.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);

  /* BLOCK */
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(), ContentSettingsPattern::Wildcard(),
      ContentSettingsType::PLUGINS, huhi_shields::kCookies,
      CONTENT_SETTING_BLOCK);
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(),
      ContentSettingsPattern::FromString("https://firstParty/*"),
      ContentSettingsType::PLUGINS, huhi_shields::kCookies,
      CONTENT_SETTING_BLOCK);
  setting = huhi_shields::GetCookieControlType(map, GURL());
  EXPECT_EQ(ControlType::BLOCK, setting);
  setting = huhi_shields::GetCookieControlType(map, GURL("http://huhisoft.com"));
  EXPECT_EQ(ControlType::BLOCK, setting);

  /* BLOCK_THIRD_PARTY */
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(), ContentSettingsPattern::Wildcard(),
      ContentSettingsType::PLUGINS, huhi_shields::kCookies,
      CONTENT_SETTING_BLOCK);
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(),
      ContentSettingsPattern::FromString("https://firstParty/*"),
      ContentSettingsType::PLUGINS, huhi_shields::kCookies,
      CONTENT_SETTING_ALLOW);
  setting = huhi_shields::GetCookieControlType(map, GURL());
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY, setting);
  setting = huhi_shields::GetCookieControlType(map, GURL("http://huhisoft.com"));
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY, setting);
}

TEST_F(HuhiShieldsUtilTest, GetCookieControlType_ForOrigin) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  auto setting =
      huhi_shields::GetCookieControlType(map, GURL("http://huhisoft.com"));
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY, setting);

  /* ALLOW */
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("http://huhisoft.com/*"),
      ContentSettingsPattern::Wildcard(), ContentSettingsType::PLUGINS,
      huhi_shields::kCookies, CONTENT_SETTING_ALLOW);
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("http://huhisoft.com/*"),
      ContentSettingsPattern::FromString("https://firstParty/*"),
      ContentSettingsType::PLUGINS, huhi_shields::kCookies,
      CONTENT_SETTING_ALLOW);
  setting = huhi_shields::GetCookieControlType(map, GURL("http://huhisoft.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);
  setting = huhi_shields::GetCookieControlType(map, GURL());
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY, setting);

  /* BLOCK */
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("http://huhisoft.com/*"),
      ContentSettingsPattern::Wildcard(), ContentSettingsType::PLUGINS,
      huhi_shields::kCookies, CONTENT_SETTING_BLOCK);
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("http://huhisoft.com/*"),
      ContentSettingsPattern::FromString("https://firstParty/*"),
      ContentSettingsType::PLUGINS, huhi_shields::kCookies,
      CONTENT_SETTING_BLOCK);
  setting = huhi_shields::GetCookieControlType(map, GURL("http://huhisoft.com"));
  EXPECT_EQ(ControlType::BLOCK, setting);
  setting = huhi_shields::GetCookieControlType(map, GURL());
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY, setting);

  /* BLOCK_THIRD_PARTY */
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("http://huhisoft.com/*"),
      ContentSettingsPattern::Wildcard(), ContentSettingsType::PLUGINS,
      huhi_shields::kCookies, CONTENT_SETTING_BLOCK);
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("http://huhisoft.com/*"),
      ContentSettingsPattern::FromString("https://firstParty/*"),
      ContentSettingsType::PLUGINS, huhi_shields::kCookies,
      CONTENT_SETTING_ALLOW);
  setting = huhi_shields::GetCookieControlType(map, GURL("http://huhisoft.com"));
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY, setting);
  setting = huhi_shields::GetCookieControlType(map, GURL());
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY, setting);
}

/* FINGERPRINTING CONTROL */
TEST_F(HuhiShieldsUtilTest, SetFingerprintingControlType_Default) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  // setting should be default to start with
  auto type = huhi_shields::GetFingerprintingControlType(map, GURL());
  EXPECT_EQ(ControlType::DEFAULT, type);
  type = huhi_shields::GetFingerprintingControlType(map,
                                                     GURL("http://huhisoft.com"));
  EXPECT_EQ(ControlType::DEFAULT, type);

  /* ALLOW */
  huhi_shields::SetFingerprintingControlType(map,
                                              ControlType::ALLOW,
                                              GURL());
  type = huhi_shields::GetFingerprintingControlType(map, GURL());
  EXPECT_EQ(ControlType::ALLOW, type);

  // setting should apply to all urls
  type = huhi_shields::GetFingerprintingControlType(map,
                                                     GURL("http://huhisoft.com"));
  EXPECT_EQ(ControlType::ALLOW, type);

  /* BLOCK */
  huhi_shields::SetFingerprintingControlType(map,
                                              ControlType::BLOCK,
                                              GURL());
  type = huhi_shields::GetFingerprintingControlType(map, GURL());
  EXPECT_EQ(ControlType::BLOCK, type);

  // setting should apply to all urls
  type = huhi_shields::GetFingerprintingControlType(map,
                                                     GURL("http://huhisoft.com"));
  EXPECT_EQ(ControlType::BLOCK, type);

  /* DEFAULT */
  huhi_shields::SetFingerprintingControlType(
      map, ControlType::DEFAULT, GURL());
  type = huhi_shields::GetFingerprintingControlType(map, GURL());
  EXPECT_EQ(ControlType::DEFAULT, type);

  // setting should apply to all urls
  type = huhi_shields::GetFingerprintingControlType(map,
                                                     GURL("http://huhisoft.com"));
  EXPECT_EQ(ControlType::DEFAULT, type);

  /* Global ALLOW and Site explicit DEFAULT */
  huhi_shields::SetFingerprintingControlType(map, ControlType::ALLOW, GURL());
  huhi_shields::SetFingerprintingControlType(
      map, ControlType::DEFAULT, GURL("http://huhisoft.com"));
  // Site should have DEFAULT if it's explicitly set.
  type = huhi_shields::GetFingerprintingControlType(map,
                                                     GURL("http://huhisoft.com"));
  EXPECT_EQ(ControlType::DEFAULT, type);

  /* Global BLOCK and Site explicit DEFAULT */
  huhi_shields::SetFingerprintingControlType(map, ControlType::BLOCK, GURL());
  // Site should have DEFAULT if it's explicitly set.
  type = huhi_shields::GetFingerprintingControlType(map,
                                                     GURL("http://huhisoft.com"));
  EXPECT_EQ(ControlType::DEFAULT, type);
}

TEST_F(HuhiShieldsUtilTest, SetFingerprintingControlType_ForOrigin) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  huhi_shields::SetFingerprintingControlType(
      map, ControlType::ALLOW, GURL("http://huhisoft.com"));
  auto type = huhi_shields::GetFingerprintingControlType(
      map, GURL("http://huhisoft.com"));
  EXPECT_EQ(ControlType::ALLOW, type);
  // override should also apply to different scheme
  type = huhi_shields::GetFingerprintingControlType(map,
                                                     GURL("https://huhisoft.com"));
  EXPECT_EQ(ControlType::ALLOW, type);

  huhi_shields::SetFingerprintingControlType(
      map, ControlType::BLOCK, GURL("http://huhisoft.com"));
  type = huhi_shields::GetFingerprintingControlType(map,
                                                     GURL("http://huhisoft.com"));
  EXPECT_EQ(ControlType::BLOCK, type);
  // override should also apply to different scheme
  type = huhi_shields::GetFingerprintingControlType(map,
                                                     GURL("https://huhisoft.com"));
  EXPECT_EQ(ControlType::BLOCK, type);

  // override should not apply to default
  type = huhi_shields::GetFingerprintingControlType(map, GURL());
  EXPECT_EQ(ControlType::DEFAULT, type);
}

/* HTTPSEVERYWHERE CONTROL */
TEST_F(HuhiShieldsUtilTest, SetHTTPSEverywhereEnabled_Default) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  // settings should be default
  auto setting =
      map->GetContentSetting(GURL(), GURL(), ContentSettingsType::PLUGINS,
                             huhi_shields::kHTTPUpgradableResources);
  EXPECT_EQ(CONTENT_SETTING_DEFAULT, setting);
  setting = map->GetContentSetting(GURL("http://huhisoft.com"), GURL(),
                                   ContentSettingsType::PLUGINS,
                                   huhi_shields::kHTTPUpgradableResources);
  EXPECT_EQ(CONTENT_SETTING_DEFAULT, setting);

  /* disabled */
  huhi_shields::SetHTTPSEverywhereEnabled(map, false, GURL());
  setting =
      map->GetContentSetting(GURL(), GURL(), ContentSettingsType::PLUGINS,
                             huhi_shields::kHTTPUpgradableResources);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  // override should apply to all origins
  setting = map->GetContentSetting(GURL("http://huhisoft.com"), GURL(),
                                   ContentSettingsType::PLUGINS,
                                   huhi_shields::kHTTPUpgradableResources);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  /* enabled */
  huhi_shields::SetHTTPSEverywhereEnabled(map, true, GURL());
  setting =
      map->GetContentSetting(GURL(), GURL(), ContentSettingsType::PLUGINS,
                             huhi_shields::kHTTPUpgradableResources);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);

  // override should apply to all origins
  setting = map->GetContentSetting(GURL("http://huhisoft.com"), GURL(),
                                   ContentSettingsType::PLUGINS,
                                   huhi_shields::kHTTPUpgradableResources);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);
}

TEST_F(HuhiShieldsUtilTest, SetHTTPSEverywhereEnabled_ForOrigin) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  huhi_shields::SetHTTPSEverywhereEnabled(
      map, false, GURL("http://huhisoft.com"));
  // setting should apply to origin
  auto setting = map->GetContentSetting(
      GURL("http://huhisoft.com"), GURL(), ContentSettingsType::PLUGINS,
      huhi_shields::kHTTPUpgradableResources);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  // setting should apply to different scheme
  setting = map->GetContentSetting(GURL("https://huhisoft.com"), GURL(),
                                   ContentSettingsType::PLUGINS,
                                   huhi_shields::kHTTPUpgradableResources);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  // setting should not apply to default
  setting =
      map->GetContentSetting(GURL(), GURL(), ContentSettingsType::PLUGINS,
                             huhi_shields::kHTTPUpgradableResources);
  EXPECT_EQ(CONTENT_SETTING_DEFAULT, setting);
}

TEST_F(HuhiShieldsUtilTest, GetHTTPSEverywhereEnabled_Default) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  auto setting = huhi_shields::GetHTTPSEverywhereEnabled(map, GURL());
  EXPECT_EQ(true, setting);

  /* ALLOW */
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(), ContentSettingsPattern::Wildcard(),
      ContentSettingsType::PLUGINS, huhi_shields::kHTTPUpgradableResources,
      CONTENT_SETTING_ALLOW);
  setting = huhi_shields::GetHTTPSEverywhereEnabled(map, GURL());
  EXPECT_EQ(false, setting);

  /* BLOCK */
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(), ContentSettingsPattern::Wildcard(),
      ContentSettingsType::PLUGINS, huhi_shields::kHTTPUpgradableResources,
      CONTENT_SETTING_BLOCK);
  setting = huhi_shields::GetHTTPSEverywhereEnabled(map, GURL());
  EXPECT_EQ(true, setting);
}

TEST_F(HuhiShieldsUtilTest, GetHTTPSEverywhereEnabled_ForOrigin) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  auto setting = huhi_shields::GetHTTPSEverywhereEnabled(map, GURL());
  EXPECT_EQ(true, setting);
  setting = huhi_shields::GetHTTPSEverywhereEnabled(map,
                                                     GURL("http://huhisoft.com"));
  EXPECT_EQ(true, setting);
  setting = huhi_shields::GetHTTPSEverywhereEnabled(map,
                                                     GURL("https://huhisoft.com"));
  EXPECT_EQ(true, setting);

  /* ALLOW */
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("http://huhisoft.com/*"),
      ContentSettingsPattern::Wildcard(), ContentSettingsType::PLUGINS,
      huhi_shields::kHTTPUpgradableResources, CONTENT_SETTING_ALLOW);
  setting = huhi_shields::GetHTTPSEverywhereEnabled(map,
                                                     GURL("http://huhisoft.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);

  // https in unchanged
  setting = huhi_shields::GetHTTPSEverywhereEnabled(map,
                                                     GURL("https://huhisoft.com"));
  EXPECT_EQ(true, setting);
  // default is unchanged
  setting = huhi_shields::GetHTTPSEverywhereEnabled(map, GURL());
  EXPECT_EQ(true, setting);

  /* BLOCK */
  // change default to allow
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(), ContentSettingsPattern::Wildcard(),
      ContentSettingsType::PLUGINS, huhi_shields::kHTTPUpgradableResources,
      CONTENT_SETTING_ALLOW);
  setting = huhi_shields::GetHTTPSEverywhereEnabled(map,
                                                     GURL("http://huhisoft.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);
  setting = huhi_shields::GetHTTPSEverywhereEnabled(map,
                                                     GURL("https://huhisoft.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);
  setting = huhi_shields::GetHTTPSEverywhereEnabled(map, GURL());
  EXPECT_EQ(ControlType::ALLOW, setting);

  // set override to block
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("http://huhisoft.com/*"),
      ContentSettingsPattern::Wildcard(), ContentSettingsType::PLUGINS,
      huhi_shields::kHTTPUpgradableResources, CONTENT_SETTING_BLOCK);
  setting = huhi_shields::GetHTTPSEverywhereEnabled(
      map, GURL("http://huhisoft.com/*"));
  EXPECT_EQ(true, setting);
  // https in unchanged
  setting = huhi_shields::GetHTTPSEverywhereEnabled(map,
                                                     GURL("https://huhisoft.com"));
  EXPECT_EQ(false, setting);
  // default is unchanged
  setting = huhi_shields::GetHTTPSEverywhereEnabled(map, GURL());
  EXPECT_EQ(false, setting);
}

/* NOSCRIPT CONTROL */
TEST_F(HuhiShieldsUtilTest, SetNoScriptControlType_Default) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  // settings should be default
  auto setting = map->GetContentSetting(GURL(), GURL(),
                                        ContentSettingsType::JAVASCRIPT, "");
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);
  setting = map->GetContentSetting(GURL("http://huhisoft.com"), GURL(),
                                   ContentSettingsType::JAVASCRIPT, "");
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  /* BLOCK */
  huhi_shields::SetNoScriptControlType(map,
                                        ControlType::BLOCK,
                                        GURL());
  setting = map->GetContentSetting(GURL(), GURL(),
                                   ContentSettingsType::JAVASCRIPT, "");
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);

  // override should apply to all origins
  setting = map->GetContentSetting(GURL("http://huhisoft.com"), GURL(),
                                   ContentSettingsType::JAVASCRIPT, "");
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);

  /* ALLOW */
  huhi_shields::SetNoScriptControlType(map,
                                        ControlType::ALLOW,
                                        GURL());
  setting = map->GetContentSetting(GURL(), GURL(),
                                   ContentSettingsType::JAVASCRIPT, "");
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  // override should apply to all origins
  setting = map->GetContentSetting(GURL("http://huhisoft.com"), GURL(),
                                   ContentSettingsType::JAVASCRIPT, "");
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);
}

TEST_F(HuhiShieldsUtilTest, SetNoScriptControlType_ForOrigin) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  huhi_shields::SetNoScriptControlType(map,
                                        ControlType::BLOCK,
                                        GURL("http://huhisoft.com"));
  // setting should apply to origin
  auto setting = map->GetContentSetting(GURL("http://huhisoft.com"), GURL(),
                                        ContentSettingsType::JAVASCRIPT, "");
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);

  // setting should also apply to different scheme
  setting = map->GetContentSetting(GURL("https://huhisoft.com"), GURL(),
                                   ContentSettingsType::JAVASCRIPT, "");
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);

  // setting should not apply to default
  setting = map->GetContentSetting(GURL(), GURL(),
                                   ContentSettingsType::JAVASCRIPT, "");
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);
}

TEST_F(HuhiShieldsUtilTest, GetNoScriptControlType_Default) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  auto setting = huhi_shields::GetNoScriptControlType(map, GURL());
  EXPECT_EQ(ControlType::ALLOW, setting);

  /* BLOCK */
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(), ContentSettingsPattern::Wildcard(),
      ContentSettingsType::JAVASCRIPT, "", CONTENT_SETTING_BLOCK);
  setting = huhi_shields::GetNoScriptControlType(map, GURL());
  EXPECT_EQ(ControlType::BLOCK, setting);

  /* ALLOW */
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(), ContentSettingsPattern::Wildcard(),
      ContentSettingsType::JAVASCRIPT, "", CONTENT_SETTING_ALLOW);
  setting = huhi_shields::GetNoScriptControlType(map, GURL());
  EXPECT_EQ(ControlType::ALLOW, setting);
}

TEST_F(HuhiShieldsUtilTest, GetNoScriptControlType_ForOrigin) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  auto setting = huhi_shields::GetNoScriptControlType(map, GURL());
  EXPECT_EQ(ControlType::ALLOW, setting);
  setting = huhi_shields::GetNoScriptControlType(map,
                                                  GURL("http://huhisoft.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);
  setting = huhi_shields::GetNoScriptControlType(map,
                                                  GURL("https://huhisoft.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);

  /* BLOCK */
  // set override to block
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("http://huhisoft.com/*"),
      ContentSettingsPattern::Wildcard(), ContentSettingsType::JAVASCRIPT, "",
      CONTENT_SETTING_BLOCK);
  setting = huhi_shields::GetNoScriptControlType(map,
                                                  GURL("http://huhisoft.com/*"));
  EXPECT_EQ(ControlType::BLOCK, setting);
  // https in unchanged
  setting = huhi_shields::GetNoScriptControlType(map,
                                                  GURL("https://huhisoft.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);
  // default is unchanged
  setting = huhi_shields::GetNoScriptControlType(map, GURL());
  EXPECT_EQ(ControlType::ALLOW, setting);

  /* ALLOW */
  // change default to block
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(), ContentSettingsPattern::Wildcard(),
      ContentSettingsType::JAVASCRIPT, "", CONTENT_SETTING_BLOCK);
  setting = huhi_shields::GetNoScriptControlType(map,
                                                  GURL("http://huhisoft.com"));
  EXPECT_EQ(ControlType::BLOCK, setting);
  setting = huhi_shields::GetNoScriptControlType(map,
                                                  GURL("https://huhisoft.com"));
  EXPECT_EQ(ControlType::BLOCK, setting);
  setting = huhi_shields::GetNoScriptControlType(map, GURL());
  EXPECT_EQ(ControlType::BLOCK, setting);

  map->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("http://huhisoft.com/*"),
      ContentSettingsPattern::Wildcard(), ContentSettingsType::JAVASCRIPT, "",
      CONTENT_SETTING_ALLOW);
  setting = huhi_shields::GetNoScriptControlType(map,
                                                  GURL("http://huhisoft.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);

  // https in unchanged
  setting = huhi_shields::GetNoScriptControlType(map,
                                                  GURL("https://huhisoft.com"));
  EXPECT_EQ(ControlType::BLOCK, setting);
  // default is unchanged
  setting = huhi_shields::GetNoScriptControlType(map, GURL());
  EXPECT_EQ(ControlType::BLOCK, setting);
}
