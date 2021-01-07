/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <memory>
#include <string>

#include "base/test/task_environment.h"
#include "huhi/components/huhi_referrals/browser/huhi_referrals_service.h"
#include "huhi/components/huhi_referrals/buildflags/buildflags.h"
#include "huhi/components/ntp_background_images/browser/ntp_background_images_data.h"
#include "huhi/components/ntp_background_images/browser/ntp_background_images_service.h"
#include "huhi/components/ntp_background_images/browser/ntp_background_images_source.h"
#include "huhi/components/ntp_background_images/common/pref_names.h"
#include "components/prefs/testing_pref_service.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace ntp_background_images {

class NTPBackgroundImagesSourceTest : public testing::Test {
 public:
  NTPBackgroundImagesSourceTest() {}

  void SetUp() override {
    auto* registry = local_pref_.registry();
    NTPBackgroundImagesService::RegisterLocalStatePrefs(registry);
    huhi::RegisterPrefsForHuhiReferralsService(registry);
    service_.reset(new NTPBackgroundImagesService(nullptr, &local_pref_));
    source_.reset(new NTPBackgroundImagesSource(service_.get()));
    local_pref_.Set(prefs::kNewTabPageCachedSuperReferralComponentInfo,
                    base::Value(base::Value::Type::DICTIONARY));
  }

  base::test::SingleThreadTaskEnvironment task_environment;
  TestingPrefServiceSimple local_pref_;
  std::unique_ptr<NTPBackgroundImagesService> service_;
  std::unique_ptr<NTPBackgroundImagesSource> source_;
};

TEST_F(NTPBackgroundImagesSourceTest, BasicTest) {
  const std::string test_json_string_referral = R"(
      {
        "schemaVersion": 1,
        "logo": {
          "imageUrl": "logo.png",
          "alt": "Technikke: For music lovers",
          "companyName": "Technikke",
          "destinationUrl": "https://www.hnq.vn"
        },
        "wallpapers": [
          {
            "imageUrl": "background-1.jpg",
            "focalPoint": { "x": 3988, "y": 2049}
          },
          {
            "imageUrl": "background-2.jpg",
            "focalPoint": { "x": 5233, "y": 3464}
          },
          {
            "imageUrl": "background-3.jpg"
          }
        ]
      })";
  service_->OnGetComponentJsonData(false, test_json_string_referral);
  EXPECT_FALSE(source_->AllowCaching());
  EXPECT_TRUE(source_->IsWallpaperPath("sponsored-images/wallpaper-1.jpg"));
  EXPECT_FALSE(source_->IsValidPath("super-duper/huhi.png"));
  EXPECT_FALSE(source_->IsValidPath("sponsored-images/abcd.png"));
  EXPECT_EQ("image/png", source_->GetMimeType("sponsored-images/logo.png"));
  EXPECT_EQ(
      "image/jpg", source_->GetMimeType("sponsored-images/wallpaper-2.jpg"));
  EXPECT_EQ(
      0,
      source_->GetWallpaperIndexFromPath("sponsored-images/wallpaper-0.jpg"));
  EXPECT_EQ(
      -1,
      source_->GetWallpaperIndexFromPath("sponsored-images/wallpaper-3.jpg"));
}

#if BUILDFLAG(ENABLE_HUHI_REFERRALS)

#if !defined(OS_LINUX)
TEST_F(NTPBackgroundImagesSourceTest, BasicSuperReferralDataTest) {
  // Valid super referral component json data.
  const std::string test_json_string_referral = R"(
      {
        "schemaVersion": 1,
        "themeName": "Technikke",
        "logo": {
          "imageUrl": "logo.png",
          "alt": "Technikke: For music lovers",
          "companyName": "Technikke",
          "destinationUrl": "https://www.hnq.vn"
        },
        "wallpapers": [
          {
            "imageUrl": "background-1.jpg",
            "focalPoint": { "x": 3988, "y": 2049}
          },
          {
            "imageUrl": "background-2.jpg",
            "focalPoint": { "x": 5233, "y": 3464}
          },
          {
            "imageUrl": "background-3.jpg"
          }
        ],
        "topSites": [
          {
            "name": "Huhi",
            "destinationUrl": "https://hnq.vn/",
            "iconUrl": "huhi.png"
          },
          {
            "name": "Wiki",
            "destinationUrl": "https://wikipedia.org/",
            "iconUrl": "wikipedia.png"
          },
          {
            "name": "BAT",
            "destinationUrl": "https://basicattentiontoken.org/",
            "iconUrl": "bat.png"
          }
        ]
      })";
  service_->OnGetComponentJsonData(true, test_json_string_referral);
  EXPECT_FALSE(source_->AllowCaching());
  EXPECT_TRUE(source_->IsTopSiteFaviconPath("super-referral/bat.png"));
  EXPECT_FALSE(source_->IsTopSiteFaviconPath("super-referral/logo.png"));
  EXPECT_TRUE(source_->IsWallpaperPath("super-referral/wallpaper-1.jpg"));
  EXPECT_TRUE(source_->IsValidPath("super-referral/huhi.png"));
  EXPECT_FALSE(source_->IsValidPath("super-duper/huhi.png"));
  EXPECT_FALSE(source_->IsValidPath("super-referral/abcd.png"));
  EXPECT_EQ("image/png", source_->GetMimeType("super-referral/logo.png"));
  EXPECT_EQ(
      "image/jpg", source_->GetMimeType("super-referral/wallpaper-2.jpg"));
  EXPECT_EQ(
      0, source_->GetWallpaperIndexFromPath("super-referral/wallpaper-0.jpg"));
  EXPECT_EQ(
      -1, source_->GetWallpaperIndexFromPath("super-referral/wallpaper-3.jpg"));
}
#endif

#endif  // ENABLE_HUHI_REFERRALS

}  // namespace ntp_background_images
