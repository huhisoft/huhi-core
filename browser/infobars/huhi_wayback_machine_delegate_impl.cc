/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/infobars/huhi_wayback_machine_delegate_impl.h"

#include "base/command_line.h"
#include "huhi/common/huhi_switches.h"
#include "huhi/components/huhi_wayback_machine/huhi_wayback_machine_infobar_delegate.h"
#include "huhi/components/huhi_wayback_machine/huhi_wayback_machine_tab_helper.h"
#include "components/infobars/core/infobar.h"
#include "chrome/browser/infobars/infobar_service.h"

// static
void HuhiWaybackMachineDelegateImpl::AttachTabHelperIfNeeded(
    content::WebContents* web_contents) {
  if (!base::CommandLine::ForCurrentProcess()->HasSwitch(
          switches::kDisableHuhiWaybackMachineExtension)) {
    HuhiWaybackMachineTabHelper::CreateForWebContents(web_contents);
    auto* tab_helper =
        HuhiWaybackMachineTabHelper::FromWebContents(web_contents);
    tab_helper->set_delegate(
        std::make_unique<HuhiWaybackMachineDelegateImpl>());
  }
}

HuhiWaybackMachineDelegateImpl::HuhiWaybackMachineDelegateImpl() = default;
HuhiWaybackMachineDelegateImpl::~HuhiWaybackMachineDelegateImpl() = default;


void HuhiWaybackMachineDelegateImpl::CreateInfoBar(
    content::WebContents* web_contents) {
  InfoBarService::FromWebContents(web_contents)->AddInfoBar(
      CreateInfoBarView(
          std::make_unique<HuhiWaybackMachineInfoBarDelegate>(),
          web_contents),
      true);
}
