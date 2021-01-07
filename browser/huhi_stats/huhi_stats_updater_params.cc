/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <cmath>

#include "huhi/browser/huhi_stats/huhi_stats_updater_params.h"
#include "huhi/components/huhi_referrals/buildflags/buildflags.h"

#include "base/strings/string_util.h"
#include "base/time/time.h"
#include "huhi/common/pref_names.h"
#include "huhi/components/huhi_referrals/common/pref_names.h"
#include "huhi/components/huhi_stats/browser/huhi_stats_updater_util.h"
#include "chrome/browser/first_run/first_run.h"
#include "components/prefs/pref_service.h"

namespace huhi_stats {

base::Time HuhiStatsUpdaterParams::g_current_time;
bool HuhiStatsUpdaterParams::g_force_first_run = false;
static constexpr base::TimeDelta g_dtoi_delete_delta =
    base::TimeDelta::FromSeconds(14 * 24 * 60 * 60);

HuhiStatsUpdaterParams::HuhiStatsUpdaterParams(PrefService* pref_service)
    : HuhiStatsUpdaterParams(pref_service,
                              GetCurrentDateAsYMD(),
                              GetCurrentISOWeekNumber(),
                              GetCurrentMonth()) {}

HuhiStatsUpdaterParams::HuhiStatsUpdaterParams(PrefService* pref_service,
                                                 const std::string& ymd,
                                                 int woy,
                                                 int month)
    : pref_service_(pref_service), ymd_(ymd), woy_(woy), month_(month) {
  LoadPrefs();
}

HuhiStatsUpdaterParams::~HuhiStatsUpdaterParams() {}

std::string HuhiStatsUpdaterParams::GetDailyParam() const {
  return BooleanToString(
      base::CompareCaseInsensitiveASCII(ymd_, last_check_ymd_) == 1);
}

std::string HuhiStatsUpdaterParams::GetWeeklyParam() const {
  return BooleanToString(last_check_woy_ == 0 || woy_ != last_check_woy_);
}

std::string HuhiStatsUpdaterParams::GetMonthlyParam() const {
  return BooleanToString(last_check_month_ == 0 || month_ != last_check_month_);
}

std::string HuhiStatsUpdaterParams::GetFirstCheckMadeParam() const {
  return BooleanToString(!first_check_made_);
}

std::string HuhiStatsUpdaterParams::GetWeekOfInstallationParam() const {
  return week_of_installation_;
}

std::string HuhiStatsUpdaterParams::GetDateOfInstallationParam() const {
  return (GetCurrentTimeNow() - date_of_installation_ >= g_dtoi_delete_delta)
             ? "null"
             : huhi_stats::GetDateAsYMD(date_of_installation_);
}

std::string HuhiStatsUpdaterParams::GetReferralCodeParam() const {
  return referral_promo_code_.empty() ? "none" : referral_promo_code_;
}

void HuhiStatsUpdaterParams::LoadPrefs() {
  last_check_ymd_ = pref_service_->GetString(kLastCheckYMD);
  last_check_woy_ = pref_service_->GetInteger(kLastCheckWOY);
  last_check_month_ = pref_service_->GetInteger(kLastCheckMonth);
  first_check_made_ = pref_service_->GetBoolean(kFirstCheckMade);
  week_of_installation_ = pref_service_->GetString(kWeekOfInstallation);
  if (week_of_installation_.empty())
    week_of_installation_ = GetLastMondayAsYMD();
  if (ShouldForceFirstRun()) {
    date_of_installation_ = GetCurrentTimeNow();
  } else {
    date_of_installation_ = GetFirstRunTime(pref_service_);
    DCHECK(!date_of_installation_.is_null());
  }
#if BUILDFLAG(ENABLE_HUHI_REFERRALS)
  referral_promo_code_ = pref_service_->GetString(kReferralPromoCode);
#endif
}

void HuhiStatsUpdaterParams::SavePrefs() {
  pref_service_->SetString(kLastCheckYMD, ymd_);
  pref_service_->SetInteger(kLastCheckWOY, woy_);
  pref_service_->SetInteger(kLastCheckMonth, month_);
  pref_service_->SetBoolean(kFirstCheckMade, true);
  pref_service_->SetString(kWeekOfInstallation, week_of_installation_);
}

std::string HuhiStatsUpdaterParams::BooleanToString(bool bool_value) const {
  return bool_value ? "true" : "false";
}

std::string HuhiStatsUpdaterParams::GetCurrentDateAsYMD() const {
  return huhi_stats::GetDateAsYMD(GetCurrentTimeNow());
}

std::string HuhiStatsUpdaterParams::GetLastMondayAsYMD() const {
  base::Time now = GetCurrentTimeNow();
  base::Time::Exploded exploded;
  now.LocalExplode(&exploded);

  int days_adjusted =
      (exploded.day_of_week == 0) ? 6 : exploded.day_of_week - 1;
  base::Time last_monday = base::Time::FromJsTime(
      now.ToJsTime() - (days_adjusted * base::Time::kMillisecondsPerDay));

  return huhi_stats::GetDateAsYMD(last_monday);
}

int HuhiStatsUpdaterParams::GetCurrentMonth() const {
  base::Time now = GetCurrentTimeNow();
  base::Time::Exploded exploded;
  now.LocalExplode(&exploded);
  return exploded.month;
}

int HuhiStatsUpdaterParams::GetCurrentISOWeekNumber() const {
  return GetIsoWeekNumber(GetCurrentTimeNow());
}

base::Time HuhiStatsUpdaterParams::GetCurrentTimeNow() const {
  return g_current_time.is_null() ? base::Time::Now() : g_current_time;
}

// static
bool HuhiStatsUpdaterParams::ShouldForceFirstRun() const {
  return g_force_first_run;
}

// static
void HuhiStatsUpdaterParams::SetCurrentTimeForTest(
    const base::Time& current_time) {
  g_current_time = current_time;
}

// static
void HuhiStatsUpdaterParams::SetFirstRunForTest(bool first_run) {
  g_force_first_run = first_run;
}

// static
base::Time HuhiStatsUpdaterParams::GetFirstRunTime(PrefService* pref_service) {
#if defined(OS_ANDROID)
  // Android doesn't use a sentinel to track first run, so we use a
  // preference instead. kReferralAndroidFirstRunTimestamp is used because
  // previously only referrals needed to know the first run value.
  base::Time first_run_timestamp =
      pref_service->GetTime(kReferralAndroidFirstRunTimestamp);
  if (first_run_timestamp.is_null()) {
    first_run_timestamp = base::Time::Now();
    pref_service->SetTime(kReferralAndroidFirstRunTimestamp,
                          first_run_timestamp);
  }
  return first_run_timestamp;
#else
  (void)pref_service;  // suppress unused warning

  // Note that CreateSentinelIfNeeded() is called in chrome_browser_main.cc,
  // so this will be a non-blocking read of the cached sentinel value.
  return first_run::GetFirstRunSentinelCreationTime();
#endif  // #defined(OS_ANDROID)
}

}  // namespace huhi_stats
