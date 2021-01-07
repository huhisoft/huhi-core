/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ads/pref_names.h"

namespace ads {

namespace prefs {

// Stores whether Huhi ads is enabled or disabled
const char kEnabled[] = "huhi.huhi_ads.enabled";

// Stores whether Huhi ads should allow conversion tracking
const char kShouldAllowConversionTracking[] =
    "huhi.huhi_ads.should_allow_ad_conversion_tracking";

// Stores the maximum amount of ads per hour
const char kAdsPerHour[] = "huhi.huhi_ads.ads_per_hour";

// Stores the maximum amount of ads per day
const char kAdsPerDay[] = "huhi.huhi_ads.ads_per_day";

// Stores the idle threshold before checking if an ad can be served
const char kIdleThreshold[] = "huhi.huhi_ads.idle_threshold";

// Stores whether Huhi ads should allow subdivision ad targeting
const char kShouldAllowAdsSubdivisionTargeting[] =
    "huhi.huhi_ads.should_allow_ads_subdivision_targeting";

// Stores the selected ads subdivision targeting code
const char kAdsSubdivisionTargetingCode[] =
    "huhi.huhi_ads.ads_subdivision_targeting_code";

// Stores the automatically detected ads subdivision targeting code
const char kAutoDetectedAdsSubdivisionTargetingCode[] =
    "huhi.huhi_ads.automatically_detected_ads_subdivision_targeting_code";

}  // namespace prefs

}  // namespace ads
