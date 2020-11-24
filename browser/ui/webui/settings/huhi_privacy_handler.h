/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_WEBUI_SETTINGS_HUHI_PRIVACY_HANDLER_H_
#define HUHI_BROWSER_UI_WEBUI_SETTINGS_HUHI_PRIVACY_HANDLER_H_

#include "huhi/components/p3a/buildflags.h"
#include "chrome/browser/ui/webui/settings/settings_page_ui_handler.h"
#include "components/prefs/pref_change_registrar.h"

namespace content {
class WebUIDataSource;
}

class Profile;

class HuhiPrivacyHandler : public settings::SettingsPageUIHandler {
 public:
  HuhiPrivacyHandler();
  ~HuhiPrivacyHandler() override;
  static void AddLoadTimeData(content::WebUIDataSource* data_source,
                              Profile* profile);

 private:
  // SettingsPageUIHandler overrides:
  void RegisterMessages() override;
  void OnJavascriptAllowed() override {}
  void OnJavascriptDisallowed() override {}

  void SetWebRTCPolicy(const base::ListValue* args);
  void GetWebRTCPolicy(const base::ListValue* args);

#if BUILDFLAG(HUHI_P3A_ENABLED)
  void SetP3AEnabled(const base::ListValue* args);
  void GetP3AEnabled(const base::ListValue* args);
  void OnP3AEnabledChanged();
#endif

  Profile* profile_ = nullptr;
  PrefChangeRegistrar local_state_change_registrar_;

  DISALLOW_COPY_AND_ASSIGN(HuhiPrivacyHandler);
};

#endif  // HUHI_BROWSER_UI_WEBUI_SETTINGS_HUHI_PRIVACY_HANDLER_H_
