/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_WEBUI_HUHI_REWARDS_PAGE_UI_H_
#define HUHI_BROWSER_UI_WEBUI_HUHI_REWARDS_PAGE_UI_H_

#include <memory>
#include <string>

#include "huhi/browser/ui/webui/basic_ui.h"

class HuhiRewardsPageUI : public BasicUI {
 public:
  HuhiRewardsPageUI(content::WebUI* web_ui, const std::string& host);
  ~HuhiRewardsPageUI() override;

 private:
  DISALLOW_COPY_AND_ASSIGN(HuhiRewardsPageUI);
};

#endif  // HUHI_BROWSER_UI_WEBUI_HUHI_REWARDS_PAGE_UI_H_
