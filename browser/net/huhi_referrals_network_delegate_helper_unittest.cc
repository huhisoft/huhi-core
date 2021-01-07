/* Copyright 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/net/huhi_referrals_network_delegate_helper.h"

#include <memory>
#include <string>

#include "base/json/json_reader.h"
#include "huhi/browser/net/url_context.h"
#include "huhi/common/network_constants.h"
#include "net/base/net_errors.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"
#include "url/url_constants.h"

using huhi::ResponseCallback;

namespace {
const char kTestReferralHeaders[] = R"(
  [
    {
      "domains": [
         "marketwatch.com",
         "barrons.com"
      ],
      "headers": {
         "X-Huhi-Partner":"dowjones",
         "X-Invalid": "test"
      },
      "cookieNames": [
      ],
      "expiration":31536000000
    },
    {
      "domains": [
         "townsquareblogs.com",
         "tasteofcountry.com",
         "ultimateclassicrock.com",
         "xxlmag.com",
         "popcrush.com"
      ],
      "headers": {
         "X-Huhi-Partner":"townsquare"
      },
      "cookieNames":[
      ],
      "expiration":31536000000
    }
  ])";
}  // namespace

TEST(HuhiReferralsNetworkDelegateHelperTest, ReplaceHeadersForMatchingDomain) {
  const GURL url("https://www.marketwatch.com");
  base::JSONReader::ValueWithError referral_headers =
      base::JSONReader::ReadAndReturnValueWithError(kTestReferralHeaders);
  ASSERT_TRUE(referral_headers.value);
  ASSERT_TRUE(referral_headers.value->is_list());

  const base::ListValue* referral_headers_list = nullptr;
  referral_headers.value->GetAsList(&referral_headers_list);

  net::HttpRequestHeaders headers;
  auto request_info = std::make_shared<huhi::HuhiRequestInfo>(url);
  request_info->referral_headers_list = referral_headers_list;

  int rc = huhi::OnBeforeStartTransaction_ReferralsWork(
      &headers, huhi::ResponseCallback(), request_info);

  std::string partner_header;
  headers.GetHeader("X-Huhi-Partner", &partner_header);
  EXPECT_EQ(partner_header, "dowjones");

  std::string invalid_partner_header;
  EXPECT_EQ(headers.GetHeader("X-Invalid", &invalid_partner_header), false);
  EXPECT_EQ(invalid_partner_header, "");

  EXPECT_EQ(rc, net::OK);
}

TEST(HuhiReferralsNetworkDelegateHelperTest,
     NoReplaceHeadersForNonMatchingDomain) {
  const GURL url("https://www.google.com");
  base::JSONReader::ValueWithError referral_headers =
      base::JSONReader::ReadAndReturnValueWithError(kTestReferralHeaders);
  ASSERT_TRUE(referral_headers.value);
  ASSERT_TRUE(referral_headers.value->is_list());

  const base::ListValue* referral_headers_list = nullptr;
  referral_headers.value->GetAsList(&referral_headers_list);

  net::HttpRequestHeaders headers;
  auto request_info = std::make_shared<huhi::HuhiRequestInfo>(GURL());
  request_info->referral_headers_list = referral_headers_list;
  int rc = huhi::OnBeforeStartTransaction_ReferralsWork(
      &headers, huhi::ResponseCallback(), request_info);

  EXPECT_FALSE(headers.HasHeader("X-Huhi-Partner"));
  EXPECT_EQ(rc, net::OK);
}
