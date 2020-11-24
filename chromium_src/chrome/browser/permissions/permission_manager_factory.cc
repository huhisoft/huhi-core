/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/browser/permissions/permission_manager_factory.h"

#include <memory>

#include "huhi/browser/autoplay/autoplay_permission_context.h"
#include "huhi/browser/geolocation/huhi_geolocation_permission_context_delegate.h"
#include "components/content_settings/core/common/content_settings_types.h"
#include "components/permissions/permission_manager.h"

namespace {

// Forward declaration.
permissions::PermissionManager::PermissionContextMap CreatePermissionContexts(
    Profile* profile);

permissions::PermissionManager::PermissionContextMap
HuhiCreatePermissionContexts(Profile* profile) {
  permissions::PermissionManager::PermissionContextMap permission_contexts =
      CreatePermissionContexts(profile);
  permission_contexts[ContentSettingsType::AUTOPLAY] =
      std::make_unique<AutoplayPermissionContext>(profile);
  return permission_contexts;
}

}  // namespace

#define BuildServiceInstanceFor BuildServiceInstanceFor_ChromiumImpl
#define GeolocationPermissionContextDelegate \
  HuhiGeolocationPermissionContextDelegate
#include "../../../../../chrome/browser/permissions/permission_manager_factory.cc"
#undef GeolocationPermissionContextDelegate
#undef BuildServiceInstanceFor

KeyedService* PermissionManagerFactory::BuildServiceInstanceFor(
    content::BrowserContext* context) const {
  Profile* profile = Profile::FromBrowserContext(context);
  return new permissions::PermissionManager(
      profile, HuhiCreatePermissionContexts(profile));
}
