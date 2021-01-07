// Copyright (c) 2020 The Huhi Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HUHI_BROWSER_UI_WEBUI_NEW_TAB_PAGE_HUHI_NEW_TAB_UI_H_
#define HUHI_BROWSER_UI_WEBUI_NEW_TAB_PAGE_HUHI_NEW_TAB_UI_H_

#include <string>

#include "base/macros.h"
#include "content/public/browser/web_ui_controller.h"

class HuhiNewTabUI : public content::WebUIController {
 public:
  HuhiNewTabUI(content::WebUI* web_ui, const std::string& name);
  ~HuhiNewTabUI() override;
 private:
  DISALLOW_COPY_AND_ASSIGN(HuhiNewTabUI);
};

#endif  // HUHI_BROWSER_UI_WEBUI_NEW_TAB_PAGE_HUHI_NEW_TAB_UI_H_
