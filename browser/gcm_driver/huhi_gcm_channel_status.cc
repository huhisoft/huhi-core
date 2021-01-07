/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/gcm_driver/huhi_gcm_channel_status.h"

#include <memory>

#include "huhi/common/pref_names.h"
#include "chrome/browser/gcm/gcm_profile_service_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "components/gcm_driver/gcm_driver_desktop.h"
#include "components/gcm_driver/gcm_profile_service.h"
#include "components/prefs/pref_service.h"

namespace gcm {

const char kHuhiGCMStatusKey[] = "huhi_gcm_channel_status";

HuhiGCMChannelStatus::HuhiGCMChannelStatus(Profile* profile, bool enabled)
    : profile_(profile), gcm_enabled_(enabled) {}

// static
HuhiGCMChannelStatus* HuhiGCMChannelStatus::GetForProfile(
    Profile* profile) {
  HuhiGCMChannelStatus* status = static_cast<HuhiGCMChannelStatus*>(
      profile->GetUserData(kHuhiGCMStatusKey));

  if (!status) {
    bool enabled = profile->GetPrefs()->GetBoolean(kHuhiGCMChannelStatus);
    // Object cleanup is handled by SupportsUserData
    profile->SetUserData(
        kHuhiGCMStatusKey,
        std::make_unique<HuhiGCMChannelStatus>(profile, enabled));
    status = static_cast<HuhiGCMChannelStatus*>(
        profile->GetUserData(kHuhiGCMStatusKey));
  }
  return status;
}

bool HuhiGCMChannelStatus::IsGCMEnabled() const {
  return gcm_enabled_;
}

void HuhiGCMChannelStatus::UpdateGCMDriverStatus() {
  if (!profile_)
    return;
  gcm::GCMProfileService* gcm_profile_service =
      gcm::GCMProfileServiceFactory::GetForProfile(profile_);
  if (!gcm_profile_service)
    return;
  gcm::GCMDriver* gcm_driver = gcm_profile_service->driver();
  if (!gcm_driver)
    return;
  (static_cast<gcm::HuhiGCMDriverDesktop*>(gcm_driver))
      ->SetEnabled(IsGCMEnabled());
}

}  // namespace gcm
