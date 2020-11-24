/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <string>

#include "huhi/browser/net/url_context.h"
#include "huhi/browser/net/huhi_stp_util.h"
#include "chrome/test/base/chrome_render_view_host_test_harness.h"
#include "content/public/test/browser_task_environment.h"
#include "net/traffic_annotation/network_traffic_annotation_test_helper.h"
#include "net/url_request/url_request_test_util.h"
#include "url/gurl.h"

using huhi::RemoveTrackableSecurityHeadersForThirdParty;
using huhi::TrackableSecurityHeaders;
using net::HttpResponseHeaders;


namespace {

const char kFirstPartyDomain[] = "http://firstparty.com/";
const char kThirdPartyDomain[] = "http://thirdparty.com/";
const char kAcceptLanguageHeader[] = "Accept-Language";
const char kXSSProtectionHeader[] = "X-XSS-Protection";

const char kRawHeaders[] =
    "HTTP/1.0 200 OK\n"
    "Strict-Transport-Security: max-age=31557600\n"
    "Accept-Language: *\n"
    "Expect-CT: max-age=86400, enforce "
    "report-uri=\"https://foo.example/report\"\n"
    "Public-Key-Pins:"
    "pin-sha256=\"cUPcTAZWKaASuYWhhBAkE3h2+soZS7sWs=\""
    "max-age=5184000; includeSubDomains\n"
    "Public-Key-Pins-Report-Only:"
    "pin-sha256=\"cUPcTAZWKaASuYWhhBAkE3h2+soZS7sWs=\""
    "max-age=5184000; includeSubDomains"
    "report-uri=\"https://www.pkp.org/hpkp-report\"\n"
    "X-XSS-Protection: 0";

class HuhiNetworkDelegateBaseTest : public testing::Test {
 public:
  HuhiNetworkDelegateBaseTest()
      : task_environment_(content::BrowserTaskEnvironment::IO_MAINLOOP),
        context_(new net::TestURLRequestContext(true)) {}
  ~HuhiNetworkDelegateBaseTest() override {}
  void SetUp() override { context_->Init(); }

 private:
  content::BrowserTaskEnvironment task_environment_;
  std::unique_ptr<net::TestURLRequestContext> context_;
};

TEST_F(HuhiNetworkDelegateBaseTest, RemoveTrackableSecurityHeaders) {
  net::TestDelegate test_delegate;
  GURL request_url(kThirdPartyDomain);
  GURL tab_url(kFirstPartyDomain);

  scoped_refptr<HttpResponseHeaders> headers(
      new HttpResponseHeaders(net::HttpUtil::AssembleRawHeaders(kRawHeaders)));

  RemoveTrackableSecurityHeadersForThirdParty(request_url,
                                              url::Origin::Create(tab_url),
                                              nullptr, &headers);
  for (auto header : *TrackableSecurityHeaders()) {
    EXPECT_FALSE(headers->HasHeader(header.as_string()));
  }
  EXPECT_TRUE(headers->HasHeader(kAcceptLanguageHeader));
  EXPECT_TRUE(headers->HasHeader(kXSSProtectionHeader));
}

TEST_F(HuhiNetworkDelegateBaseTest, RemoveTrackableSecurityHeadersMixedCase) {
  net::TestDelegate test_delegate;
  GURL request_url(kThirdPartyDomain);
  GURL tab_url(kFirstPartyDomain);

  scoped_refptr<HttpResponseHeaders> headers(
      new HttpResponseHeaders(net::HttpUtil::AssembleRawHeaders(kRawHeaders)));

  RemoveTrackableSecurityHeadersForThirdParty(request_url,
                                              url::Origin::Create(tab_url),
                                              nullptr, &headers);
  for (auto header : *TrackableSecurityHeaders()) {
    EXPECT_FALSE(headers->HasHeader(header.as_string()));
  }
  EXPECT_TRUE(headers->HasHeader(kAcceptLanguageHeader));
  EXPECT_TRUE(headers->HasHeader(kXSSProtectionHeader));
}

TEST_F(HuhiNetworkDelegateBaseTest, RetainTrackableSecurityHeaders) {
  net::TestDelegate test_delegate;
  GURL request_url(kFirstPartyDomain);
  GURL tab_url(kFirstPartyDomain);

  scoped_refptr<HttpResponseHeaders> headers(
      new HttpResponseHeaders(net::HttpUtil::AssembleRawHeaders(kRawHeaders)));

  RemoveTrackableSecurityHeadersForThirdParty(request_url,
                                              url::Origin::Create(tab_url),
                                              nullptr, &headers);
  for (auto header : *TrackableSecurityHeaders()) {
    EXPECT_TRUE(headers->HasHeader(header.as_string()));
  }
  EXPECT_TRUE(headers->HasHeader(kAcceptLanguageHeader));
  EXPECT_TRUE(headers->HasHeader(kXSSProtectionHeader));
}

}  // namespace
