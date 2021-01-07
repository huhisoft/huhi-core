/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#define HUHI_IS_RENDERER_CONTENT_SETTING \
  content_type == ContentSettingsType::AUTOPLAY ||

#include "../../../../../../components/content_settings/core/common/content_settings.cc"

#undef HUHI_IS_RENDERER_CONTENT_SETTING
