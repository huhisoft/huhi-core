/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_GEOLOCATION_HUHI_GEOLOCATION_PERMISSION_CONTEXT_DELEGATE_H_
#define HUHI_BROWSER_GEOLOCATION_HUHI_GEOLOCATION_PERMISSION_CONTEXT_DELEGATE_H_

#include "chrome/browser/geolocation/geolocation_permission_context_delegate.h"

class Profile;

class HuhiGeolocationPermissionContextDelegate
    : public GeolocationPermissionContextDelegate {
 public:
  explicit HuhiGeolocationPermissionContextDelegate(
      content::BrowserContext* browser_context);
  ~HuhiGeolocationPermissionContextDelegate() override;

  bool DecidePermission(
      content::WebContents* web_contents,
      const permissions::PermissionRequestID& id,
      const GURL& requesting_origin,
      bool user_gesture,
      permissions::BrowserPermissionCallback* callback,
      permissions::GeolocationPermissionContext* context) override;

 private:
  Profile* profile_;
  DISALLOW_COPY_AND_ASSIGN(HuhiGeolocationPermissionContextDelegate);
};

#endif  // HUHI_BROWSER_GEOLOCATION_HUHI_GEOLOCATION_PERMISSION_CONTEXT_DELEGATE_H_
