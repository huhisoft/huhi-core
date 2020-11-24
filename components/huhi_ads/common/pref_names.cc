/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/components/huhi_ads/common/pref_names.h"

namespace huhi_ads {

namespace prefs {

// Stores whether Huhi ads is enabled or disabled
const char kEnabled[] = "huhi.huhi_ads.enabled";

// Stores whether Huhi ads should allow ad conversion tracking
const char kShouldAllowAdConversionTracking[] =
    "huhi.huhi_ads.should_allow_ad_conversion_tracking";

// Stores whether ads were disabled at least once
const char kAdsWereDisabled[] = "huhi.huhi_ads.were_disabled";

// Indicates whether we have any initial state of the ads status metric, besides
// "No Wallet".
const char kHasAdsP3AState[] = "huhi.huhi_ads.has_p3a_state";

// Stores the maximum amount of ads per hour
const char kAdsPerHour[] = "huhi.huhi_ads.ads_per_hour";

// Stores whether Huhi ads should allow subdivision ad targeting
const char kShouldAllowAdsSubdivisionTargeting[] =
    "huhi.huhi_ads.should_allow_ads_subdivision_targeting";

// Stores the selected ads subdivision targeting code
const char kAdsSubdivisionTargetingCode[] =
    "huhi.huhi_ads.ads_subdivision_targeting_code";

// Stores the automatically detected ads subdivision targeting code
const char kAutomaticallyDetectedAdsSubdivisionTargetingCode[] =
    "huhi.huhi_ads.automatically_detected_ads_subdivision_targeting_code";

// Stores the maximum amount of ads per day
const char kAdsPerDay[] = "huhi.huhi_ads.ads_per_day";

// Stores the idle threshold before checking if an ad can be served
const char kIdleThreshold[] = "huhi.huhi_ads.idle_threshold";

// Stores whether onboarding should be shown
const char kShouldShowOnboarding[] =
    "huhi.huhi_ads.should_show_first_launch_notification";

// Stores the timestamp of when onboarding was shown
const char kOnboardingTimestamp[] =
    "huhi.huhi_ads.launch_notification_timestamp";

// Stores whether we should show the My First Ad notification
const char kShouldShowMyFirstAdNotification[] =
    "huhi.huhi_ads.should_show_my_first_ad_notification";

// Stores the supported country codes current schema version number
const char kSupportedCountryCodesLastSchemaVersion[] =
    "huhi.huhi_ads.supported_regions_last_schema_version_number";
const char kSupportedCountryCodesSchemaVersion[] =
    "huhi.huhi_ads.supported_regions_schema_version_number";

const int kSupportedCountryCodesSchemaVersionNumber = 9;

// Stores the preferences version number
const char kVersion[] = "huhi.huhi_ads.prefs.version";

const int kCurrentVersionNumber = 7;

const char kAdViewConfirmationCountPrefName[] =
    "huhi.weekly_storage.p2a_ad_view_confirmation_count";

}  // namespace prefs

}  // namespace huhi_ads
