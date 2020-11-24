/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "base/path_service.h"
#include "base/strings/stringprintf.h"
#include "base/task/post_task.h"
#include "base/test/thread_test_helper.h"
#include "huhi/browser/huhi_browser_process_impl.h"
#include "huhi/browser/huhi_content_browser_client.h"
#include "huhi/browser/extensions/huhi_base_local_data_files_browsertest.h"
#include "huhi/common/huhi_paths.h"
#include "huhi/common/pref_names.h"
#include "huhi/components/huhi_shields/browser/huhi_shields_util.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/extensions/extension_browsertest.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/common/chrome_content_client.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "chrome/test/base/ui_test_utils.h"
#include "components/permissions/permission_request.h"
#include "components/prefs/pref_service.h"
#include "content/public/browser/render_frame_host.h"
#include "content/public/test/browser_test.h"
#include "content/public/test/browser_test_utils.h"
#include "net/dns/mock_host_resolver.h"

using huhi_shields::ControlType;

const char kEmbeddedTestServerDirectory[] = "canvas";
const char kTitleScript[] = "domAutomationController.send(document.title);";

class HuhiOffscreenCanvasFarblingBrowserTest : public InProcessBrowserTest {
 public:
  void SetUpOnMainThread() override {
    InProcessBrowserTest::SetUpOnMainThread();

    content_client_.reset(new ChromeContentClient);
    content::SetContentClient(content_client_.get());
    browser_content_client_.reset(new HuhiContentBrowserClient());
    content::SetBrowserClientForTesting(browser_content_client_.get());

    host_resolver()->AddRule("*", "127.0.0.1");
    content::SetupCrossSiteRedirector(embedded_test_server());

    huhi::RegisterPathProvider();
    base::FilePath test_data_dir;
    base::PathService::Get(huhi::DIR_TEST_DATA, &test_data_dir);
    test_data_dir = test_data_dir.AppendASCII(kEmbeddedTestServerDirectory);
    embedded_test_server()->ServeFilesFromDirectory(test_data_dir);

    ASSERT_TRUE(embedded_test_server()->Start());

    top_level_page_url_ = embedded_test_server()->GetURL("a.com", "/");
    offscreen_farbling_url_ =
        embedded_test_server()->GetURL("a.com", "/offscreen-farbling.html");
  }

  void TearDown() override {
    browser_content_client_.reset();
    content_client_.reset();
  }

  const GURL& offscreen_farbling_url() { return offscreen_farbling_url_; }

  HostContentSettingsMap* content_settings() {
    return HostContentSettingsMapFactory::GetForProfile(browser()->profile());
  }

  void AllowFingerprinting() {
    huhi_shields::SetFingerprintingControlType(
        content_settings(), ControlType::ALLOW, top_level_page_url_);
  }

  void BlockFingerprinting() {
    huhi_shields::SetFingerprintingControlType(
        content_settings(), ControlType::BLOCK, top_level_page_url_);
  }

  void SetFingerprintingDefault() {
    huhi_shields::SetFingerprintingControlType(
        content_settings(), ControlType::DEFAULT, top_level_page_url_);
  }

  template <typename T>
  std::string ExecScriptGetStr(const std::string& script, T* frame) {
    std::string value;
    EXPECT_TRUE(ExecuteScriptAndExtractString(frame, script, &value));
    return value;
  }

  content::WebContents* contents() {
    return browser()->tab_strip_model()->GetActiveWebContents();
  }

  bool NavigateToURLUntilLoadStop(const GURL& url) {
    ui_test_utils::NavigateToURL(browser(), url);
    return WaitForLoadStop(contents());
  }

 private:
  GURL top_level_page_url_;
  GURL offscreen_farbling_url_;
  std::unique_ptr<ChromeContentClient> content_client_;
  std::unique_ptr<HuhiContentBrowserClient> browser_content_client_;
};

IN_PROC_BROWSER_TEST_F(HuhiOffscreenCanvasFarblingBrowserTest,
                       MustNotTimeout) {
  AllowFingerprinting();
  NavigateToURLUntilLoadStop(offscreen_farbling_url());
  // NavigateToURLUntilLoadStop() will return before our Worker has a chance to
  // run its code to completion, so we block here until document.title changes.
  // This will happen relatively quickly if things are going well inside the
  // Worker. If the browser crashes while executing the Worker code (which is
  // what this test is really testing), then this will never unblock and the
  // entire browser test will eventually time out. Timing out indicates a fatal
  // error.
  while (ExecScriptGetStr(kTitleScript, contents()) == "") {
  }
  EXPECT_EQ(ExecScriptGetStr(kTitleScript, contents()), "pass");

  BlockFingerprinting();
  NavigateToURLUntilLoadStop(offscreen_farbling_url());
  while (ExecScriptGetStr(kTitleScript, contents()) == "") {
  }
  EXPECT_EQ(ExecScriptGetStr(kTitleScript, contents()), "pass");

  SetFingerprintingDefault();
  NavigateToURLUntilLoadStop(offscreen_farbling_url());
  while (ExecScriptGetStr(kTitleScript, contents()) == "") {
  }
  EXPECT_EQ(ExecScriptGetStr(kTitleScript, contents()), "pass");
}
