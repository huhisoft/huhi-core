/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/ui/webui/settings/default_huhi_shields_handler.h"

#include <string>

#include "base/bind.h"
#include "base/values.h"
#include "huhi/components/huhi_shields/browser/huhi_shields_util.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "content/public/browser/web_ui.h"

using huhi_shields::ControlType;
using huhi_shields::ControlTypeFromString;
using huhi_shields::ControlTypeToString;

void DefaultHuhiShieldsHandler::RegisterMessages() {
  profile_ = Profile::FromWebUI(web_ui());
  web_ui()->RegisterMessageCallback(
      "isAdControlEnabled",
      base::BindRepeating(&DefaultHuhiShieldsHandler::IsAdControlEnabled,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "setAdControlType",
      base::BindRepeating(&DefaultHuhiShieldsHandler::SetAdControlType,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "isFirstPartyCosmeticFilteringEnabled",
      base::BindRepeating(
          &DefaultHuhiShieldsHandler::IsFirstPartyCosmeticFilteringEnabled,
          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "setCosmeticFilteringControlType",
      base::BindRepeating(
          &DefaultHuhiShieldsHandler::SetCosmeticFilteringControlType,
          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "getCookieControlType",
      base::BindRepeating(&DefaultHuhiShieldsHandler::GetCookieControlType,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "setCookieControlType",
      base::BindRepeating(&DefaultHuhiShieldsHandler::SetCookieControlType,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "getFingerprintingControlType",
      base::BindRepeating(
          &DefaultHuhiShieldsHandler::GetFingerprintingControlType,
          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "setFingerprintingControlType",
      base::BindRepeating(
          &DefaultHuhiShieldsHandler::SetFingerprintingControlType,
          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "setHTTPSEverywhereEnabled",
      base::BindRepeating(
          &DefaultHuhiShieldsHandler::SetHTTPSEverywhereEnabled,
          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "setNoScriptControlType",
      base::BindRepeating(&DefaultHuhiShieldsHandler::SetNoScriptControlType,
                          base::Unretained(this)));
}

void DefaultHuhiShieldsHandler::IsAdControlEnabled(
    const base::ListValue* args) {
  CHECK_EQ(args->GetSize(), 1U);
  CHECK(profile_);

  ControlType setting = huhi_shields::GetAdControlType(
      HostContentSettingsMapFactory::GetForProfile(profile_), GURL());

  AllowJavascript();
  ResolveJavascriptCallback(
      args->GetList()[0].Clone(),
      base::Value(setting == ControlType::BLOCK));
}

void DefaultHuhiShieldsHandler::SetAdControlType(const base::ListValue* args) {
  CHECK_EQ(args->GetSize(), 1U);
  CHECK(profile_);
  bool value;
  args->GetBoolean(0, &value);

  huhi_shields::SetAdControlType(
      HostContentSettingsMapFactory::GetForProfile(profile_),
      value ? ControlType::BLOCK
            : ControlType::ALLOW,
      GURL(),
      g_browser_process->local_state());
}

void DefaultHuhiShieldsHandler::IsFirstPartyCosmeticFilteringEnabled(
    const base::ListValue* args) {
  CHECK_EQ(args->GetSize(), 1U);
  CHECK(profile_);

  bool enabled = huhi_shields::IsFirstPartyCosmeticFilteringEnabled(
      HostContentSettingsMapFactory::GetForProfile(profile_),
      GURL());

  AllowJavascript();
  ResolveJavascriptCallback(
      args->GetList()[0].Clone(),
      base::Value(enabled));
}

void DefaultHuhiShieldsHandler::SetCosmeticFilteringControlType(
    const base::ListValue* args) {
  CHECK_EQ(args->GetSize(), 1U);
  CHECK(profile_);
  std::string value;
  args->GetString(0, &value);

  huhi_shields::SetCosmeticFilteringControlType(
      HostContentSettingsMapFactory::GetForProfile(profile_),
      ControlTypeFromString(value),
      GURL(),
      g_browser_process->local_state());
}

void DefaultHuhiShieldsHandler::GetCookieControlType(
    const base::ListValue* args) {
  CHECK_EQ(args->GetSize(), 1U);
  CHECK(profile_);

  ControlType setting = huhi_shields::GetCookieControlType(
      HostContentSettingsMapFactory::GetForProfile(profile_),
      GURL());

  AllowJavascript();
  ResolveJavascriptCallback(
      args->GetList()[0].Clone(),
      base::Value(ControlTypeToString(setting)));
}

void DefaultHuhiShieldsHandler::SetCookieControlType(
    const base::ListValue* args) {
  CHECK_EQ(args->GetSize(), 1U);
  CHECK(profile_);
  std::string value;
  args->GetString(0, &value);

  huhi_shields::SetCookieControlType(
      HostContentSettingsMapFactory::GetForProfile(profile_),
      ControlTypeFromString(value),
      GURL(),
      g_browser_process->local_state());
}

void DefaultHuhiShieldsHandler::GetFingerprintingControlType(
    const base::ListValue* args) {
  CHECK_EQ(args->GetSize(), 1U);
  CHECK(profile_);

  ControlType setting = huhi_shields::GetFingerprintingControlType(
      HostContentSettingsMapFactory::GetForProfile(profile_),
      GURL());

  AllowJavascript();
  ResolveJavascriptCallback(
      args->GetList()[0].Clone(),
      base::Value(ControlTypeToString(setting)));
}

void DefaultHuhiShieldsHandler::SetFingerprintingControlType(
    const base::ListValue* args) {
  CHECK_EQ(args->GetSize(), 1U);
  CHECK(profile_);
  std::string value;
  args->GetString(0, &value);

  huhi_shields::SetFingerprintingControlType(
      HostContentSettingsMapFactory::GetForProfile(profile_),
      ControlTypeFromString(value),
      GURL(),
      g_browser_process->local_state());
}

void DefaultHuhiShieldsHandler::SetHTTPSEverywhereEnabled(
    const base::ListValue* args) {
  CHECK_EQ(args->GetSize(), 1U);
  CHECK(profile_);
  bool value;
  args->GetBoolean(0, &value);

  huhi_shields::SetHTTPSEverywhereEnabled(
      HostContentSettingsMapFactory::GetForProfile(profile_),
      value,
      GURL(),
      g_browser_process->local_state());
}

void DefaultHuhiShieldsHandler::SetNoScriptControlType(
    const base::ListValue* args) {
  CHECK_EQ(args->GetSize(), 1U);
  CHECK(profile_);
  bool value;
  args->GetBoolean(0, &value);

  huhi_shields::SetNoScriptControlType(
      HostContentSettingsMapFactory::GetForProfile(profile_),
      value ? ControlType::BLOCK
            : ControlType::ALLOW,
      GURL(),
      g_browser_process->local_state());
}
