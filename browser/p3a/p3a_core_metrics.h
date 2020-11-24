/* Copyright 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_P3A_P3A_CORE_METRICS_H_
#define HUHI_BROWSER_P3A_P3A_CORE_METRICS_H_

#include <list>

#include "base/timer/timer.h"
#include "huhi/components/weekly_storage/weekly_storage.h"
#include "chrome/browser/resource_coordinator/usage_clock.h"
#include "chrome/browser/ui/browser_list_observer.h"

class PrefService;
class PrefRegistrySimple;

namespace huhi {

class HuhiUptimeTracker {
 public:
  explicit HuhiUptimeTracker(PrefService* local_state);
  ~HuhiUptimeTracker();

  static void CreateInstance(PrefService* local_state);

  static void RegisterPrefs(PrefRegistrySimple* registry);

 private:
  void RecordUsage();
  void RecordP3A();

  resource_coordinator::UsageClock usage_clock_;
  base::RepeatingTimer timer_;
  base::TimeDelta current_total_usage_;
  WeeklyStorage state_;

  DISALLOW_COPY_AND_ASSIGN(HuhiUptimeTracker);
};

// Periodically records P3A stats (extracted from Local State) regarding the
// time when incognito windows were used.
// Used as a leaking singletone.
class HuhiWindowTracker : public BrowserListObserver {
 public:
  explicit HuhiWindowTracker(PrefService* local_state);
  ~HuhiWindowTracker() override;

  static void CreateInstance(PrefService* local_state);

  static void RegisterPrefs(PrefRegistrySimple* registry);

 private:
  // BrowserListObserver:
  void OnBrowserAdded(Browser* browser) override;
  void OnBrowserSetLastActive(Browser* browser) override;

  void UpdateP3AValues() const;

  base::RepeatingTimer timer_;
  PrefService* local_state_;
  DISALLOW_COPY_AND_ASSIGN(HuhiWindowTracker);
};

}  // namespace huhi

#endif  // HUHI_BROWSER_P3A_P3A_CORE_METRICS_H_
