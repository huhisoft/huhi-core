/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_INFOBARS_HUHI_WAYBACK_MACHINE_DELEGATE_IMPL_H_
#define HUHI_BROWSER_INFOBARS_HUHI_WAYBACK_MACHINE_DELEGATE_IMPL_H_

#include <memory>

#include "huhi/components/huhi_wayback_machine/huhi_wayback_machine_delegate.h"

namespace content {
class WebContents;
}  // namespace content

namespace infobars {
class InfoBar;
}  // namespace infobars

class HuhiWaybackMachineDelegateImpl : public HuhiWaybackMachineDelegate {
 public:
  static void AttachTabHelperIfNeeded(content::WebContents* web_contents);

  HuhiWaybackMachineDelegateImpl();
  ~HuhiWaybackMachineDelegateImpl() override;

  HuhiWaybackMachineDelegateImpl(
      const HuhiWaybackMachineDelegateImpl&) = delete;
  HuhiWaybackMachineDelegateImpl& operator=(
      const HuhiWaybackMachineDelegateImpl&) = delete;

 private:
  // HuhiWaybackMachineDelegate overrides:
  void CreateInfoBar(content::WebContents* web_contents) override;

  std::unique_ptr<infobars::InfoBar> CreateInfoBarView(
      std::unique_ptr<HuhiWaybackMachineInfoBarDelegate> delegate,
      content::WebContents* contents);
};

#endif  // HUHI_BROWSER_INFOBARS_HUHI_WAYBACK_MACHINE_DELEGATE_IMPL_H_
