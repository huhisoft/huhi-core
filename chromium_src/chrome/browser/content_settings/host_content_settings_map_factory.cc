/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/profiles/profile_util.h"

#define HUHI_BUILD_SERVICE_INSTANCE_FOR huhi::IsSessionProfile(profile) ||
#include "../../../../../chrome/browser/content_settings/host_content_settings_map_factory.cc"
#undef  HUHI_BUILD_SERVICE_INSTANCE_FOR
