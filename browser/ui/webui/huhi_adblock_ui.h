/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_WEBUI_HUHI_ADBLOCK_UI_H_
#define HUHI_BROWSER_UI_WEBUI_HUHI_ADBLOCK_UI_H_

#include <memory>
#include <string>

#include "huhi/browser/ui/webui/basic_ui.h"

class PrefChangeRegistrar;

class HuhiAdblockUI : public BasicUI {
 public:
  HuhiAdblockUI(content::WebUI* web_ui, const std::string& host);
  ~HuhiAdblockUI() override;

 private:
  // BasicUI overrides:
  void UpdateWebUIProperties() override;

  void CustomizeWebUIProperties(content::RenderFrameHost* render_frame_host);
  void OnPreferenceChanged();

  std::unique_ptr<PrefChangeRegistrar> pref_change_registrar_;

  DISALLOW_COPY_AND_ASSIGN(HuhiAdblockUI);
};

#endif  // HUHI_BROWSER_UI_WEBUI_HUHI_ADBLOCK_UI_H_
