/* Copyright 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_SHIELDS_COMMON_HUHI_SHIELD_UTILS_H_
#define HUHI_COMPONENTS_HUHI_SHIELDS_COMMON_HUHI_SHIELD_UTILS_H_

#include "components/content_settings/core/common/content_settings.h"

class GURL;

ContentSetting GetHuhiFPContentSettingFromRules(
    const ContentSettingsForOneType& fp_rules,
    const GURL& primary_url);

#endif  // HUHI_COMPONENTS_HUHI_SHIELDS_COMMON_HUHI_SHIELD_UTILS_H_
