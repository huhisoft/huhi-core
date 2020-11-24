/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/ipfs/content_browser_client_helper.h"

#include <memory>
#include <vector>

#include "base/test/bind_test_util.h"
#include "huhi/browser/ipfs/ipfs_service.h"
#include "huhi/browser/ipfs/ipfs_service_factory.h"
#include "huhi/common/pref_names.h"
#include "huhi/components/ipfs/common/ipfs_constants.h"
#include "chrome/test/base/chrome_render_view_host_test_harness.h"
#include "chrome/test/base/scoped_testing_local_state.h"
#include "chrome/test/base/testing_browser_process.h"
#include "content/public/browser/content_browser_client.h"
#include "content/public/browser/navigation_handle.h"
#include "content/public/common/content_client.h"
#include "content/public/test/mock_navigation_handle.h"
#include "content/public/test/web_contents_tester.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"

using IPFSHuhiContentBrowserClientTest = testing::Test;

namespace ipfs {

TEST_F(IPFSHuhiContentBrowserClientTest, TranslateIPFSURLNotIPFSScheme) {
  GURL url("http://a.com/ipfs/QmfM2r8seH2GiRaC4esTjeraXEachRt8ZsSeGaWTPLyMoG");
  GURL new_url;
  ASSERT_FALSE(
      ContentBrowserClientHelper::TranslateIPFSURL(url, &new_url, false));
}

TEST_F(IPFSHuhiContentBrowserClientTest, TranslateIPFSURLIPFSScheme) {
  GURL url("ipfs://QmfM2r8seH2GiRaC4esTjeraXEachRt8ZsSeGaWTPLyMoG");
  GURL new_url;
  ASSERT_TRUE(
      ContentBrowserClientHelper::TranslateIPFSURL(url, &new_url, false));
  EXPECT_EQ(new_url, GURL(
      "https://dweb.link/ipfs/QmfM2r8seH2GiRaC4esTjeraXEachRt8ZsSeGaWTPLyMoG"));
}

TEST_F(IPFSHuhiContentBrowserClientTest, TranslateIPFSURLIPNSScheme) {
  GURL url("ipns://QmSrPmbaUKA3ZodhzPWZnpFgcPMFWF4QsxXbkWfEptTBJd");
  GURL new_url;
  ASSERT_TRUE(
      ContentBrowserClientHelper::TranslateIPFSURL(url, &new_url, false));
  EXPECT_EQ(new_url, GURL(
      "https://dweb.link/ipns/QmSrPmbaUKA3ZodhzPWZnpFgcPMFWF4QsxXbkWfEptTBJd"));
}

TEST_F(IPFSHuhiContentBrowserClientTest, TranslateIPFSURLIPFSSchemeLocal) {
  GURL url("ipfs://QmfM2r8seH2GiRaC4esTjeraXEachRt8ZsSeGaWTPLyMoG");
  GURL new_url;
  ASSERT_TRUE(
      ContentBrowserClientHelper::TranslateIPFSURL(url, &new_url, true));
  EXPECT_EQ(new_url, GURL(
      "http://127.0.0.1:8080/ipfs/"
      "QmfM2r8seH2GiRaC4esTjeraXEachRt8ZsSeGaWTPLyMoG"));
}

TEST_F(IPFSHuhiContentBrowserClientTest, TranslateIPFSURLIPNSSchemeLocal) {
  GURL url("ipns://QmSrPmbaUKA3ZodhzPWZnpFgcPMFWF4QsxXbkWfEptTBJd");
  GURL new_url;
  ASSERT_TRUE(
      ContentBrowserClientHelper::TranslateIPFSURL(url, &new_url, true));
  EXPECT_EQ(new_url, GURL(
      "http://127.0.0.1:8080/ipns/"
      "QmSrPmbaUKA3ZodhzPWZnpFgcPMFWF4QsxXbkWfEptTBJd"));
}

TEST_F(IPFSHuhiContentBrowserClientTest, TranslateIPFSURLIPFSSchemeWithPath) {
  GURL url("ipfs://bafybeiemxf5abjwjbikoz4mc3a3dla6ual3jsgpdr4cjr3oz3evfyavhwq"
           "/wiki/Vincent_van_Gogh.html");
  GURL new_url;
  ASSERT_TRUE(
      ContentBrowserClientHelper::TranslateIPFSURL(url, &new_url, false));
  EXPECT_EQ(new_url, GURL(
      "https://dweb.link/ipfs/"
      "bafybeiemxf5abjwjbikoz4mc3a3dla6ual3jsgpdr4cjr3oz3evfyavhwq"
      "/wiki/Vincent_van_Gogh.html"));
}

}  // namespace ipfs
