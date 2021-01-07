/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "base/feature_list.h"
#include "huhi/components/huhi_shields/common/huhi_shield_constants.h"

#define HUHI_GET_RENDER_CONTENT_SETTING_RULES                                \
  map->GetSettingsForOneType(ContentSettingsType::AUTOPLAY,                   \
                             ResourceIdentifier(), &(rules->autoplay_rules)); \
  map->GetSettingsForOneType(ContentSettingsType::PLUGINS,                    \
                             huhi_shields::kFingerprintingV2,                \
                             &(rules->fingerprinting_rules));                 \
  map->GetSettingsForOneType(ContentSettingsType::PLUGINS,                    \
                             huhi_shields::kHuhiShields,                    \
                             &(rules->huhi_shields_rules));

#include "../../../../../../components/content_settings/core/browser/content_settings_utils.cc"

#undef HUHI_HUHI_GET_RENDER_CONTENT_SETTING_RULES
