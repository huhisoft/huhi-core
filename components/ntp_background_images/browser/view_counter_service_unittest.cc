/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <memory>
#include <string>

#include "base/feature_list.h"
#include "base/files/file_path.h"
#include "base/test/task_environment.h"
#include "huhi/common/pref_names.h"
#include "huhi/components/huhi_referrals/browser/huhi_referrals_service.h"
#include "huhi/components/huhi_referrals/common/pref_names.h"
#include "huhi/components/ntp_background_images/browser/features.h"
#include "huhi/components/ntp_background_images/browser/ntp_background_images_data.h"
#include "huhi/components/ntp_background_images/browser/ntp_background_images_service.h"
#include "huhi/components/ntp_background_images/browser/view_counter_model.h"
#include "huhi/components/ntp_background_images/browser/view_counter_service.h"
#include "huhi/components/ntp_background_images/common/pref_names.h"
#include "components/prefs/testing_pref_service.h"
#include "components/pref_registry/pref_registry_syncable.h"
#include "components/sync_preferences/testing_pref_service_syncable.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace ntp_background_images {

std::unique_ptr<NTPBackgroundImagesData> GetDemoWallpaper(bool super_referral) {
  auto demo = std::make_unique<NTPBackgroundImagesData>();
  demo->url_prefix = "chrome://newtab/ntp-dummy-brandedwallpaper/";
  demo->backgrounds = {
      { base::FilePath(FILE_PATH_LITERAL("wallpaper1.jpg")), { 3988, 2049 } },
      { base::FilePath(FILE_PATH_LITERAL("wallpaper2.jpg")), { 5233, 3464 } },
      { base::FilePath(FILE_PATH_LITERAL("wallpaper3.jpg")), {  0, 0 } },
  };
  demo->logo_alt_text = "Huhisoftware: Hú hí software.";
  demo->logo_company_name = "Huhisoftware";
  demo->logo_destination_url = "https://huhisoft.com";

  if (super_referral) {
    demo->theme_name = "Huhisoftware";
    demo->top_sites = {
      { "Huhi", "https://huhisoft.com", "huhi.png",
        base::FilePath(FILE_PATH_LITERAL("huhi.png")) },
     { "BAT", "https://basicattentiontoken.org/", "bat.png",
        base::FilePath(FILE_PATH_LITERAL("bat.png")) },
    };
  }

  return demo;
}

class NTPBackgroundImagesViewCounterTest : public testing::Test {
 public:
  NTPBackgroundImagesViewCounterTest() = default;
  ~NTPBackgroundImagesViewCounterTest() override = default;

  void SetUp() override {
    // Need ntp_sponsored_images prefs
    auto* registry = prefs()->registry();
    ViewCounterService::RegisterProfilePrefs(registry);
    auto* local_registry = local_pref_.registry();
    huhi::RegisterPrefsForHuhiReferralsService(local_registry);
    NTPBackgroundImagesService::RegisterLocalStatePrefs(local_registry);

    service_ = std::make_unique<NTPBackgroundImagesService>(
        nullptr,
        &local_pref_,
        base::FilePath());
    view_counter_ = std::make_unique<ViewCounterService>(
        service_.get(), prefs(), true);

    // Set referral service is properly initialized sr component is set.
    local_pref_.SetBoolean(kReferralCheckedForPromoCodeFile, true);
    local_pref_.Set(prefs::kNewTabPageCachedSuperReferralComponentInfo,
                    base::Value(base::Value::Type::DICTIONARY));
  }

  void EnableSIPref(bool enable) {
    prefs()->SetBoolean(
        prefs::kNewTabPageShowSponsoredImagesBackgroundImage, enable);
  }

  void EnableSRPref(bool enable) {
    prefs()->SetInteger(
        prefs::kNewTabPageSuperReferralThemesOption,
        enable ? ViewCounterService::SUPER_REFERRAL
               : ViewCounterService::DEFAULT);
  }

  void EnableNTPBGImagesPref(bool enable) {
    prefs()->SetBoolean(prefs::kNewTabPageShowBackgroundImage, enable);
  }

  sync_preferences::TestingPrefServiceSyncable* prefs() { return &prefs_; }

 protected:
  base::test::SingleThreadTaskEnvironment task_environment;
  TestingPrefServiceSimple local_pref_;
  sync_preferences::TestingPrefServiceSyncable prefs_;
  std::unique_ptr<ViewCounterService> view_counter_;
  std::unique_ptr<NTPBackgroundImagesService> service_;
};

TEST_F(NTPBackgroundImagesViewCounterTest, NotActiveInitially) {
  // By default, data is bad and wallpaper is not active.
  EXPECT_FALSE(view_counter_->IsBrandedWallpaperActive());
}

TEST_F(NTPBackgroundImagesViewCounterTest, NotActiveWithBadData) {
  // Set some bad data explicitly.
  service_->si_images_data_.reset(new NTPBackgroundImagesData);
  service_->sr_images_data_.reset(new NTPBackgroundImagesData);
  EXPECT_FALSE(view_counter_->IsBrandedWallpaperActive());
}

TEST_F(NTPBackgroundImagesViewCounterTest, NotActiveOptedOut) {
  // Even with good data, wallpaper should not be active if user pref is off.
  service_->si_images_data_ = GetDemoWallpaper(false);
  EnableSIPref(false);
  EXPECT_FALSE(view_counter_->IsBrandedWallpaperActive());

  service_->sr_images_data_ = GetDemoWallpaper(true);
  EnableSRPref(false);
  EXPECT_FALSE(view_counter_->IsBrandedWallpaperActive());
}

TEST_F(NTPBackgroundImagesViewCounterTest,
       ActiveOptedInWithNTPBackgoundOption) {
  EnableNTPBGImagesPref(false);
  service_->sr_images_data_ = GetDemoWallpaper(true);

  // Even with bg images turned off, SR wallpaper should be active.
  EnableSRPref(true);
#if defined(OS_LINUX)
  EXPECT_FALSE(view_counter_->IsBrandedWallpaperActive());
#else
  EXPECT_TRUE(view_counter_->IsBrandedWallpaperActive());
#endif

  EnableSRPref(false);
  EXPECT_FALSE(view_counter_->IsBrandedWallpaperActive());
}

// Branded wallpaper is active if one of them is available.
TEST_F(NTPBackgroundImagesViewCounterTest, IsActiveOptedIn) {
  service_->si_images_data_ = GetDemoWallpaper(false);
  EnableSIPref(true);
  EXPECT_TRUE(view_counter_->IsBrandedWallpaperActive());

  service_->sr_images_data_ = GetDemoWallpaper(true);
  EnableSRPref(true);
  EXPECT_TRUE(view_counter_->IsBrandedWallpaperActive());

  // Active if SI is possible.
  EnableSRPref(false);
  EXPECT_TRUE(view_counter_->IsBrandedWallpaperActive());

  // Active if SR is only opted in.
  EnableSIPref(false);
  EnableSRPref(true);
#if defined(OS_LINUX)
  EXPECT_FALSE(view_counter_->IsBrandedWallpaperActive());
#else
  EXPECT_TRUE(view_counter_->IsBrandedWallpaperActive());
#endif
}

TEST_F(NTPBackgroundImagesViewCounterTest, ActiveInitiallyOptedIn) {
  // Sanity check that the default is still to be opted-in.
  // If this gets manually changed, then this test should be manually changed
  // too.
  service_->si_images_data_ = GetDemoWallpaper(false);
  EXPECT_TRUE(view_counter_->IsBrandedWallpaperActive());

  service_->sr_images_data_ = GetDemoWallpaper(true);
  EXPECT_TRUE(view_counter_->IsBrandedWallpaperActive());
}

#if !defined(OS_LINUX)
// Super referral feature is disabled on linux.
TEST_F(NTPBackgroundImagesViewCounterTest, ModelTest) {
  service_->sr_images_data_ = GetDemoWallpaper(true);
  service_->si_images_data_ = GetDemoWallpaper(false);
  view_counter_->OnUpdated(service_->sr_images_data_.get());
  EXPECT_TRUE(view_counter_->model_.ignore_count_to_branded_wallpaper_);

  service_->sr_images_data_.reset(new NTPBackgroundImagesData);
  view_counter_->OnSuperReferralEnded();
  EXPECT_FALSE(view_counter_->model_.ignore_count_to_branded_wallpaper_);
  const int expected_count = ViewCounterModel::kRegularCountToBrandedWallpaper;
  EXPECT_EQ(expected_count, view_counter_->model_.count_to_branded_wallpaper_);
}
#endif

}  // namespace ntp_background_images
