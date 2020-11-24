/* Copyright 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#define InitializePageLoadMetricsForWebContents \
  InitializePageLoadMetricsForWebContents_Chromium
#include "../../../../../chrome/browser/page_load_metrics/page_load_metrics_initialize.cc"
#undef InitializePageLoadMetricsForWebContents

#include "huhi/components/huhi_perf_predictor/browser/buildflags.h"

#if BUILDFLAG(ENABLE_HUHI_PERF_PREDICTOR)
#include "huhi/components/huhi_perf_predictor/browser/perf_predictor_page_metrics_observer.h"
#endif

namespace chrome {

namespace {

class HuhiPageLoadMetricsEmbedder : public chrome::PageLoadMetricsEmbedder {
 public:
  explicit HuhiPageLoadMetricsEmbedder(content::WebContents* web_contents);
  ~HuhiPageLoadMetricsEmbedder() override;

 protected:
  // page_load_metrics::PageLoadMetricsEmbedderBase:
  void RegisterEmbedderObservers(
      ::page_load_metrics::PageLoadTracker* tracker) override;

 private:
  DISALLOW_COPY_AND_ASSIGN(HuhiPageLoadMetricsEmbedder);
};

HuhiPageLoadMetricsEmbedder::HuhiPageLoadMetricsEmbedder(
    content::WebContents* web_contents)
    : chrome::PageLoadMetricsEmbedder(web_contents) {}

HuhiPageLoadMetricsEmbedder::~HuhiPageLoadMetricsEmbedder() = default;

void HuhiPageLoadMetricsEmbedder::RegisterEmbedderObservers(
    page_load_metrics::PageLoadTracker* tracker) {
  PageLoadMetricsEmbedder::RegisterEmbedderObservers(tracker);

#if BUILDFLAG(ENABLE_HUHI_PERF_PREDICTOR)
  tracker->AddObserver(
      std::make_unique<
          huhi_perf_predictor::PerfPredictorPageMetricsObserver>());
#endif
}

}  // namespace

void InitializePageLoadMetricsForWebContents(
    content::WebContents* web_contents) {
  // TODO(bug https://github.com/huhisoft/huhi-browser/issues/7784)
  // change
  // android_webview/browser/page_load_metrics/page_load_metrics_initialize.cc
  // as well to register Page Load Metrics Observers
  page_load_metrics::MetricsWebContentsObserver::CreateForWebContents(
      web_contents,
      std::make_unique<HuhiPageLoadMetricsEmbedder>(web_contents));
}

}  // namespace chrome
