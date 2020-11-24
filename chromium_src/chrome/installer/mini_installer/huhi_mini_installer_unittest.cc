// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/installer/mini_installer/mini_installer.h"

#include "testing/gtest/include/gtest/gtest.h"

namespace mini_installer {

class HuhiMiniInstallerTest: public testing::Test {
 public:
  HuhiMiniInstallerTest() {
  }
  ~HuhiMiniInstallerTest() override {}
};


TEST_F(HuhiMiniInstallerTest, HasNoReferralCode) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"HuhiBrowserSetup.exe", &referral_code));
}

TEST_F(HuhiMiniInstallerTest, HasStandardReferralCode) {
  ReferralCodeString referral_code;
  EXPECT_TRUE(ParseReferralCode(L"HuhiBrowserSetup-FOO123.exe",
                          &referral_code));
  EXPECT_STREQ(referral_code.get(), L"FOO123");
}

TEST_F(HuhiMiniInstallerTest, HasStandardReferralCodeWithLowercase) {
  ReferralCodeString referral_code;
  EXPECT_TRUE(ParseReferralCode(L"HuhiBrowserSetup-foo123.exe",
                          &referral_code));
  EXPECT_STREQ(referral_code.get(), L"FOO123");
}

TEST_F(HuhiMiniInstallerTest, HasStandardReferralCodeWithPath) {
  ReferralCodeString referral_code;
  EXPECT_TRUE(ParseReferralCode(L"c:/foo/bar/HuhiBrowserSetup-FOO123.exe",
                          &referral_code));
  EXPECT_STREQ(referral_code.get(), L"FOO123");
}

TEST_F(HuhiMiniInstallerTest,
                HasStandardReferralCodeWithDeduplicatingSuffix) {
  ReferralCodeString referral_code;
  EXPECT_TRUE(ParseReferralCode(L"c:/foo/bar/HuhiBrowserSetup-FOO123 (1).exe",
                          &referral_code));
  EXPECT_STREQ(referral_code.get(), L"FOO123");
}

TEST_F(HuhiMiniInstallerTest,
                HasStandardReferralCodeWithDeduplicatingSuffixNoSpaces) {
  ReferralCodeString referral_code;
  EXPECT_TRUE(ParseReferralCode(L"c:/foo/bar/HuhiBrowserSetup-FOO123(1).exe",
                          &referral_code));
  EXPECT_STREQ(referral_code.get(), L"FOO123");
}

TEST_F(HuhiMiniInstallerTest,
                HasStandardReferralCodeWithDeduplicatingSuffixExtraSpaces) {
  ReferralCodeString referral_code;
  EXPECT_TRUE(ParseReferralCode(
                          L"c:/foo/bar/HuhiBrowserSetup-FOO123   (1).exe",
                          &referral_code));
  EXPECT_STREQ(referral_code.get(), L"FOO123");
}

TEST_F(HuhiMiniInstallerTest, HasInvalidStandardReferralCodeReversed) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"HuhiBrowserSetup-123FOO.exe",
                          &referral_code));
}

TEST_F(HuhiMiniInstallerTest, HasInvalidStandardReferralCodeNoDigits) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"HuhiBrowserSetup-FOO.exe", &referral_code));
}

TEST_F(HuhiMiniInstallerTest, HasInvalidStandardReferralCodeNoLetters) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"HuhiBrowserSetup-123.exe", &referral_code));
}

TEST_F(HuhiMiniInstallerTest, HasInvalidStandardReferralCodeTooManyDigits) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"HuhiBrowserSetup-FOO1234.exe",
                          &referral_code));
}

TEST_F(HuhiMiniInstallerTest, HasInvalidStandardReferralCodeTooFewDigits) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"HuhiBrowserSetup-FOO12.exe",
                          &referral_code));
}

TEST_F(HuhiMiniInstallerTest, HasInvalidStandardReferralCodeTooManyLetters) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"HuhiBrowserSetup-FOOO123.exe",
                          &referral_code));
}

TEST_F(HuhiMiniInstallerTest, HasInvalidStandardReferralCodeTooFewLetters) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"HuhiBrowserSetup-FO123.exe",
                          &referral_code));
}

TEST_F(HuhiMiniInstallerTest, HasExtendedReferralCode) {
  ReferralCodeString referral_code;
  EXPECT_TRUE(ParseReferralCode(L"HuhiBrowserSetup-extended-code.exe",
                          &referral_code));
  EXPECT_STREQ(referral_code.get(), L"extended-code");
}

TEST_F(HuhiMiniInstallerTest,
                HasInvalidExtendedReferralCodeNonAlphabeticCharacters) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(
                          L"HuhiBrowserSetup-invalid-extended-c0de.exe",
                          &referral_code));
}

TEST_F(HuhiMiniInstallerTest, HasInvalidExtendedReferralCodeTooFewWords) {
  ReferralCodeString referral_code;
  EXPECT_FALSE(ParseReferralCode(L"HuhiBrowserSetup-invalidextendedcode.exe",
                          &referral_code));
}

}  // namespace mini_installer
