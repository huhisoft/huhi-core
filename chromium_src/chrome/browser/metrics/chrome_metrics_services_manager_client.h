/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * you can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_CHROME_BROWSER_METRICS_CHROME_METRICS_SERVICES_MANAGER_CLIENT_H_
#define HUHI_CHROMIUM_SRC_CHROME_BROWSER_METRICS_CHROME_METRICS_SERVICES_MANAGER_CLIENT_H_

#include "components/metrics_services_manager/metrics_services_manager_client.h"

#define IsMetricsReportingEnabled IsMetricsReportingEnabled_ChromiumImpl(); \
  virtual bool IsMetricsReportingEnabled
#include "../../../../../chrome/browser/metrics/chrome_metrics_services_manager_client.h"
#undef IsMetricsReportingEnabled

#endif  // HUHI_CHROMIUM_SRC_CHROME_BROWSER_METRICS_CHROME_METRICS_SERVICES_MANAGER_CLIENT_H_
