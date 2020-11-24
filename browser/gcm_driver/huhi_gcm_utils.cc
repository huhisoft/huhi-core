/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/gcm_driver/huhi_gcm_utils.h"

#include "base/values.h"
#include "huhi/common/pref_names.h"
#include "chrome/browser/profiles/profile.h"
#include "components/prefs/pref_service.h"
#include "components/pref_registry/pref_registry_syncable.h"

namespace gcm {

// Chromium pref deprecated as of 01/2020.
const char kGCMChannelStatus[] = "gcm.channel_status";

void RegisterGCMProfilePrefs(user_prefs::PrefRegistrySyncable* registry) {
  // Deprecated Chromium pref.
  registry->SetDefaultPrefValue(kGCMChannelStatus, base::Value(false));
  // Current Huhi eqiuvalent of the deprecated pref.
  registry->RegisterBooleanPref(kHuhiGCMChannelStatus, false);
}

void MigrateGCMPrefs(Profile* profile) {
  PrefService* prefs = profile->GetPrefs();
  // The default was false (see above).
  auto* pref = prefs->FindPreference(kGCMChannelStatus);
  if (pref && !pref->IsDefaultValue())
    prefs->SetBoolean(kHuhiGCMChannelStatus, pref->GetValue()->GetBool());
}

}  // namespace gcm
