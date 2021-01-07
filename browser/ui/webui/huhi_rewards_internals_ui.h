/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_WEBUI_HUHI_REWARDS_INTERNALS_UI_H_
#define HUHI_BROWSER_UI_WEBUI_HUHI_REWARDS_INTERNALS_UI_H_

#include <memory>
#include <string>

#include "base/memory/weak_ptr.h"
#include "huhi/browser/ui/webui/basic_ui.h"

class HuhiRewardsInternalsUI : public BasicUI {
 public:
  HuhiRewardsInternalsUI(content::WebUI* web_ui, const std::string& host);
  ~HuhiRewardsInternalsUI() override;

 private:
  DISALLOW_COPY_AND_ASSIGN(HuhiRewardsInternalsUI);
};

#endif  // HUHI_BROWSER_UI_WEBUI_HUHI_REWARDS_INTERNALS_UI_H_
