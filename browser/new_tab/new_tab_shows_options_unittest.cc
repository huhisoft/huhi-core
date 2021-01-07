/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/new_tab/new_tab_shows_options.h"
#include "huhi/common/pref_names.h"
#include "huhi/common/webui_url_constants.h"
#include "chrome/common/pref_names.h"
#include "chrome/test/base/testing_browser_process.h"
#include "chrome/test/base/testing_profile.h"
#include "chrome/test/base/testing_profile_manager.h"
#include "components/prefs/pref_service.h"
#include "content/public/test/browser_task_environment.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "url/url_constants.h"

class HuhiNewTabTest : public testing::Test {
 public:
  HuhiNewTabTest() : manager_(TestingBrowserProcess::GetGlobal()) {}
  ~HuhiNewTabTest() override {}

 protected:
  void SetUp() override {
    ASSERT_TRUE(manager_.SetUp());
  }

  TestingProfileManager* manager() { return &manager_; }

 private:
  content::BrowserTaskEnvironment task_environment_;
  TestingProfileManager manager_;
};

TEST_F(HuhiNewTabTest, BasicTest) {
  Profile* profile = manager()->CreateTestingProfile("Test 1");
  Profile* otr_profile = profile->GetPrimaryOTRProfile();
  ASSERT_TRUE(profile);
  ASSERT_TRUE(otr_profile);

  auto* prefs = profile->GetPrefs();

  // Check NTP url is empty for DASHBOARD.
  prefs->SetInteger(
      kNewTabPageShowsOptions,
      static_cast<int>(huhi::NewTabPageShowsOptions::kDashboard));
  EXPECT_EQ(GURL(), huhi::GetNewTabPageURL(profile));
  EXPECT_EQ(GURL(), huhi::GetNewTabPageURL(otr_profile));
  EXPECT_TRUE(huhi::ShouldUseNewTabURLForNewTab(profile));
  EXPECT_TRUE(huhi::ShouldNewTabShowDashboard(profile));

  // Check NTP url is empty when option is HOMEPAGE and kHomePageIsNewTabPage
  // is true.
  prefs->SetInteger(
      kNewTabPageShowsOptions,
      static_cast<int>(huhi::NewTabPageShowsOptions::kHomepage));
  prefs->SetString(prefs::kHomePage, "https://www.hnq.vn/");
  prefs->SetBoolean(prefs::kHomePageIsNewTabPage, true);
  EXPECT_EQ(GURL(), huhi::GetNewTabPageURL(profile));
  EXPECT_EQ(GURL(), huhi::GetNewTabPageURL(otr_profile));
  EXPECT_TRUE(huhi::ShouldUseNewTabURLForNewTab(profile));
  EXPECT_TRUE(huhi::ShouldNewTabShowDashboard(profile));

  // Check NTP url is configured url when option is HOMEPAGE and
  // kHomePageIsNewTabPage is false.
  prefs->SetBoolean(prefs::kHomePageIsNewTabPage, false);
  EXPECT_EQ(GURL("https://www.hnq.vn/"), huhi::GetNewTabPageURL(profile));
  EXPECT_EQ(GURL(), huhi::GetNewTabPageURL(otr_profile));
  EXPECT_FALSE(huhi::ShouldUseNewTabURLForNewTab(profile));
  EXPECT_FALSE(huhi::ShouldNewTabShowDashboard(profile));

  // If homepage url is newtab url, dashboard settings should be shown.
  prefs->SetString(prefs::kHomePage, "chrome://newtab/");
  EXPECT_TRUE(huhi::ShouldUseNewTabURLForNewTab(profile));
  EXPECT_TRUE(huhi::ShouldNewTabShowDashboard(profile));

  // Check NTP url is used when option is BLANKPAGE.
  // Blank page will go NTP route and HuhiNewTabUI will handle it.
  prefs->SetInteger(
      kNewTabPageShowsOptions,
      static_cast<int>(huhi::NewTabPageShowsOptions::kBlankpage));
  EXPECT_EQ(GURL(), huhi::GetNewTabPageURL(profile));
  EXPECT_EQ(GURL(), huhi::GetNewTabPageURL(otr_profile));
  EXPECT_TRUE(huhi::ShouldUseNewTabURLForNewTab(profile));
  EXPECT_FALSE(huhi::ShouldNewTabShowDashboard(profile));
  EXPECT_TRUE(huhi::ShouldNewTabShowBlankpage(profile));
  EXPECT_FALSE(huhi::ShouldNewTabShowBlankpage(otr_profile));
}
