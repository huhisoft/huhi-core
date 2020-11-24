/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/ui/views/infobars/huhi_wayback_machine_infobar_view.h"

#include <string>
#include <utility>

#include "huhi/browser/infobars/huhi_wayback_machine_delegate_impl.h"
#include "huhi/browser/ui/views/infobars/huhi_wayback_machine_infobar_contents_view.h"
#include "huhi/components/huhi_wayback_machine/huhi_wayback_machine_infobar_delegate.h"

// static
std::unique_ptr<infobars::InfoBar>
HuhiWaybackMachineDelegateImpl::CreateInfoBarView(
    std::unique_ptr<HuhiWaybackMachineInfoBarDelegate> delegate,
    content::WebContents* contents) {
  return std::make_unique<HuhiWaybackMachineInfoBarView>(std::move(delegate),
                                                          contents);
}

HuhiWaybackMachineInfoBarView::HuhiWaybackMachineInfoBarView(
      std::unique_ptr<HuhiWaybackMachineInfoBarDelegate> delegate,
      content::WebContents* contents)
    : InfoBarView(std::move(delegate)) {
  sub_views_ = new HuhiWaybackMachineInfoBarContentsView(contents);
  sub_views_->SizeToPreferredSize();
  AddChildView(sub_views_);
}

HuhiWaybackMachineInfoBarView::~HuhiWaybackMachineInfoBarView() {
}

void HuhiWaybackMachineInfoBarView::Layout() {
  InfoBarView::Layout();
  // |sub_views_| occupies from the beginning.
  // Don't adjust child view's height. Just use their preferred height.
  // It can cause infinite Layout loop because of infobar's height
  // re-calculation during the animation.
  sub_views_->SetBounds(0, OffsetY(sub_views_), EndX(), sub_views_->height());
}
