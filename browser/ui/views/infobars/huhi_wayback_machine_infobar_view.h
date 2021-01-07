/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_VIEWS_INFOBARS_HUHI_WAYBACK_MACHINE_INFOBAR_VIEW_H_
#define HUHI_BROWSER_UI_VIEWS_INFOBARS_HUHI_WAYBACK_MACHINE_INFOBAR_VIEW_H_

#include <memory>

#include "chrome/browser/ui/views/infobars/infobar_view.h"

namespace content {
class WebContents;
}

class HuhiWaybackMachineInfoBarDelegate;

class HuhiWaybackMachineInfoBarView : public InfoBarView {
 public:
  HuhiWaybackMachineInfoBarView(
      std::unique_ptr<HuhiWaybackMachineInfoBarDelegate> delegate,
      content::WebContents* contents);
  ~HuhiWaybackMachineInfoBarView() override;

  HuhiWaybackMachineInfoBarView(
      const HuhiWaybackMachineInfoBarView&) = delete;
  HuhiWaybackMachineInfoBarView& operator=(
      const HuhiWaybackMachineInfoBarView&) = delete;

 private:
  // InfoBarView overrides:
  void Layout() override;

  views::View* sub_views_ = nullptr;
};

#endif  // HUHI_BROWSER_UI_VIEWS_INFOBARS_HUHI_WAYBACK_MACHINE_INFOBAR_VIEW_H_
