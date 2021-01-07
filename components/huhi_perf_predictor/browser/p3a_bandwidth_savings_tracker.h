/* Copyright 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_PERF_PREDICTOR_BROWSER_P3A_BANDWIDTH_SAVINGS_TRACKER_H_
#define HUHI_COMPONENTS_HUHI_PERF_PREDICTOR_BROWSER_P3A_BANDWIDTH_SAVINGS_TRACKER_H_

#include <cstdint>
#include <memory>

class PrefRegistrySimple;
class PrefService;

namespace base {
class Clock;
}  // namespace base

namespace huhi_perf_predictor {

class P3ABandwidthSavingsTracker {
 public:
  explicit P3ABandwidthSavingsTracker(PrefService* user_prefs);
  // Constructor with injected clock for testing
  P3ABandwidthSavingsTracker(PrefService* user_prefs,
                             std::unique_ptr<base::Clock> clock);
  ~P3ABandwidthSavingsTracker();
  P3ABandwidthSavingsTracker(const P3ABandwidthSavingsTracker&) = delete;
  P3ABandwidthSavingsTracker& operator=(const P3ABandwidthSavingsTracker&) =
      delete;

  static void RegisterPrefs(PrefRegistrySimple* registry);
  void RecordSavings(uint64_t savings);

 private:
  PrefService* user_prefs_;
  std::unique_ptr<base::Clock> clock_;  // Injected clock for testing
  void StoreSavingsHistogram(uint64_t savings_bytes);
};

}  // namespace huhi_perf_predictor

#endif  // HUHI_COMPONENTS_HUHI_PERF_PREDICTOR_BROWSER_P3A_BANDWIDTH_SAVINGS_TRACKER_H_
