/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_WEBUI_HUHI_WALLET_UI_H_
#define HUHI_BROWSER_UI_WEBUI_HUHI_WALLET_UI_H_

#include <string>

#include "huhi/browser/ui/webui/basic_ui.h"

class HuhiWalletUI : public BasicUI {
 public:
  HuhiWalletUI(content::WebUI* web_ui, const std::string& host);
  ~HuhiWalletUI() override;

 private:
  DISALLOW_COPY_AND_ASSIGN(HuhiWalletUI);
};

#endif  // HUHI_BROWSER_UI_WEBUI_HUHI_WALLET_UI_H_
