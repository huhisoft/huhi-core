/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <memory>

#include "huhi/browser/net/huhi_httpse_network_delegate_helper.h"

#include "huhi/browser/net/url_context.h"
#include "huhi/common/network_constants.h"
#include "chrome/test/base/chrome_render_view_host_test_harness.h"
#include "content/public/test/browser_task_environment.h"
#include "net/cookies/site_for_cookies.h"
#include "net/traffic_annotation/network_traffic_annotation_test_helper.h"
#include "net/url_request/url_request_test_util.h"

namespace {

class HuhiHTTPSENetworkDelegateHelperTest: public testing::Test {
 public:
  HuhiHTTPSENetworkDelegateHelperTest()
      : task_environment_(content::BrowserTaskEnvironment::IO_MAINLOOP),
        context_(new net::TestURLRequestContext(true)) {
  }
  ~HuhiHTTPSENetworkDelegateHelperTest() override {}
  void SetUp() override {
    context_->Init();
  }
  net::TestURLRequestContext* context() { return context_.get(); }

 private:
  content::BrowserTaskEnvironment task_environment_;
  std::unique_ptr<net::TestURLRequestContext> context_;
};


TEST_F(HuhiHTTPSENetworkDelegateHelperTest, AlreadySetNewURLNoOp) {
  net::TestDelegate test_delegate;
  GURL url("http://bradhatesprimes.huhisoft.com/composite_numbers_ftw");
  std::unique_ptr<net::URLRequest> request =
      context()->CreateRequest(url, net::IDLE, &test_delegate,
                               TRAFFIC_ANNOTATION_FOR_TESTS);
  std::shared_ptr<huhi::HuhiRequestInfo>
      huhi_request_info(new huhi::HuhiRequestInfo());
  request->set_site_for_cookies(net::SiteForCookies::FromUrl(
      GURL("http://brad.huhisoft.com/hide_all_primes_in_ui/composites_forever")));
  huhi_request_info->new_url_spec = "data:image/png;base64,iVB";
  huhi::ResponseCallback callback;
  int ret =
    OnBeforeURLRequest_HttpsePreFileWork(callback, huhi_request_info);
  EXPECT_EQ(huhi_request_info->new_url_spec, huhi_request_info->new_url_spec);
  EXPECT_EQ(ret, net::OK);
}

}  // namespace
