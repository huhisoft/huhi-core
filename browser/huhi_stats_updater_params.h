/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_HUHI_STATS_UPDATER_PARAMS_H_
#define HUHI_BROWSER_HUHI_STATS_UPDATER_PARAMS_H_

#include <string>

#include "base/macros.h"
#include "base/time/time.h"

class HuhiStatsUpdaterBrowserTest;
class HuhiStatsUpdaterTest;
class PrefService;

namespace huhi {

class HuhiStatsUpdaterParams {
 public:
  explicit HuhiStatsUpdaterParams(PrefService* pref_service);
  HuhiStatsUpdaterParams(PrefService* pref_service,
                          const std::string& ymd,
                          int woy,
                          int month);
  ~HuhiStatsUpdaterParams();

  std::string GetDailyParam() const;
  std::string GetWeeklyParam() const;
  std::string GetMonthlyParam() const;
  std::string GetFirstCheckMadeParam() const;
  std::string GetWeekOfInstallationParam() const;
  std::string GetDateOfInstallationParam() const;
  std::string GetReferralCodeParam() const;

  void SavePrefs();

 private:
  friend class ::HuhiStatsUpdaterBrowserTest;
  friend class ::HuhiStatsUpdaterTest;
  PrefService* pref_service_;
  std::string ymd_;
  int woy_;
  int month_;
  std::string last_check_ymd_;
  int last_check_woy_;
  int last_check_month_;
  bool first_check_made_;
  std::string week_of_installation_;
  base::Time date_of_installation_;
  std::string referral_promo_code_;
  static base::Time g_current_time;
  static bool g_force_first_run;

  void LoadPrefs();

  std::string BooleanToString(bool bool_value) const;

  std::string GetDateAsYMD(const base::Time& time) const;
  std::string GetCurrentDateAsYMD() const;
  std::string GetLastMondayAsYMD() const;
  int GetCurrentMonth() const;
  int GetCurrentISOWeekNumber() const;
  base::Time GetCurrentTimeNow() const;
  bool ShouldForceFirstRun() const;

  static void SetCurrentTimeForTest(const base::Time& current_time);
  static void SetFirstRunForTest(bool first_run);

  DISALLOW_COPY_AND_ASSIGN(HuhiStatsUpdaterParams);
};

}  // namespace huhi

#endif  // HUHI_BROWSER_HUHI_STATS_UPDATER_PARAMS_H_
