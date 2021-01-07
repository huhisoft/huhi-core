/* Copyright 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/huhi_browser_main_extra_parts.h"

#include "base/metrics/histogram_macros.h"
#include "huhi/browser/huhi_browser_process_impl.h"
#include "huhi/components/huhi_shields/browser/huhi_shields_p3a.h"
#include "huhi/components/p3a/huhi_p3a_service.h"
#include "huhi/components/p3a/buildflags.h"
#include "components/metrics/metrics_pref_names.h"
#include "components/prefs/pref_service.h"
#include "services/network/public/cpp/shared_url_loader_factory.h"
#include "third_party/widevine/cdm/buildflags.h"

#if !defined(OS_ANDROID)
#include "huhi/browser/importer/huhi_importer_p3a.h"
#include "huhi/browser/p3a/p3a_core_metrics.h"
#include "huhi/browser/ui/webui/new_tab_page/huhi_new_tab_message_handler.h"
#include "chrome/browser/first_run/first_run.h"
#endif  // !defined(OS_ANDROID)

#if BUILDFLAG(BUNDLE_WIDEVINE_CDM)
#include "huhi/browser/widevine/huhi_widevine_bundle_manager.h"
#endif

namespace {

// Records default values for some histograms because we want these stats to be
// uploaded anyways. Corresponding components will write new values according
// to their usage scenarios.
//
// For profile specific values, see browser/profiles/profile_util.cc
void RecordInitialP3AValues() {
#if !defined(OS_ANDROID)
  if (first_run::IsChromeFirstRun()) {
    RecordImporterP3A(importer::ImporterType::TYPE_UNKNOWN);
  }

  HuhiNewTabMessageHandler::RecordInitialP3AValues(
      g_browser_process->local_state());
#endif  // !defined(OS_ANDROID)

  huhi_shields::MaybeRecordShieldsUsageP3A(huhi_shields::kNeverClicked,
                                            g_browser_process->local_state());

  // Record crash reporting status stats.
  const bool crash_reports_enabled = g_browser_process->local_state()->
      GetBoolean(metrics::prefs::kMetricsReportingEnabled);
  UMA_HISTOGRAM_BOOLEAN("Huhi.Core.CrashReportsEnabled",
                        crash_reports_enabled);
}

}  // namespace

HuhiBrowserMainExtraParts::HuhiBrowserMainExtraParts() {
}

HuhiBrowserMainExtraParts::~HuhiBrowserMainExtraParts() {
}

void HuhiBrowserMainExtraParts::PostBrowserStart() {
  g_huhi_browser_process->StartHuhiServices();
}

void HuhiBrowserMainExtraParts::PreMainMessageLoopRun() {
#if BUILDFLAG(BUNDLE_WIDEVINE_CDM)
  // Want to check as early as possible because |StartupCheck()| has some
  // fixup handling for abnormal status and run it on UI thread.
  // However, HuhiBrowserProcessImpl that the owner of bundle manager is
  // created before browser thread creation.
  // So, call it after browser threads are created.
  g_huhi_browser_process->huhi_widevine_bundle_manager()->StartupCheck();
#endif
  // Disabled on mobile platforms, see for instance issues/6176
#if BUILDFLAG(HUHI_P3A_ENABLED)
  // TODO(iefremov): Maybe find a better place for this initialization.
  g_huhi_browser_process->huhi_p3a_service()->Init(
      g_browser_process->shared_url_loader_factory());
#endif  // BUILDFLAG(HUHI_P3A_ENABLED)

  RecordInitialP3AValues();

  // The code below is not supported on android.
#if !defined(OS_ANDROID)
  huhi::HuhiWindowTracker::CreateInstance(g_browser_process->local_state());
  huhi::HuhiUptimeTracker::CreateInstance(g_browser_process->local_state());
#endif  // !defined(OS_ANDROID)
}
