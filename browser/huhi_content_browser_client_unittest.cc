/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/huhi_content_browser_client.h"

#include "huhi/components/huhi_wallet/browser/buildflags/buildflags.h"
#include "extensions/buildflags/buildflags.h"
#include "testing/gtest/include/gtest/gtest.h"

#if BUILDFLAG(ENABLE_EXTENSIONS)
#include "extensions/browser/extension_registry.h"
#include "extensions/common/constants.h"
#include "extensions/common/extension.h"
#include "extensions/common/extension_builder.h"
#endif

#if BUILDFLAG(HUHI_WALLET_ENABLED)
#include "chrome/test/base/chrome_render_view_host_test_harness.h"
#include "content/public/common/content_client.h"

namespace extensions {

class HuhiWalleBrowserClientUnitTest
    : public ChromeRenderViewHostTestHarness {
 public:
  HuhiWalleBrowserClientUnitTest() {}

  void SetUp() override {
    ChromeRenderViewHostTestHarness::SetUp();
    original_client_ = content::SetBrowserClientForTesting(&client_);
  }

  void TearDown() override {
    content::SetBrowserClientForTesting(original_client_);
    ChromeRenderViewHostTestHarness::TearDown();
  }

  void AddExtension() {
    DictionaryBuilder manifest;
    manifest.Set("name", "ext")
        .Set("version", "0.1")
        .Set("manifest_version", 2);
    extension_ = ExtensionBuilder()
                     .SetManifest(manifest.Build())
                     .SetID(ethereum_remote_client_extension_id)
                     .Build();
    ASSERT_TRUE(extension_);
    ExtensionRegistry::Get(browser_context())->AddReady(extension_.get());
  }

 private:
  scoped_refptr<const Extension> extension_;
  content::ContentBrowserClient client_;
  content::ContentBrowserClient* original_client_;
  DISALLOW_COPY_AND_ASSIGN(HuhiWalleBrowserClientUnitTest);
};

TEST_F(HuhiWalleBrowserClientUnitTest,
    DoesNotResolveEthereumRemoteClientIfNotInstalled) {
  GURL url("chrome://wallet/");
  ASSERT_FALSE(HuhiContentBrowserClient::HandleURLOverrideRewrite(
        &url, browser_context()));
}

TEST_F(HuhiWalleBrowserClientUnitTest,
    ResolvesEthereumRemoteClientIfInstalled) {
  AddExtension();
  GURL url("chrome://wallet/");
  ASSERT_TRUE(HuhiContentBrowserClient::HandleURLOverrideRewrite(
        &url, browser_context()));
  ASSERT_STREQ(url.spec().c_str(), ethereum_remote_client_base_url);
}

}  // namespace extensions
#endif

using HuhiContentBrowserClientTest = testing::Test;

TEST_F(HuhiContentBrowserClientTest, ResolvesSync) {
  GURL url("chrome://sync/");
  ASSERT_TRUE(
    HuhiContentBrowserClient::HandleURLOverrideRewrite(&url, nullptr));
  ASSERT_STREQ(url.spec().c_str(), "chrome://settings/huhiSync");

  GURL url2("chrome://sync/");
  ASSERT_TRUE(
    HuhiContentBrowserClient::HandleURLOverrideRewrite(&url2, nullptr));
}

TEST_F(HuhiContentBrowserClientTest, ResolvesWelcomePage) {
  GURL url("chrome://welcome/");
  ASSERT_TRUE(
      HuhiContentBrowserClient::HandleURLOverrideRewrite(&url, nullptr));
}
