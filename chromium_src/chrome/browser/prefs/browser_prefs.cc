/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/huhi_local_state_prefs.h"
#include "huhi/browser/huhi_profile_prefs.h"
#include "huhi/browser/search/ntp_utils.h"
#include "huhi/browser/themes/huhi_dark_mode_utils.h"
#include "huhi/components/huhi_sync/huhi_sync_prefs.h"
#include "chrome/browser/profiles/profile.h"
#include "components/gcm_driver/gcm_buildflags.h"
#include "third_party/widevine/cdm/buildflags.h"

#if BUILDFLAG(ENABLE_WIDEVINE)
#include "huhi/browser/widevine/widevine_utils.h"
#endif

#define MigrateObsoleteProfilePrefs MigrateObsoleteProfilePrefs_ChromiumImpl
#include "../../../../../chrome/browser/prefs/browser_prefs.cc"
#undef MigrateObsoleteProfilePrefs

#if !BUILDFLAG(USE_GCM_FROM_PLATFORM)
#include "huhi/browser/gcm_driver/huhi_gcm_utils.h"
#endif

// This method should be periodically pruned of year+ old migrations.
void MigrateObsoleteProfilePrefs(Profile* profile) {
#if !BUILDFLAG(USE_GCM_FROM_PLATFORM)
  // Added 02/2020.
  // Must be called before ChromiumImpl because it's migrating a Chromium pref
  // to Huhi pref.
  gcm::MigrateGCMPrefs(profile);
#endif

  MigrateObsoleteProfilePrefs_ChromiumImpl(profile);

#if BUILDFLAG(ENABLE_WIDEVINE)
  // Added 11/2019.
  MigrateWidevinePrefs(profile);
#endif
  huhi_sync::MigrateHuhiSyncPrefs(profile->GetPrefs());

  // Added 12/2019.
  dark_mode::MigrateHuhiDarkModePrefs(profile);

  // Added 9/2020
#if !defined(OS_ANDROID)
  new_tab_page::MigrateNewTabPagePrefs(profile);
#endif
}
