/* Copyright 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_P3A_HUHI_P3A_SCHEDULER_H_
#define HUHI_COMPONENTS_P3A_HUHI_P3A_SCHEDULER_H_

#include "base/callback_forward.h"
#include "components/metrics/metrics_scheduler.h"

namespace huhi {

class HuhiP3AScheduler : public metrics::MetricsScheduler {
 public:
  explicit HuhiP3AScheduler(
      const base::Closure& upload_callback,
      const base::Callback<base::TimeDelta(void)>& get_interval_callback);
  ~HuhiP3AScheduler() override;

  void UploadFinished(bool ok);

 private:
  // Provides us with the interval between successful uploads.
  base::Callback<base::TimeDelta(void)> get_interval_callback_;

  // Initial time to wait between upload retry attempts.
  const base::TimeDelta initial_backoff_interval_;

  // Time to wait for the next upload attempt if the next one fails.
  base::TimeDelta backoff_interval_;

  DISALLOW_COPY_AND_ASSIGN(HuhiP3AScheduler);
};

}  // namespace huhi

#endif  // HUHI_COMPONENTS_P3A_HUHI_P3A_SCHEDULER_H_
