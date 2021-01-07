/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/browsing_data/huhi_browsing_data_remover_delegate.h"

#include <memory>
#include <string>
#include <utility>

#include "base/bind.h"
#include "huhi/components/huhi_shields/browser/huhi_shields_util.h"
#include "huhi/components/huhi_shields/common/huhi_shield_constants.h"
#include "huhi/components/content_settings/core/browser/huhi_content_settings_utils.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/test/base/testing_profile.h"
#include "components/content_settings/core/browser/host_content_settings_map.h"
#include "content/public/test/browser_task_environment.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"

class HuhiBrowsingDataRemoverDelegateTest : public testing::Test {
 public:
  void SetUp() override {
    profile_ = std::make_unique<TestingProfile>();
    map_ = HostContentSettingsMapFactory::GetForProfile(profile());
  }

  Profile* profile() { return profile_.get(); }

  HostContentSettingsMap* map() { return map_.get(); }

  HuhiBrowsingDataRemoverDelegate* delegate() {
    return static_cast<HuhiBrowsingDataRemoverDelegate*>(
        profile()->GetBrowsingDataRemoverDelegate());
  }

  int GetShieldsSettingsCount() {
    int shields_settings_count = 0;
    for (const auto& resource_id : content_settings::GetShieldsResourceIDs()) {
      ContentSettingsForOneType settings;
      ContentSettingsType content_type = ContentSettingsType::PLUGINS;
      map()->GetSettingsForOneType(content_type, resource_id, &settings);
      shields_settings_count += settings.size();
    }
    return shields_settings_count;
  }

 private:
  content::BrowserTaskEnvironment task_environment_;

  std::unique_ptr<TestingProfile> profile_;
  scoped_refptr<HostContentSettingsMap> map_;
};

TEST_F(HuhiBrowsingDataRemoverDelegateTest, ShieldsSettingsClearTest) {
  const GURL kHuhiURL("https://www.hnq.vn");
  const GURL kBatURL("https://basicattentiontoken.org");
  const GURL kGoogleURL("https://www.google.com");
  const GURL kAbcURL("https://www.abc.com");
  // Four settings are added.
  // First two settings are shields settings in PLUGINS type.
  // Javascript is not counted as shields type because it's stored to
  // JAVASCRIPT type instead of PLUGINS type.
  // Last one is PLUGINS type but it's flash resource not shields resource.
  map()->SetContentSettingDefaultScope(
      kHuhiURL, GURL(), ContentSettingsType::PLUGINS,
      huhi_shields::kHTTPUpgradableResources, CONTENT_SETTING_ALLOW);
  map()->SetContentSettingDefaultScope(
      kBatURL, GURL(), ContentSettingsType::PLUGINS,
      huhi_shields::kFingerprintingV2, CONTENT_SETTING_ALLOW);
  map()->SetContentSettingCustomScope(
      huhi_shields::GetPatternFromURL(kGoogleURL),
      ContentSettingsPattern::Wildcard(),
      ContentSettingsType::JAVASCRIPT, "", CONTENT_SETTING_BLOCK);
  map()->SetContentSettingDefaultScope(
      kAbcURL, GURL(), ContentSettingsType::PLUGINS,
      "", CONTENT_SETTING_ALLOW);

  const base::Time kNow = base::Time::Now();
  const base::Time k1DaysOld = kNow - base::TimeDelta::FromDays(1);

  // Check current shields settings count is 2 and zero after clearing 1 day
  // time range.
  EXPECT_EQ(2, GetShieldsSettingsCount());
  delegate()->ClearShieldsSettings(k1DaysOld, kNow);
  EXPECT_EQ(0, GetShieldsSettingsCount());
}
