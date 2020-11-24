/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_BROWSING_DATA_COUNTERS_HUHI_SITE_SETTINGS_COUNTER_H_
#define HUHI_BROWSER_BROWSING_DATA_COUNTERS_HUHI_SITE_SETTINGS_COUNTER_H_

#include "chrome/browser/browsing_data/counters/site_settings_counter.h"

// This class adds shieldss settings count
class HuhiSiteSettingsCounter : public SiteSettingsCounter {
 public:
  HuhiSiteSettingsCounter(HostContentSettingsMap* map,
                           content::HostZoomMap* zoom_map,
                           ProtocolHandlerRegistry* handler_registry,
                           PrefService* pref_service);
  ~HuhiSiteSettingsCounter() override;
  HuhiSiteSettingsCounter(const HuhiSiteSettingsCounter&) = delete;
  HuhiSiteSettingsCounter& operator=(const HuhiSiteSettingsCounter&) = delete;

 private:
  // SiteSettingsCounter overrides:
  void ReportResult(ResultInt value) override;

  int CountShieldsSettings();

  scoped_refptr<HostContentSettingsMap> map_;
};

#endif  // HUHI_BROWSER_BROWSING_DATA_COUNTERS_HUHI_SITE_SETTINGS_COUNTER_H_
