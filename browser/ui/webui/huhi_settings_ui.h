/* Copyright 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_WEBUI_HUHI_SETTINGS_UI_H_
#define HUHI_BROWSER_UI_WEBUI_HUHI_SETTINGS_UI_H_

#include <memory>
#include <string>

#include "chrome/browser/ui/webui/settings/settings_ui.h"

namespace content {
class WebUIDataSource;
}

class Profile;

class HuhiSettingsUI : public settings::SettingsUI {
 public:
  HuhiSettingsUI(content::WebUI* web_ui, const std::string& host);
  ~HuhiSettingsUI() override;

  static void AddResources(content::WebUIDataSource* html_source,
                           Profile* profile);

  DISALLOW_COPY_AND_ASSIGN(HuhiSettingsUI);
};

#endif  // HUHI_BROWSER_UI_WEBUI_HUHI_SETTINGS_UI_H_
