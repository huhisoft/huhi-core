/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/themes/huhi_dark_mode_utils.h"

namespace dark_mode {

void MigrateHuhiDarkModePrefs(Profile* profile) {
}

void RegisterHuhiDarkModeLocalStatePrefs(PrefRegistrySimple* registry) {
}

void RegisterHuhiDarkModePrefsForMigration(
    user_prefs::PrefRegistrySyncable* registry) {
}

bool SystemDarkModeEnabled() {
  return false;
}

void SetUseSystemDarkModeEnabledForTest(bool enabled) {
}

std::string GetStringFromHuhiDarkModeType(HuhiDarkModeType type) {
  return "Default";
}

void SetHuhiDarkModeType(const std::string& type) {
}

void SetHuhiDarkModeType(HuhiDarkModeType type) {
}

HuhiDarkModeType GetActiveHuhiDarkModeType() {
  return HuhiDarkModeType::HUHI_DARK_MODE_TYPE_DEFAULT;
}

HuhiDarkModeType GetHuhiDarkModeType() {
  return HuhiDarkModeType::HUHI_DARK_MODE_TYPE_DEFAULT;
}

base::Value GetHuhiDarkModeTypeList() {
  return base::Value(base::Value::Type::LIST);
}

void SetSystemDarkMode(HuhiDarkModeType type) {
}

}  // namespace dark_mode
