/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/ui/webui/settings/huhi_appearance_handler.h"

#include "base/bind.h"
#include "base/strings/string_number_conversions.h"
#include "huhi/browser/ntp_background_images/view_counter_service_factory.h"
#include "huhi/browser/themes/huhi_dark_mode_utils.h"
#include "huhi/components/binance/browser/buildflags/buildflags.h"
#include "huhi/components/huhi_together/buildflags/buildflags.h"
#include "huhi/components/gemini/browser/buildflags/buildflags.h"
#include "huhi/components/moonpay/browser/buildflags/buildflags.h"
#include "huhi/components/ntp_widget_utils/browser/ntp_widget_utils_region.h"
#include "huhi/common/pref_names.h"
#include "huhi/components/ntp_background_images/browser/ntp_background_images_data.h"
#include "huhi/components/ntp_background_images/browser/view_counter_service.h"
#include "huhi/components/ntp_background_images/common/pref_names.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/profiles/profile.h"
#include "content/public/browser/web_ui.h"

#if BUILDFLAG(BINANCE_ENABLED)
#include "huhi/components/binance/browser/regions.h"
#endif

#if BUILDFLAG(HUHI_TOGETHER_ENABLED)
#include "huhi/components/huhi_together/browser/regions.h"
#endif

#if BUILDFLAG(GEMINI_ENABLED)
#include "huhi/components/gemini/browser/regions.h"
#endif

#if BUILDFLAG(MOONPAY_ENABLED)
#include "huhi/components/moonpay/browser/regions.h"
#endif

using ntp_background_images::ViewCounterServiceFactory;
using ntp_background_images::prefs::kNewTabPageSuperReferralThemesOption;

namespace {

bool IsSuperReferralActive(Profile* profile) {
  bool isSuperReferralActive = false;
  auto* service = ViewCounterServiceFactory::GetForProfile(profile);
  if (service) {
    auto* data = service->GetCurrentBrandedWallpaperData();
    if (data && data->IsSuperReferral()) {
      isSuperReferralActive = true;
    }
  }

  return isSuperReferralActive;
}

}  // namespace

HuhiAppearanceHandler::HuhiAppearanceHandler() {
  local_state_change_registrar_.Init(g_browser_process->local_state());
  local_state_change_registrar_.Add(
      kHuhiDarkMode,
      base::Bind(&HuhiAppearanceHandler::OnHuhiDarkModeChanged,
                 base::Unretained(this)));
}

HuhiAppearanceHandler::~HuhiAppearanceHandler() = default;

void HuhiAppearanceHandler::RegisterMessages() {
  profile_ = Profile::FromWebUI(web_ui());
  profile_state_change_registrar_.Init(profile_->GetPrefs());
  profile_state_change_registrar_.Add(
      kNewTabPageSuperReferralThemesOption,
      base::BindRepeating(&HuhiAppearanceHandler::OnPreferenceChanged,
      base::Unretained(this)));

  web_ui()->RegisterMessageCallback(
      "setHuhiThemeType",
      base::BindRepeating(&HuhiAppearanceHandler::SetHuhiThemeType,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "getHuhiThemeType",
      base::BindRepeating(&HuhiAppearanceHandler::GetHuhiThemeType,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "getIsSuperReferralActive",
      base::BindRepeating(&HuhiAppearanceHandler::GetIsSuperReferralActive,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "getIsBinanceSupported",
      base::BindRepeating(&HuhiAppearanceHandler::GetIsBinanceSupported,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "getIsHuhiTogetherSupported",
      base::BindRepeating(&HuhiAppearanceHandler::GetIsHuhiTogetherSupported,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "getIsGeminiSupported",
      base::BindRepeating(&HuhiAppearanceHandler::GetIsGeminiSupported,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "getIsBitcoinDotComSupported",
      base::BindRepeating(&HuhiAppearanceHandler::GetIsBitcoinDotComSupported,
                          base::Unretained(this)));
}

void HuhiAppearanceHandler::SetHuhiThemeType(const base::ListValue* args) {
  CHECK_EQ(args->GetSize(), 1U);
  AllowJavascript();

  int int_type;
  args->GetInteger(0, &int_type);
  dark_mode::SetHuhiDarkModeType(
      static_cast<dark_mode::HuhiDarkModeType>(int_type));
}

void HuhiAppearanceHandler::GetHuhiThemeType(const base::ListValue* args) {
  CHECK_EQ(args->GetSize(), 1U);

  AllowJavascript();
  // GetHuhiThemeType() should be used because settings option displays all
  // available options including default.
  ResolveJavascriptCallback(
      args->GetList()[0],
      base::Value(static_cast<int>(dark_mode::GetHuhiDarkModeType())));
}

void HuhiAppearanceHandler::GetIsSuperReferralActive(
    const base::ListValue* args) {
  CHECK_EQ(args->GetSize(), 1U);

  AllowJavascript();
  ResolveJavascriptCallback(args->GetList()[0],
                            base::Value(IsSuperReferralActive(profile_)));
}

void HuhiAppearanceHandler::GetIsBinanceSupported(
    const base::ListValue* args) {
  CHECK_EQ(args->GetSize(), 1U);

  AllowJavascript();

#if !BUILDFLAG(BINANCE_ENABLED)
  bool is_supported = false;
#else
  bool is_supported = ntp_widget_utils::IsRegionSupported(
      profile_->GetPrefs(), binance::unsupported_regions, false);
#endif

  ResolveJavascriptCallback(args->GetList()[0], base::Value(is_supported));
}

void HuhiAppearanceHandler::GetIsHuhiTogetherSupported(
    const base::ListValue* args) {
  CHECK_EQ(args->GetSize(), 1U);

  AllowJavascript();

#if !BUILDFLAG(HUHI_TOGETHER_ENABLED)
  bool is_supported = false;
#else
  bool is_supported = ntp_widget_utils::IsRegionSupported(
      profile_->GetPrefs(), huhi_together::supported_regions, true);
#endif

  ResolveJavascriptCallback(args->GetList()[0], base::Value(is_supported));
}

void HuhiAppearanceHandler::GetIsGeminiSupported(
    const base::ListValue* args) {
  CHECK_EQ(args->GetSize(), 1U);

  AllowJavascript();

#if !BUILDFLAG(GEMINI_ENABLED)
  bool is_supported = false;
#else
  bool is_supported = ntp_widget_utils::IsRegionSupported(
      profile_->GetPrefs(), gemini::supported_regions, true);
#endif

  ResolveJavascriptCallback(args->GetList()[0], base::Value(is_supported));
}

void HuhiAppearanceHandler::GetIsBitcoinDotComSupported(
    const base::ListValue* args) {
  CHECK_EQ(args->GetSize(), 1U);

  AllowJavascript();

#if !BUILDFLAG(MOONPAY_ENABLED)
  bool is_supported = false;
#else
  bool is_supported = ntp_widget_utils::IsRegionSupported(
      profile_->GetPrefs(), moonpay::bitcoin_dot_com_supported_regions, true);
#endif

  ResolveJavascriptCallback(args->GetList()[0], base::Value(is_supported));
}

void HuhiAppearanceHandler::OnHuhiDarkModeChanged() {
  // GetHuhiThemeType() should be used because settings option displays all
  // available options including default.
  if (IsJavascriptAllowed()) {
    FireWebUIListener(
        "huhi-theme-type-changed",
        base::Value(static_cast<int>(dark_mode::GetHuhiDarkModeType())));
  }
}

void HuhiAppearanceHandler::OnPreferenceChanged(const std::string& pref_name) {
  DCHECK_EQ(kNewTabPageSuperReferralThemesOption, pref_name);
  if (IsJavascriptAllowed()) {
    FireWebUIListener("super-referral-active-state-changed",
                      base::Value(IsSuperReferralActive(profile_)));
  }
}
