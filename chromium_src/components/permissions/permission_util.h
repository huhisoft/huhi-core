/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_COMPONENTS_PERMISSIONS_PERMISSION_UTIL_H_
#define HUHI_CHROMIUM_SRC_COMPONENTS_PERMISSIONS_PERMISSION_UTIL_H_

#define GetPermissionString                              \
  GetPermissionString_ChromiumImpl(ContentSettingsType); \
  static std::string GetPermissionString

#define GetRequestType                                         \
  GetRequestType_ChromiumImpl(ContentSettingsType permission); \
  static PermissionRequestType GetRequestType

#define GetPermissionType                                       \
  GetPermissionType_ChromiumImpl(ContentSettingsType type,      \
                                 content::PermissionType* out); \
  static bool GetPermissionType

#define IsPermission                                   \
  IsPermission_ChromiumImpl(ContentSettingsType type); \
  static bool IsPermission

#include "../../../../components/permissions/permission_util.h"
#undef IsPermission
#undef GetPermissionType
#undef GetRequestType
#undef GetPermissionString

#endif  // HUHI_CHROMIUM_SRC_COMPONENTS_PERMISSIONS_PERMISSION_UTIL_H_
