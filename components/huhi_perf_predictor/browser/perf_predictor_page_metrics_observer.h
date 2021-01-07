/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_PERF_PREDICTOR_BROWSER_PERF_PREDICTOR_PAGE_METRICS_OBSERVER_H_
#define HUHI_COMPONENTS_HUHI_PERF_PREDICTOR_BROWSER_PERF_PREDICTOR_PAGE_METRICS_OBSERVER_H_

#include <cstdint>
#include <string>

#include "components/page_load_metrics/browser/page_load_metrics_observer.h"
#include "services/metrics/public/cpp/ukm_source_id.h"

namespace content {
class NavigationHandle;
}  // namespace content

namespace page_load_metrics {
namespace mojom {
class PageLoadTiming;
}  // namespace mojom
}  // namespace page_load_metrics

namespace huhi_perf_predictor {

class PerfPredictorTabHelper;

// Observer responsible for recording per site performance metrics.
class PerfPredictorPageMetricsObserver
    : public page_load_metrics::PageLoadMetricsObserver {
 public:
  PerfPredictorPageMetricsObserver();
  ~PerfPredictorPageMetricsObserver() override;

  PerfPredictorPageMetricsObserver(const PerfPredictorPageMetricsObserver&) =
      delete;
  PerfPredictorPageMetricsObserver& operator=(
      const PerfPredictorPageMetricsObserver&) = delete;

  void OnFirstContentfulPaintInPage(
      const page_load_metrics::mojom::PageLoadTiming& timing) override;
  void OnFirstMeaningfulPaintInMainFrameDocument(
      const page_load_metrics::mojom::PageLoadTiming& timing) override;
  void OnLoadEventStart(
      const page_load_metrics::mojom::PageLoadTiming& timing) override;

 private:
  ObservePolicy OnCommit(content::NavigationHandle* navigation_handle,
                         ukm::SourceId source_id) override;

  ObservePolicy ShouldObserveMimeType(
      const std::string& mime_type) const override;

  int64_t navigation_id_ = 0;

  // The browser context this navigation is operating in.
  PerfPredictorTabHelper* observer_ = nullptr;
};

}  // namespace huhi_perf_predictor

#endif  // HUHI_COMPONENTS_HUHI_PERF_PREDICTOR_BROWSER_PERF_PREDICTOR_PAGE_METRICS_OBSERVER_H_
