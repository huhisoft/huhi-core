/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_CHROME_BROWSER_PROFILES_RENDERER_UPDATER_H_
#define HUHI_CHROMIUM_SRC_CHROME_BROWSER_PROFILES_RENDERER_UPDATER_H_

#define HUHI_GET_GUEST_VIEW_DEFAULT_CONTENT_SETTING_RULES                    \
  rules->fingerprinting_rules.push_back(ContentSettingPatternSource(          \
      ContentSettingsPattern::Wildcard(), ContentSettingsPattern::Wildcard(), \
      base::Value::FromUniquePtrValue(                                        \
          content_settings::ContentSettingToValue(CONTENT_SETTING_ALLOW)),    \
      std::string(), incognito));                                             \
  rules->huhi_shields_rules.push_back(ContentSettingPatternSource(           \
      ContentSettingsPattern::Wildcard(), ContentSettingsPattern::Wildcard(), \
      base::Value::FromUniquePtrValue(                                        \
          content_settings::ContentSettingToValue(CONTENT_SETTING_ALLOW)),    \
      std::string(), incognito));

#include "../../../../../chrome/browser/profiles/renderer_updater.cc"

#endif  // HUHI_CHROMIUM_SRC_CHROME_BROWSER_PROFILES_RENDERER_UPDATER_H_
