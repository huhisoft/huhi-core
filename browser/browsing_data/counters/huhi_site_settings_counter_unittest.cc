/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/browsing_data/counters/huhi_site_settings_counter.h"

#include <memory>
#include <string>
#include <utility>

#include "base/bind.h"
#include "base/test/simple_test_clock.h"
#include "huhi/components/huhi_shields/browser/huhi_shields_util.h"
#include "huhi/components/huhi_shields/common/huhi_shield_constants.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/custom_handlers/protocol_handler_registry.h"
#include "chrome/browser/custom_handlers/protocol_handler_registry_factory.h"
#include "chrome/browser/custom_handlers/test_protocol_handler_registry_delegate.h"
#include "chrome/test/base/testing_profile.h"
#include "components/browsing_data/core/browsing_data_utils.h"
#include "components/browsing_data/core/pref_names.h"
#include "components/content_settings/core/browser/host_content_settings_map.h"
#include "components/prefs/pref_service.h"
#include "content/public/test/browser_task_environment.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"

#if !defined(OS_ANDROID)
#include "content/public/browser/host_zoom_map.h"
#endif

class HuhiSiteSettingsCounterTest : public testing::Test {
 public:
  void SetUp() override {
    profile_ = std::make_unique<TestingProfile>();
    map_ = HostContentSettingsMapFactory::GetForProfile(profile());
#if !defined(OS_ANDROID)
    auto* zoom_map =
        content::HostZoomMap::GetDefaultForBrowserContext(profile());
#else
    content::HostZoomMap* zoom_map = nullptr;
#endif
    handler_registry_ = std::make_unique<ProtocolHandlerRegistry>(
        profile(), std::make_unique<TestProtocolHandlerRegistryDelegate>());
    counter_ = std::make_unique<HuhiSiteSettingsCounter>(
        map(), zoom_map, handler_registry_.get(), profile_->GetPrefs());
    counter_->Init(profile()->GetPrefs(),
                   browsing_data::ClearBrowsingDataTab::ADVANCED,
                   base::BindRepeating(&HuhiSiteSettingsCounterTest::Callback,
                                       base::Unretained(this)));
  }

  Profile* profile() { return profile_.get(); }

  HostContentSettingsMap* map() { return map_.get(); }

  HuhiSiteSettingsCounter* counter() { return counter_.get(); }

  browsing_data::BrowsingDataCounter::ResultInt GetResult() {
    DCHECK(finished_);
    return result_;
  }

  void Callback(
      std::unique_ptr<browsing_data::BrowsingDataCounter::Result> result) {
    DCHECK(result->Finished());
    finished_ = result->Finished();

    result_ = static_cast<browsing_data::BrowsingDataCounter::FinishedResult*>(
                  result.get())
                  ->Value();
  }

 private:
  content::BrowserTaskEnvironment task_environment_;
  std::unique_ptr<TestingProfile> profile_;

  scoped_refptr<HostContentSettingsMap> map_;
  std::unique_ptr<ProtocolHandlerRegistry> handler_registry_;
  std::unique_ptr<HuhiSiteSettingsCounter> counter_;
  bool finished_;
  browsing_data::BrowsingDataCounter::ResultInt result_;
};

// Tests that the counter correctly counts each setting.
TEST_F(HuhiSiteSettingsCounterTest, Count) {
  const GURL kHuhiURL("https://www.huhisoft.com");
  const GURL kBatURL("https://basicattentiontoken.org");
  const GURL kGoogleURL("https://www.google.com");
  const GURL kAbcURL("https://www.abc.com");
  // Check below four settings for different host are counted properly.
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

  counter()->Restart();
  EXPECT_EQ(4, GetResult());
}
