/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#define HUHI_READ_RENDERER_CONTENT_SETTING_RULES_DATA_VIEW       \
  data.ReadAutoplayRules(&out->autoplay_rules) &&                 \
      data.ReadFingerprintingRules(&out->fingerprinting_rules) && \
      data.ReadHuhiShieldsRules(&out->huhi_shields_rules) &&

#include "../../../../../../components/content_settings/core/common/content_settings_mojom_traits.cc"

#undef HUHI_READ_RENDERER_CONTENT_SETTING_RULES_DATA_VIEW
