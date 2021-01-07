// Copyright (c) 2020 The Huhi Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#include "base/path_service.h"
#include "huhi/common/huhi_paths.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "chrome/test/base/ui_test_utils.h"
#include "content/public/test/browser_test.h"
#include "content/public/test/browser_test_utils.h"

namespace {

const char kDetectHuhiTest[] = "/detect_huhi.html";

}  // namespace

class NavigatorGetHuhiDetectedTest : public InProcessBrowserTest {
 public:
  void SetUpOnMainThread() override {
    InProcessBrowserTest::SetUpOnMainThread();

    content::SetupCrossSiteRedirector(embedded_test_server());

    huhi::RegisterPathProvider();
    base::FilePath test_data_dir;
    base::PathService::Get(huhi::DIR_TEST_DATA, &test_data_dir);
    embedded_test_server()->ServeFilesFromDirectory(test_data_dir);

    ASSERT_TRUE(embedded_test_server()->Start());
  }
};

IN_PROC_BROWSER_TEST_F(NavigatorGetHuhiDetectedTest, IsDetected) {
  GURL url = embedded_test_server()->GetURL(kDetectHuhiTest);
  ui_test_utils::NavigateToURL(browser(), url);
  content::WebContents* contents =
      browser()->tab_strip_model()->GetActiveWebContents();
  EXPECT_EQ(true, EvalJs(contents, "getHuhiDetected()"));
}
