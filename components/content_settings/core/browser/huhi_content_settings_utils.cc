/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/components/content_settings/core/browser/huhi_content_settings_utils.h"

#include <algorithm>

#include "base/optional.h"
#include "huhi/components/huhi_shields/common/huhi_shield_constants.h"
#include "url/gurl.h"

namespace {

const std::vector<std::string> kShieldsResourceIDs {
    huhi_shields::kAds,
    huhi_shields::kTrackers,
    huhi_shields::kCosmeticFiltering,
    huhi_shields::kHTTPUpgradableResources,
    huhi_shields::kJavaScript,
    huhi_shields::kFingerprintingV2,
    huhi_shields::kHuhiShields,
    huhi_shields::kReferrers,
    huhi_shields::kCookies };

bool CanPatternBeConvertedToWildcardSchemeAndPort(
    const ContentSettingsPattern& pattern) {
  // 1. Wildcard is already in the desired state.
  // 2. Our firstParty placeholder shouldn't be converted.
  // 3. Patterns that have file:// scheme.
  // 4. We only want to convert patterns that have a specific host, so something
  // like "http://*:80/*" should be left alone.
  if (pattern == ContentSettingsPattern::Wildcard() ||
      pattern == ContentSettingsPattern::FromString("https://firstParty/*") ||
      pattern.GetScheme() == ContentSettingsPattern::SCHEME_FILE ||
      pattern.MatchesAllHosts() || pattern.GetHost().empty())
    return false;
  // Check for the case when the scheme is wildcard, but the port isn't.
  if (pattern.GetScheme() == ContentSettingsPattern::SCHEME_WILDCARD) {
    GURL check_for_port_url("http://" + pattern.ToString());
    return check_for_port_url.has_port();
  }
  GURL url(pattern.ToString());
  if (!url.is_valid() || url.is_empty() || !url.has_host())
    return false;
  if (url.has_scheme())
    return !ContentSettingsPattern::IsNonWildcardDomainNonPortScheme(
        url.scheme_piece());
  return url.has_port();
}

}  // namespace

namespace content_settings {

const std::vector<std::string>& GetShieldsResourceIDs() {
  return kShieldsResourceIDs;
}

bool IsShieldsResourceID(
    const content_settings::ResourceIdentifier& resource_identifier) {
  return std::find(kShieldsResourceIDs.begin(),
                   kShieldsResourceIDs.end(),
                   resource_identifier) != kShieldsResourceIDs.end();
}

base::Optional<ContentSettingsPattern> ConvertPatternToWildcardSchemeAndPort(
    const ContentSettingsPattern& pattern) {
  if (!CanPatternBeConvertedToWildcardSchemeAndPort(pattern))
    return base::nullopt;
  DCHECK(!pattern.GetHost().empty());
  base::Optional<ContentSettingsPattern> new_pattern =
      ContentSettingsPattern::FromString("*://" + pattern.GetHost() + "/*");
  return new_pattern;
}

}  // namespace content_settings
