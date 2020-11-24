/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_ADS_BROWSER_BACKGROUND_HELPER_LINUX_H_
#define HUHI_COMPONENTS_HUHI_ADS_BROWSER_BACKGROUND_HELPER_LINUX_H_

#include "base/macros.h"
#include "base/memory/singleton.h"
#include "base/memory/weak_ptr.h"
#include "huhi/components/huhi_ads/browser/background_helper.h"
#include "chrome/browser/ui/browser_list_observer.h"

namespace huhi_ads {

class BackgroundHelperLinux :
    public BackgroundHelper,
    public base::SupportsWeakPtr<BackgroundHelperLinux>,
    public BrowserListObserver {
 public:
  BackgroundHelperLinux(const BackgroundHelperLinux&) = delete;
  BackgroundHelperLinux& operator=(const BackgroundHelperLinux&) = delete;

  static BackgroundHelperLinux* GetInstance();

 private:
  friend struct base::DefaultSingletonTraits<BackgroundHelperLinux>;

  BackgroundHelperLinux();
  ~BackgroundHelperLinux() override;

  // BrowserListObserver overrides
  void OnBrowserSetLastActive(Browser* browser) override;
  void OnBrowserNoLongerActive(Browser* browser) override;

  // BackgroundHelper impl
  bool IsForeground() const override;
};

}  // namespace huhi_ads

#endif  // HUHI_COMPONENTS_HUHI_ADS_BROWSER_BACKGROUND_HELPER_LINUX_H_
