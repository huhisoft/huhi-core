/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/net/huhi_translate_redirect_network_delegate_helper.h"

#include <memory>
#include <string>
#include <vector>

#include "huhi/browser/net/url_context.h"
#include "huhi/common/translate_network_constants.h"
#include "chrome/test/base/chrome_render_view_host_test_harness.h"
#include "net/traffic_annotation/network_traffic_annotation_test_helper.h"
#include "net/url_request/url_request_test_util.h"
#include "url/gurl.h"
// #include "url/url_constants.h"

namespace {

class HuhiTranslateRedirectNetworkDelegateHelperTest
    : public testing::Test {
 public:
  HuhiTranslateRedirectNetworkDelegateHelperTest()
      : thread_bundle_(content::TestBrowserThreadBundle::IO_MAINLOOP),
        context_(new net::TestURLRequestContext(true)) {}
  ~HuhiTranslateRedirectNetworkDelegateHelperTest() override {}
  void SetUp() override { context_->Init(); }
  net::TestURLRequestContext* context() { return context_.get(); }

 private:
  content::TestBrowserThreadBundle thread_bundle_;
  std::unique_ptr<net::TestURLRequestContext> context_;
};

TEST_F(HuhiTranslateRedirectNetworkDelegateHelperTest,
    RedirectTranslateScriptRequestInitiateByGTranslate) {
  std::string translate_host("https://translate.googleapis.com");
  std::vector<std::string> paths({
      "/element/TE_20181015_01/e/js/element/element_main.js",
      "/translate_static/js/element/main.js"
  });
  std::for_each(paths.begin(), paths.end(),
      [this, &translate_host](std::string path_string) {
    net::TestDelegate test_delegate;
    GURL url(translate_host + path_string);

    std::unique_ptr<net::URLRequest> request = context()->CreateRequest(
        url, net::IDLE, &test_delegate, TRAFFIC_ANNOTATION_FOR_TESTS);
    request->set_initiator(url::Origin::Create(GURL(kTranslateInitiatorURL)));

    std::shared_ptr<huhi::HuhiRequestInfo> before_url_context(
        new huhi::HuhiRequestInfo());
    huhi::HuhiRequestInfo::FillCTXFromRequest(request.get(),
        before_url_context);
    huhi::ResponseCallback callback;

    GURL expected_url(kHuhiTranslateServer + path_string);
    int ret = OnBeforeURLRequest_TranslateRedirectWork(callback,
        before_url_context);
    EXPECT_EQ(before_url_context->new_url_spec, expected_url);
    EXPECT_EQ(ret, net::OK);
  });
}

TEST_F(HuhiTranslateRedirectNetworkDelegateHelperTest,
    NoRedirectTranslateScriptRequestNotInitiateByGTranslate) {
  std::string translate_host("https://translate.googleapis.com");
  std::vector<std::string> paths({
      "/element/TE_20181015_01/e/js/element/element_main.js",
      "/translate_static/js/element/main.js"
  });
  std::for_each(paths.begin(), paths.end(),
      [this, &translate_host](std::string path_string) {
    net::TestDelegate test_delegate;

    GURL url(translate_host + path_string);
    std::unique_ptr<net::URLRequest> request = context()->CreateRequest(
        url, net::IDLE, &test_delegate, TRAFFIC_ANNOTATION_FOR_TESTS);

    std::shared_ptr<huhi::HuhiRequestInfo> before_url_context(
        new huhi::HuhiRequestInfo());
    huhi::HuhiRequestInfo::FillCTXFromRequest(request.get(),
        before_url_context);
    huhi::ResponseCallback callback;

    int ret = OnBeforeURLRequest_TranslateRedirectWork(callback,
        before_url_context);
    EXPECT_EQ(before_url_context->new_url_spec, "");
    EXPECT_EQ(ret, net::OK);
  });
}

TEST_F(HuhiTranslateRedirectNetworkDelegateHelperTest,
    RedirectTranslateResourceRequest) {
  std::string translate_host("https://translate.googleapis.com");
  std::string gstatic_host("https://www.gstatic.com");
  std::vector<GURL> urls({
      GURL(translate_host + "/translate_static/css/translateelement.css"),
      GURL(gstatic_host + "/images/branding/product/1x/translate_24dp.png"),
      GURL(gstatic_host + "/images/branding/product/2x/translate_24dp.png")
  });
  std::for_each(urls.begin(), urls.end(),
      [this](GURL url) {
    net::TestDelegate test_delegate;

    std::unique_ptr<net::URLRequest> request = context()->CreateRequest(
        url, net::IDLE, &test_delegate, TRAFFIC_ANNOTATION_FOR_TESTS);

    std::shared_ptr<huhi::HuhiRequestInfo> before_url_context(
        new huhi::HuhiRequestInfo());
    huhi::HuhiRequestInfo::FillCTXFromRequest(request.get(),
        before_url_context);
    huhi::ResponseCallback callback;

    GURL expected_url(kHuhiTranslateServer + url.path());
    int ret = OnBeforeURLRequest_TranslateRedirectWork(callback,
        before_url_context);
    EXPECT_EQ(before_url_context->new_url_spec, expected_url);
    EXPECT_EQ(ret, net::OK);
  });
}

TEST_F(HuhiTranslateRedirectNetworkDelegateHelperTest,
    RedirectTranslateRequestInitiateByGTranslate) {
  net::TestDelegate test_delegate;
  GURL url(
      "https://translate.googleapis.com/translate_a/t?"
      "anno=3&client=te_lib&format=html&v=1.0&key=DUMMY_KEY&"
      "logld=vTE_20181015_01&sl=auto&tl=en&sp=nmt&tc=1&sr=1&"
      "tk=568026.932804&mode=1");

  std::unique_ptr<net::URLRequest> request = context()->CreateRequest(
      url, net::IDLE, &test_delegate, TRAFFIC_ANNOTATION_FOR_TESTS);
  request->set_initiator(url::Origin::Create(GURL(kTranslateInitiatorURL)));

  std::shared_ptr<huhi::HuhiRequestInfo> before_url_context(
      new huhi::HuhiRequestInfo());
  huhi::HuhiRequestInfo::FillCTXFromRequest(request.get(),
      before_url_context);
  huhi::ResponseCallback callback;

  GURL expected_url(kHuhiTranslateEndpoint + std::string("?") + url.query());
  int ret = OnBeforeURLRequest_TranslateRedirectWork(callback,
      before_url_context);
  EXPECT_EQ(before_url_context->new_url_spec, expected_url);
  EXPECT_EQ(ret, net::OK);
}

TEST_F(HuhiTranslateRedirectNetworkDelegateHelperTest,
    NoRedirectTranslateRequestNotInitiateByGTranslate) {
  net::TestDelegate test_delegate;
  GURL url(
      "https://translate.googleapis.com/translate_a/t?"
      "anno=3&client=te_lib&format=html&v=1.0&key=DUMMY_KEY&"
      "logld=vTE_20181015_01&sl=auto&tl=en&sp=nmt&tc=1&sr=1&"
      "tk=568026.932804&mode=1");

  std::unique_ptr<net::URLRequest> request = context()->CreateRequest(
      url, net::IDLE, &test_delegate, TRAFFIC_ANNOTATION_FOR_TESTS);

  std::shared_ptr<huhi::HuhiRequestInfo> before_url_context(
      new huhi::HuhiRequestInfo());
  huhi::HuhiRequestInfo::FillCTXFromRequest(request.get(),
      before_url_context);
  huhi::ResponseCallback callback;

  GURL expected_url(kHuhiTranslateServer + url.path());
  int ret = OnBeforeURLRequest_TranslateRedirectWork(callback,
      before_url_context);
  EXPECT_EQ(before_url_context->new_url_spec, "");
  EXPECT_EQ(ret, net::OK);
}

TEST_F(HuhiTranslateRedirectNetworkDelegateHelperTest,
    AbortTranslateGen204RequestFromTELib) {
  net::TestDelegate test_delegate;

  GURL url(
      "https://translate.google.com/gen204"
      "?nca=te_li&client=te_lib&logld=vTE_20181015_01");

  std::unique_ptr<net::URLRequest> request = context()->CreateRequest(
      url, net::IDLE, &test_delegate, TRAFFIC_ANNOTATION_FOR_TESTS);

  std::shared_ptr<huhi::HuhiRequestInfo> before_url_context(
      new huhi::HuhiRequestInfo());
  huhi::HuhiRequestInfo::FillCTXFromRequest(request.get(),
                                              before_url_context);
  huhi::ResponseCallback callback;

  int ret = OnBeforeURLRequest_TranslateRedirectWork(callback,
      before_url_context);

  EXPECT_EQ(before_url_context->new_url_spec, "");
  EXPECT_EQ(ret, net::ERR_ABORTED);
}

TEST_F(HuhiTranslateRedirectNetworkDelegateHelperTest,
  NoAbortTranslateGen204RequestNotFromTELib) {
  net::TestDelegate test_delegate;

  GURL url(
      "https://translate.google.com/gen204"
      "?nca=te_li&client=webapp&logld=vTE_20181015_01");

  std::unique_ptr<net::URLRequest> request = context()->CreateRequest(
      url, net::IDLE, &test_delegate, TRAFFIC_ANNOTATION_FOR_TESTS);

  std::shared_ptr<huhi::HuhiRequestInfo> before_url_context(
      new huhi::HuhiRequestInfo());
  huhi::HuhiRequestInfo::FillCTXFromRequest(request.get(),
                                              before_url_context);
  huhi::ResponseCallback callback;

  int ret = OnBeforeURLRequest_TranslateRedirectWork(callback,
      before_url_context);
  EXPECT_EQ(before_url_context->new_url_spec, "");
  EXPECT_EQ(ret, net::OK);
}

}  // namespace
