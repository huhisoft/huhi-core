/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "huhi/browser/net/huhi_block_safebrowsing_urls.h"

#include <memory>
#include <string>
#include <vector>

#include "huhi/browser/net/url_context.h"
#include "net/base/net_errors.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"
#include "url/url_constants.h"

namespace {
const char kInvalidUrl[] = "https://no-thanks.invalid";
}  // namespace

void CheckUrl(const std::string& test_url,
              const char* expected_url,
              int expected_error) {
  GURL new_url;
  int rc = huhi::OnBeforeURLRequest_BlockSafeBrowsingReportingURLs(
      GURL(test_url), &new_url);
  EXPECT_EQ(new_url, GURL(expected_url));
  EXPECT_EQ(rc, expected_error);
}

TEST(HuhiBlockReportingUrlsHelperTest, PreserveNormalUrls) {
  const std::vector<const std::string> normalUrls({
      "https://huhisoft.com/",
      "https://safebrowsing.google.com/safebrowsing",
      "https://safebrowsing.googleapis.com/v4",
  });

  for (const auto& url : normalUrls) {
    CheckUrl(url, "", net::OK);
  }
}

TEST(HuhiBlockReportingUrlsHelperTest, CancelReportingUrl) {
  const std::vector<const std::string> reportingUrls({
      "https://sb-ssl.google.com/safebrowsing/clientreport/download",
      "https://sb-ssl.google.com/safebrowsing/clientreport/chrome-reset",
      "https://sb-ssl.google.com/safebrowsing/clientreport/incident",
      "https://sb-ssl.google.com/safebrowsing/clientreport/login",
      "https://sb-ssl.google.com/safebrowsing/clientreport/phishing",
      "https://sb-ssl.google.com/safebrowsing/clientreport/malware-check",
      "https://safebrowsing.google.com/safebrowsing/uploads/webprotect",
      "https://safebrowsing.google.com/safebrowsing/report",
      "https://safebrowsing.google.com/safebrowsing/clientreport/malware",
      "https://safebrowsing.google.com/safebrowsing/uploads/chrome",
      "https://safebrowsing.google.com/safebrowsing/clientreport/crx-list-info",
  });

  for (const auto& url : reportingUrls) {
    CheckUrl(url, kInvalidUrl, net::ERR_ABORTED);
  }
}
