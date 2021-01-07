/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <memory>

#include "testing/gtest/include/gtest/gtest.h"

#include "huhi/components/l10n/browser/locale.h"

// npm run test -- huhi_unit_tests --filter=HuhiAds*


namespace ads {

class HuhiAdsLocaleTest : public ::testing::Test {
 protected:
  HuhiAdsLocaleTest() {
    // You can do set-up work for each test here
  }

  ~HuhiAdsLocaleTest() override {
    // You can do clean-up work that doesn't throw exceptions here
  }

  // If the constructor and destructor are not enough for setting up and
  // cleaning up each test, you can use the following methods

  void SetUp() override {
    // Code here will be called immediately after the constructor (right before
    // each test)
  }

  void TearDown() override {
    // Code here will be called immediately after each test (right before the
    // destructor)
  }
};

TEST_F(HuhiAdsLocaleTest,
    LanguageCodeForEnglish) {
  // Arrange
  const std::string locale = "en";

  // Act
  const std::string language_code =
      huhi_l10n::Locale::GetLanguageCode(locale);

  // Assert
  const std::string expected_language_code = "en";
  EXPECT_EQ(expected_language_code, language_code);
}

TEST_F(HuhiAdsLocaleTest,
    CountryCodeForEnglish) {
  // Arrange
  const std::string locale = "en";

  // Act
  const std::string country_code =
      huhi_l10n::Locale::GetCountryCode(locale);

  // Assert
  const std::string expected_country_code = "US";
  EXPECT_EQ(expected_country_code, country_code);
}

TEST_F(HuhiAdsLocaleTest,
    LanguageCodeForLanguageCodeDashCountryCode) {
  // Arrange
  const std::string locale = "en-US";

  // Act
  const std::string language_code =
      huhi_l10n::Locale::GetCountryCode(locale);

  // Assert
  const std::string expected_language_code = "en";
  EXPECT_EQ(expected_language_code, language_code);
}

TEST_F(HuhiAdsLocaleTest,
    CountryCodeForLanguageCodeDashCountryCode) {
  // Arrange
  const std::string locale = "en-US";

  // Act
  const std::string country_code =
      huhi_l10n::Locale::GetCountryCode(locale);

  // Assert
  const std::string expected_country_code = "US";
  EXPECT_EQ(expected_country_code, country_code);
}

TEST_F(HuhiAdsLocaleTest,
    LanguageCodeForLanguageCodeDashWorld) {
  // Arrange
  const std::string locale = "en-101";

  // Act
  const std::string language_code =
      huhi_l10n::Locale::GetLanguageCode(locale);

  // Assert
  const std::string expected_language_code = "en";
  EXPECT_EQ(expected_language_code, language_code);
}

TEST_F(HuhiAdsLocaleTest,
    CountryCodeForLanguageCodeDashWorld) {
  // Arrange
  const std::string locale = "en-101";

  // Act
  const std::string country_code =
      huhi_l10n::Locale::GetCountryCode(locale);

  // Assert
  const std::string expected_country_code = "101";
  EXPECT_EQ(expected_country_code, country_code);
}

TEST_F(HuhiAdsLocaleTest,
    LanguageCodeForLanguageCodeDashCountryCodeDotEncoding) {
  // Arrange
  const std::string locale = "en-US.UTF-8";

  // Act
  const std::string language_code =
      huhi_l10n::Locale::GetLanguageCode(locale);

  // Assert
  const std::string expected_language_code = "en";
  EXPECT_EQ(expected_language_code, language_code);
}

TEST_F(HuhiAdsLocaleTest,
    CountryCodeForLanguageCodeDashCountryCodeDotEncoding) {
  // Arrange
  const std::string locale = "en-US.UTF-8";

  // Act
  const std::string country_code =
      huhi_l10n::Locale::GetCountryCode(locale);

  // Assert
  const std::string expected_country_code = "US";
  EXPECT_EQ(expected_country_code, country_code);
}

TEST_F(HuhiAdsLocaleTest,
    LanguageCodeForLanguageCodeDashScriptDashCountryCode) {
  // Arrange
  const std::string locale = "az-Latn-AZ";

  // Act
  const std::string language_code =
      huhi_l10n::Locale::GetLanguageCode(locale);

  // Assert
  const std::string expected_language_code = "az";
  EXPECT_EQ(expected_language_code, language_code);
}

TEST_F(HuhiAdsLocaleTest,
    CountryCodeForLanguageCodeDashScriptDashCountryCode) {
  // Arrange
  const std::string locale = "az-Latn-AZ";

  // Act
  const std::string country_code =
      huhi_l10n::Locale::GetCountryCode(locale);

  // Assert
  const std::string expected_country_code = "AZ";
  EXPECT_EQ(expected_country_code, country_code);
}

TEST_F(HuhiAdsLocaleTest,
    LanguageCodeForLanguageCodeUnderscoreCountryCode) {
  // Arrange
  const std::string locale = "en_US";

  // Act
  const std::string language_code =
      huhi_l10n::Locale::GetLanguageCode(locale);

  // Assert
  const std::string expected_language_code = "en";
  EXPECT_EQ(expected_language_code, language_code);
}

TEST_F(HuhiAdsLocaleTest,
    CountryCodeForLanguageCodeUnderscoreCountryCode) {
  // Arrange
  const std::string locale = "en_US";

  // Act
  const std::string country_code =
      huhi_l10n::Locale::GetCountryCode(locale);

  // Assert
  const std::string expected_country_code = "US";
  EXPECT_EQ(expected_country_code, country_code);
}

TEST_F(HuhiAdsLocaleTest,
    LanguageCodeForLanguageCodeUnderscoreCountryCodeDotEncoding) {
  // Arrange
  const std::string locale = "en_US.UTF-8";

  // Act
  const std::string language_code =
      huhi_l10n::Locale::GetLanguageCode(locale);

  // Assert
  const std::string expected_language_code = "en";
  EXPECT_EQ(expected_language_code, language_code);
}

TEST_F(HuhiAdsLocaleTest,
    CountryCodeForLanguageCodeUnderscoreCountryCodeDotEncoding) {
  // Arrange
  const std::string locale = "en_US.UTF-8";

  // Act
  const std::string country_code =
      huhi_l10n::Locale::GetCountryCode(locale);

  // Assert
  const std::string expected_country_code = "US";
  EXPECT_EQ(expected_country_code, country_code);
}

TEST_F(HuhiAdsLocaleTest,
    LanguageCodeForLanguageCodeUnderscoreScriptUnderscoreCountryCode) {
  // Arrange
  const std::string locale = "az_Latn_AZ";

  // Act
  const std::string language_code =
      huhi_l10n::Locale::GetLanguageCode(locale);

  // Assert
  const std::string expected_language_code = "az";
  EXPECT_EQ(expected_language_code, language_code);
}

TEST_F(HuhiAdsLocaleTest,
    CountryCodeForLanguageCodeUnderscoreScriptUnderscoreCountryCode) {
  // Arrange
  const std::string locale = "az_Latn_AZ";

  // Act
  const std::string country_code =
      huhi_l10n::Locale::GetCountryCode(locale);

  // Assert
  const std::string expected_country_code = "AZ";
  EXPECT_EQ(expected_country_code, country_code);
}

}  // namespace ads
