/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/components/huhi_shields/common/huhi_shield_constants.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "components/content_settings/core/browser/host_content_settings_map.h"
#include "components/content_settings/core/common/content_settings_pattern.h"
#include "content/public/test/browser_test.h"

const GURL& GetHuhiURL() {
  static const GURL kHuhiURL("https://www.hnq.vn");
  return kHuhiURL;
}

class HuhiContentSettingsRegistryBrowserTest : public InProcessBrowserTest {
 public:
  using InProcessBrowserTest::InProcessBrowserTest;

  HostContentSettingsMap* content_settings() {
    return HostContentSettingsMapFactory::GetForProfile(browser()->profile());
  }

  HostContentSettingsMap* private_content_settings() {
    return HostContentSettingsMapFactory::GetForProfile(
        browser()->profile()->GetPrimaryOTRProfile());
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(HuhiContentSettingsRegistryBrowserTest);
};

IN_PROC_BROWSER_TEST_F(HuhiContentSettingsRegistryBrowserTest,
                       WithoutWildcardContentSetting) {
  ContentSetting huhi_url_shields_setting =
      content_settings()->GetContentSetting(
          GetHuhiURL(), GetHuhiURL(), ContentSettingsType::PLUGINS,
          huhi_shields::kHuhiShields);
  EXPECT_EQ(CONTENT_SETTING_DEFAULT, huhi_url_shields_setting);

  ContentSetting huhi_url_shields_setting_private =
      private_content_settings()->GetContentSetting(
          GetHuhiURL(), GetHuhiURL(), ContentSettingsType::PLUGINS,
          huhi_shields::kHuhiShields);
  EXPECT_EQ(CONTENT_SETTING_DEFAULT, huhi_url_shields_setting_private);
}

IN_PROC_BROWSER_TEST_F(HuhiContentSettingsRegistryBrowserTest,
                       WithHuhiShieldsContentSetting) {
  ContentSettingsPattern huhi_url_pattern =
      ContentSettingsPattern::FromURL(GetHuhiURL());

  content_settings()->SetContentSettingCustomScope(
      huhi_url_pattern,
      huhi_url_pattern,
      ContentSettingsType::PLUGINS,
      huhi_shields::kHuhiShields,
      CONTENT_SETTING_ALLOW);

  ContentSetting huhi_url_shields_setting =
      content_settings()->GetContentSetting(
          GetHuhiURL(), GetHuhiURL(), ContentSettingsType::PLUGINS,
          huhi_shields::kHuhiShields);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, huhi_url_shields_setting);

  ContentSetting huhi_url_shields_setting_private =
      private_content_settings()->GetContentSetting(
          GetHuhiURL(), GetHuhiURL(), ContentSettingsType::PLUGINS,
          huhi_shields::kHuhiShields);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, huhi_url_shields_setting_private);
}
