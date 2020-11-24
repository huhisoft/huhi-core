/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/ui/views/huhi_views_delegate_linux.h"
#include "chrome/grit/chrome_unscaled_resources.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "content/public/test/browser_test.h"
#include "ui/base/resource/resource_bundle.h"
#include "ui/views/views_delegate.h"

using HuhiViewsDelegateViewLinuxBrowserTest = InProcessBrowserTest;

IN_PROC_BROWSER_TEST_F(HuhiViewsDelegateViewLinuxBrowserTest,
                       GetDefaultWindowIconTest) {
  auto env = base::Environment::Create();
  views::ViewsDelegate* views_delegate = views::ViewsDelegate::GetInstance();
  auto& rb = ui::ResourceBundle::GetSharedInstance();

#if defined(OFFICIAL_BUILD)
  env->SetVar("CHROME_VERSION_EXTRA", LINUX_CHANNEL_STABLE);
  EXPECT_EQ(rb.GetImageSkiaNamed(IDR_PRODUCT_LOGO_128)->bitmap(),
            views_delegate->GetDefaultWindowIcon()->bitmap());
  env->SetVar("CHROME_VERSION_EXTRA", LINUX_CHANNEL_BETA);
  EXPECT_EQ(rb.GetImageSkiaNamed(IDR_PRODUCT_LOGO_128_BETA)->bitmap(),
            views_delegate->GetDefaultWindowIcon()->bitmap());
  env->SetVar("CHROME_VERSION_EXTRA", LINUX_CHANNEL_DEV);
  EXPECT_EQ(rb.GetImageSkiaNamed(IDR_PRODUCT_LOGO_128_DEV)->bitmap(),
            views_delegate->GetDefaultWindowIcon()->bitmap());
  env->SetVar("CHROME_VERSION_EXTRA", HUHI_LINUX_CHANNEL_DEV);
  EXPECT_EQ(rb.GetImageSkiaNamed(IDR_PRODUCT_LOGO_128_DEV)->bitmap(),
            views_delegate->GetDefaultWindowIcon()->bitmap());
  env->SetVar("CHROME_VERSION_EXTRA", HUHI_LINUX_CHANNEL_NIGHTLY);
  EXPECT_EQ(rb.GetImageSkiaNamed(IDR_PRODUCT_LOGO_128_NIGHTLY)->bitmap(),
            views_delegate->GetDefaultWindowIcon()->bitmap());
#else  // OFFICIAL_BUILD
  EXPECT_EQ(rb.GetImageSkiaNamed(IDR_PRODUCT_LOGO_128_DEVELOPMENT)->bitmap(),
            views_delegate->GetDefaultWindowIcon()->bitmap());
#endif
}
