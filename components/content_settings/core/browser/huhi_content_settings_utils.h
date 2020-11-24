/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_CONTENT_SETTINGS_CORE_BROWSER_HUHI_CONTENT_SETTINGS_UTILS_H_
#define HUHI_COMPONENTS_CONTENT_SETTINGS_CORE_BROWSER_HUHI_CONTENT_SETTINGS_UTILS_H_

#include <string>
#include <vector>

#include "components/content_settings/core/common/content_settings.h"

namespace content_settings {

const std::vector<std::string>& GetShieldsResourceIDs();

bool IsShieldsResourceID(const ResourceIdentifier& resource_identifier);

base::Optional<ContentSettingsPattern> ConvertPatternToWildcardSchemeAndPort(
    const ContentSettingsPattern& pattern);

}  // namespace content_settings

#endif  // HUHI_COMPONENTS_CONTENT_SETTINGS_CORE_BROWSER_HUHI_CONTENT_SETTINGS_UTILS_H_
