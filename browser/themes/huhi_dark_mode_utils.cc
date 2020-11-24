/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/themes/huhi_dark_mode_utils.h"

#include <utility>

#include "base/command_line.h"
#include "base/strings/string_util.h"
#include "huhi/browser/themes/huhi_dark_mode_utils_internal.h"
#include "huhi/common/huhi_switches.h"
#include "huhi/common/pref_names.h"
#include "huhi/grit/huhi_generated_resources.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/common/channel_info.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/pref_service.h"
#include "components/pref_registry/pref_registry_syncable.h"
#include "components/version_info/channel.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/native_theme/native_theme.h"

namespace {

bool g_is_test_ = false;
bool g_system_dark_mode_enabled_in_test_ = false;

void ClearHuhiDarkModeProfilePrefs(Profile* profile) {
  PrefService* prefs = profile->GetPrefs();
  prefs->ClearPref(kHuhiThemeType);
  prefs->ClearPref(kUseOverriddenHuhiThemeType);
}

dark_mode::HuhiDarkModeType GetDarkModeTypeBasedOnChannel() {
  switch (chrome::GetChannel()) {
    case version_info::Channel::STABLE:
    case version_info::Channel::BETA:
      return dark_mode::HuhiDarkModeType::HUHI_DARK_MODE_TYPE_LIGHT;
    case version_info::Channel::DEV:
    case version_info::Channel::CANARY:
    case version_info::Channel::UNKNOWN:
    default:
      return dark_mode::HuhiDarkModeType::HUHI_DARK_MODE_TYPE_DARK;
  }
}

dark_mode::HuhiDarkModeType GetDarkModeSwitchValue(
    const base::CommandLine& command_line) {
  DCHECK(command_line.HasSwitch(switches::kDarkMode));

  std::string requested_dark_mode_value =
      command_line.GetSwitchValueASCII(switches::kDarkMode);
  std::string requested_dark_mode_value_lower =
      base::ToLowerASCII(requested_dark_mode_value);
  if (requested_dark_mode_value_lower == "light")
    return dark_mode::HuhiDarkModeType::HUHI_DARK_MODE_TYPE_LIGHT;
  if (requested_dark_mode_value_lower == "dark")
    return dark_mode::HuhiDarkModeType::HUHI_DARK_MODE_TYPE_DARK;

  NOTREACHED();
  return dark_mode::HuhiDarkModeType::HUHI_DARK_MODE_TYPE_LIGHT;
}

}  // namespace

namespace dark_mode {

void MigrateHuhiDarkModePrefs(Profile* profile) {
  auto* local_state = g_browser_process->local_state();
  // If migration is done, local state doesn't have default value because
  // they were explicitly set by primary prefs' value. After that, we don't
  // need to try migration again and prefs from profiles are already cleared.
  if (local_state->FindPreference(kHuhiDarkMode)->IsDefaultValue()) {
    PrefService* prefs = profile->GetPrefs();
    local_state->SetInteger(kHuhiDarkMode,
                            prefs->GetInteger(kHuhiThemeType));
  }

  // Clear deprecated prefs.
  ClearHuhiDarkModeProfilePrefs(profile);
}

void RegisterHuhiDarkModeLocalStatePrefs(PrefRegistrySimple* registry) {
  registry->RegisterIntegerPref(
      kHuhiDarkMode,
      static_cast<int>(HuhiDarkModeType::HUHI_DARK_MODE_TYPE_DEFAULT));
}

void RegisterHuhiDarkModePrefsForMigration(
    user_prefs::PrefRegistrySyncable* registry) {
  registry->RegisterIntegerPref(
      kHuhiThemeType,
      static_cast<int>(HuhiDarkModeType::HUHI_DARK_MODE_TYPE_DEFAULT));
  registry->RegisterBooleanPref(kUseOverriddenHuhiThemeType, false);
}

bool SystemDarkModeEnabled() {
  if (g_is_test_)
    return g_system_dark_mode_enabled_in_test_;

  return ui::NativeTheme::GetInstanceForNativeUi()->SystemDarkModeSupported();
}

void SetUseSystemDarkModeEnabledForTest(bool enabled) {
  g_is_test_ = true;
  g_system_dark_mode_enabled_in_test_ = enabled;
}

std::string GetStringFromHuhiDarkModeType(HuhiDarkModeType type) {
  switch (type) {
    case HuhiDarkModeType::HUHI_DARK_MODE_TYPE_LIGHT:
      return "Light";
    case HuhiDarkModeType::HUHI_DARK_MODE_TYPE_DARK:
      return "Dark";
    default:
      NOTREACHED();
      return "Default";
  }
}

void SetHuhiDarkModeType(const std::string& type) {
  HuhiDarkModeType parsed_type =
      HuhiDarkModeType::HUHI_DARK_MODE_TYPE_DEFAULT;

  if (type == "Light") {
    parsed_type = HuhiDarkModeType::HUHI_DARK_MODE_TYPE_LIGHT;
  } else if (type == "Dark") {
    parsed_type = HuhiDarkModeType::HUHI_DARK_MODE_TYPE_DARK;
  }
  SetHuhiDarkModeType(parsed_type);
}

void SetHuhiDarkModeType(HuhiDarkModeType type) {
  g_browser_process->local_state()->SetInteger(kHuhiDarkMode,
                                               static_cast<int>(type));
}

HuhiDarkModeType GetActiveHuhiDarkModeType() {
  // allow override via cli flag
  const base::CommandLine& command_line =
      *base::CommandLine::ForCurrentProcess();
  if (command_line.HasSwitch(switches::kDarkMode))
    return GetDarkModeSwitchValue(command_line);

  HuhiDarkModeType type = static_cast<HuhiDarkModeType>(
      g_browser_process->local_state()->GetInteger(kHuhiDarkMode));
  if (type == HuhiDarkModeType::HUHI_DARK_MODE_TYPE_DEFAULT) {
    if (!SystemDarkModeEnabled())
      return GetDarkModeTypeBasedOnChannel();

    return ui::NativeTheme::GetInstanceForNativeUi()->ShouldUseDarkColors()
               ? HuhiDarkModeType::HUHI_DARK_MODE_TYPE_DARK
               : HuhiDarkModeType::HUHI_DARK_MODE_TYPE_LIGHT;
  }
  return type;
}

HuhiDarkModeType GetHuhiDarkModeType() {
  // allow override via cli flag
  const base::CommandLine& command_line =
      *base::CommandLine::ForCurrentProcess();
  if (command_line.HasSwitch(switches::kDarkMode))
    return GetDarkModeSwitchValue(command_line);

  HuhiDarkModeType type = static_cast<HuhiDarkModeType>(
      g_browser_process->local_state()->GetInteger(kHuhiDarkMode));
  if (type == HuhiDarkModeType::HUHI_DARK_MODE_TYPE_DEFAULT) {
    if (!SystemDarkModeEnabled())
      return GetDarkModeTypeBasedOnChannel();
    return type;
  }
  return type;
}

base::Value GetHuhiDarkModeTypeList() {
  base::Value list(base::Value::Type::LIST);

  if (SystemDarkModeEnabled()) {
    base::Value system_type(base::Value::Type::DICTIONARY);
    system_type.SetKey(
        "value",
        base::Value(static_cast<int>(
            HuhiDarkModeType::HUHI_DARK_MODE_TYPE_DEFAULT)));
    system_type.SetKey(
        "name",
        base::Value(l10n_util::GetStringUTF16(IDS_HUHI_THEME_TYPE_SYSTEM)));
    list.Append(std::move(system_type));
  }

  base::Value dark_type(base::Value::Type::DICTIONARY);
  dark_type.SetKey(
      "value",
      base::Value(static_cast<int>(
          HuhiDarkModeType::HUHI_DARK_MODE_TYPE_DARK)));
  dark_type.SetKey(
      "name",
      base::Value(l10n_util::GetStringUTF16(IDS_HUHI_THEME_TYPE_DARK)));
  list.Append(std::move(dark_type));

  base::Value light_type(base::Value::Type::DICTIONARY);
  light_type.SetKey(
      "value",
      base::Value(static_cast<int>(
          HuhiDarkModeType::HUHI_DARK_MODE_TYPE_LIGHT)));
  light_type.SetKey(
      "name",
      base::Value(l10n_util::GetStringUTF16(IDS_HUHI_THEME_TYPE_LIGHT)));
  list.Append(std::move(light_type));

  return list;
}

}  // namespace dark_mode
