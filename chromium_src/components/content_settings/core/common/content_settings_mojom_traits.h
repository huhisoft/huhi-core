/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_COMPONENTS_CONTENT_SETTINGS_CORE_COMMON_CONTENT_SETTINGS_MOJOM_TRAITS_H_
#define HUHI_CHROMIUM_SRC_COMPONENTS_CONTENT_SETTINGS_CORE_COMMON_CONTENT_SETTINGS_MOJOM_TRAITS_H_

#define HUHI_CONTENT_SETTINGS_MOJOM_TRAITS_H                                  \
  static const std::vector<ContentSettingPatternSource>& autoplay_rules(       \
      const RendererContentSettingRules& r) {                                  \
    return r.autoplay_rules;                                                   \
  }                                                                            \
  static const std::vector<ContentSettingPatternSource>& fingerprinting_rules( \
      const RendererContentSettingRules& r) {                                  \
    return r.fingerprinting_rules;                                             \
  }                                                                            \
  static const std::vector<ContentSettingPatternSource>& huhi_shields_rules(  \
      const RendererContentSettingRules& r) {                                  \
    return r.huhi_shields_rules;                                              \
  }

#include "../../../../../../components/content_settings/core/common/content_settings_mojom_traits.h"

#undef HUHI_CONTENT_SETTINGS_MOJOM_TRAITS_H

#endif  // HUHI_CHROMIUM_SRC_COMPONENTS_CONTENT_SETTINGS_CORE_COMMON_CONTENT_SETTINGS_MOJOM_TRAITS_H_
