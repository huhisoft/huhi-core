/* Copyright 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/p3a/p3a_core_metrics.h"

#include <utility>

#include "base/metrics/histogram_macros.h"
#include "base/time/time.h"
#include "huhi/browser/profiles/profile_util.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_list.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/pref_service.h"

namespace huhi {

namespace {

HuhiWindowTracker* g_huhi_windows_tracker_instance = nullptr;

constexpr char kLastTimeIncognitoUsed[] =
    "core_p3a_metrics.incognito_used_timestamp";
constexpr char kTorUsed[] = "core_p3a_metrics.tor_used";

constexpr size_t kWindowUsageP3AIntervalMinutes = 10;

// Note: append-only enumeration! Never remove any existing values, as this enum
// is used to bucket a UMA histogram, and removing values breaks that.
// Each subsequent "bucket" doesn't include previous bucket (i.e. if the window
// was used 5 days ago, the proper bucket is |kUsedInLastWeek|, not
// |kUsedInLast28Days|.
enum class WindowUsageStats {
  kUsedIn24h,
  kUsedInLastWeek,
  kUsedInLast28Days,
  kEverUsed,
  kNeverUsed,
  kSize,
};

const char* GetPrefNameForProfile(Profile* profile) {
  if (profile->IsIncognitoProfile()) {
    return kLastTimeIncognitoUsed;
  }
  return nullptr;
}

HuhiUptimeTracker* g_huhi_uptime_tracker_instance = nullptr;

constexpr size_t kUsageTimeQueryIntervalMinutes = 1;
constexpr char kDailyUptimesListPrefName[] = "daily_uptimes";

}  // namespace

HuhiUptimeTracker::HuhiUptimeTracker(PrefService* local_state)
    : state_(local_state, kDailyUptimesListPrefName) {
  timer_.Start(
      FROM_HERE, base::TimeDelta::FromMinutes(kUsageTimeQueryIntervalMinutes),
      base::Bind(&HuhiUptimeTracker::RecordUsage, base::Unretained(this)));
}

void HuhiUptimeTracker::RecordUsage() {
  const base::TimeDelta new_total = usage_clock_.GetTotalUsageTime();
  const base::TimeDelta interval = new_total - current_total_usage_;
  if (interval > base::TimeDelta()) {
    state_.AddDelta(interval.InSeconds());
    current_total_usage_ = new_total;

    RecordP3A();
  }
}

void HuhiUptimeTracker::RecordP3A() {
  int answer = 0;
  if (state_.IsOneWeekPassed()) {
    uint64_t total = state_.GetWeeklySum();
    const int minutes = base::TimeDelta::FromSeconds(total).InMinutes();
    DCHECK_GE(minutes, 0);
    if (0 <= minutes && minutes < 30) {
      answer = 1;
    } else if (30 <= minutes && minutes < 5 * 60) {
      answer = 2;
    } else {
      answer = 3;
    }
  }
  UMA_HISTOGRAM_EXACT_LINEAR("Huhi.Uptime.BrowserOpenMinutes", answer, 3);
}

HuhiUptimeTracker::~HuhiUptimeTracker() = default;

void HuhiUptimeTracker::CreateInstance(PrefService* local_state) {
  g_huhi_uptime_tracker_instance = new HuhiUptimeTracker(local_state);
}

void HuhiUptimeTracker::RegisterPrefs(PrefRegistrySimple* registry) {
  registry->RegisterListPref(kDailyUptimesListPrefName);
}

HuhiWindowTracker::HuhiWindowTracker(PrefService* local_state)
    : local_state_(local_state) {
  if (!local_state) {
    // Can happen in tests.
    return;
  }
  BrowserList::AddObserver(this);
  timer_.Start(FROM_HERE,
               base::TimeDelta::FromMinutes(kWindowUsageP3AIntervalMinutes),
               base::Bind(&HuhiWindowTracker::UpdateP3AValues,
                          base::Unretained(this)));
  UpdateP3AValues();
}

HuhiWindowTracker::~HuhiWindowTracker() {
  BrowserList::RemoveObserver(this);
}

void HuhiWindowTracker::CreateInstance(PrefService* local_state) {
  g_huhi_windows_tracker_instance = new HuhiWindowTracker(local_state);
}

void HuhiWindowTracker::RegisterPrefs(PrefRegistrySimple* registry) {
  registry->RegisterTimePref(kLastTimeIncognitoUsed, {});
  registry->RegisterBooleanPref(kTorUsed, false);
}

void HuhiWindowTracker::OnBrowserAdded(Browser* browser) {
  if (huhi::IsTorProfile(browser->profile())) {
    local_state_->SetBoolean(kTorUsed, true);
    return;
  }
  const char* pref = GetPrefNameForProfile(browser->profile());
  if (pref) {
    local_state_->SetTime(pref, base::Time::Now());
  }
}

void HuhiWindowTracker::OnBrowserSetLastActive(Browser* browser) {
  const char* pref = GetPrefNameForProfile(browser->profile());
  if (pref) {
    local_state_->SetTime(pref, base::Time::Now());
  }
}

void HuhiWindowTracker::UpdateP3AValues() const {
  // Deal with the incognito window.
  WindowUsageStats bucket;
  const base::Time time = local_state_->GetTime(kLastTimeIncognitoUsed);
  const base::Time now = base::Time::Now();
  if (time.is_null()) {
    bucket = WindowUsageStats::kNeverUsed;
  } else if (now - time < base::TimeDelta::FromHours(24)) {
    bucket = WindowUsageStats::kUsedIn24h;
  } else if (now - time < base::TimeDelta::FromDays(7)) {
    bucket = WindowUsageStats::kUsedInLastWeek;
  } else if (now - time < base::TimeDelta::FromDays(28)) {
    bucket = WindowUsageStats::kUsedInLast28Days;
  } else {
    bucket = WindowUsageStats::kEverUsed;
  }

  UMA_HISTOGRAM_ENUMERATION("Huhi.Core.LastTimeIncognitoUsed", bucket,
                            WindowUsageStats::kSize);

  // Record if the TOR window was ever used.
  // 0 -> Yes; 1 -> No.
  const int tor_used = !local_state_->GetBoolean(kTorUsed);
  UMA_HISTOGRAM_EXACT_LINEAR("Huhi.Core.TorEverUsed", tor_used, 1);
}

}  // namespace huhi
