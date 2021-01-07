/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/geolocation/huhi_geolocation_permission_context_delegate.h"

#include <utility>

#include "huhi/browser/profiles/profile_util.h"
#include "chrome/browser/profiles/profile.h"
#include "components/content_settings/core/common/content_settings.h"
#include "components/permissions/permission_request_id.h"
#include "content/public/browser/web_contents.h"
#include "url/gurl.h"

HuhiGeolocationPermissionContextDelegate::
    HuhiGeolocationPermissionContextDelegate(
        content::BrowserContext* browser_context)
    : GeolocationPermissionContextDelegate(browser_context),
      profile_(Profile::FromBrowserContext(browser_context)) {}

HuhiGeolocationPermissionContextDelegate::
    ~HuhiGeolocationPermissionContextDelegate() {}

bool HuhiGeolocationPermissionContextDelegate::DecidePermission(
    content::WebContents* web_contents,
    const permissions::PermissionRequestID& id,
    const GURL& requesting_origin,
    bool user_gesture,
    permissions::BrowserPermissionCallback* callback,
    permissions::GeolocationPermissionContext* context) {
  if (huhi::IsTorProfile(profile_)) {
    std::move(*callback).Run(ContentSetting::CONTENT_SETTING_BLOCK);
    return true;
  }

  return GeolocationPermissionContextDelegate::DecidePermission(
      web_contents, id, requesting_origin, user_gesture, callback, context);
}
