/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#define HUHI_PERMISSION_MANAGER_PERMISSION_TYPE_TO_CONTENT_SETTING_SAFE \
  case PermissionType::AUTOPLAY:                                         \
    return ContentSettingsType::AUTOPLAY;

#include "../../../../components/permissions/permission_manager.cc"
#undef HUHI_PERMISSION_MANAGER_PERMISSION_TYPE_TO_CONTENT_SETTING_SAFE
