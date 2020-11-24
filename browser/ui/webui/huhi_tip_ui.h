/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_WEBUI_HUHI_TIP_UI_H_
#define HUHI_BROWSER_UI_WEBUI_HUHI_TIP_UI_H_

#include <string>

#include "base/macros.h"
#include "chrome/browser/ui/webui/constrained_web_dialog_ui.h"

class HuhiTipUI : public ConstrainedWebDialogUI {
 public:
  HuhiTipUI(content::WebUI* web_ui, const std::string& host);
  ~HuhiTipUI() override;

 private:
  DISALLOW_COPY_AND_ASSIGN(HuhiTipUI);
};

#endif  // HUHI_BROWSER_UI_WEBUI_HUHI_TIP_UI_H_
