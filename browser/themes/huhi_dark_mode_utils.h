/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_THEMES_HUHI_DARK_MODE_UTILS_H_
#define HUHI_BROWSER_THEMES_HUHI_DARK_MODE_UTILS_H_

#include <string>

#include "base/values.h"
#include "build/build_config.h"

class PrefRegistrySimple;
class Profile;

namespace user_prefs {
class PrefRegistrySyncable;
}  // namespace user_prefs

namespace dark_mode {

enum class HuhiDarkModeType {
  // DEFAULT type acts as two ways depends on system theme mode.
  // If system dark mode is not supported, we override it with channel based
  // policy. In this case, user can see dark or light option in settings.
  // Otherwise, it acts like system dark mode mode. It respects system's dark
  // mode. In this case, user can see all three options in theme settings.
  HUHI_DARK_MODE_TYPE_DEFAULT,
  HUHI_DARK_MODE_TYPE_DARK,
  HUHI_DARK_MODE_TYPE_LIGHT,
};

// APIs for prefs.
void MigrateHuhiDarkModePrefs(Profile* profile);
void RegisterHuhiDarkModePrefsForMigration(
    user_prefs::PrefRegistrySyncable* registry);
void RegisterHuhiDarkModeLocalStatePrefs(PrefRegistrySimple* registry);

std::string GetStringFromHuhiDarkModeType(HuhiDarkModeType type);
base::Value GetHuhiDarkModeTypeList();
void SetHuhiDarkModeType(const std::string& type);
void SetHuhiDarkModeType(HuhiDarkModeType type);
// Returns current effective theme type. dark or light.
HuhiDarkModeType GetActiveHuhiDarkModeType();
// Returns current theme type.
// dark/light will be returned if platform doesn't support system dark mode.
// Otherwise, returns default/dark/light.
HuhiDarkModeType GetHuhiDarkModeType();
bool SystemDarkModeEnabled();
void SetUseSystemDarkModeEnabledForTest(bool enabled);

// When system supports system per-application system theme changing, set it.
// Currently, only MacOS support it.
// Otherewise, we need to overrides from native theme level and explicitly
// notifying to let observers know.
// By overriding, base ui components also use same huhi theme type.
void SetSystemDarkMode(HuhiDarkModeType type);

}  // namespace dark_mode

#endif  // HUHI_BROWSER_THEMES_HUHI_DARK_MODE_UTILS_H_
