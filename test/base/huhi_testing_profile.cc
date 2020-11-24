/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/test/base/huhi_testing_profile.h"

#include "huhi/browser/profiles/profile_util.h"
#include "huhi/common/pref_names.h"
#include "components/gcm_driver/gcm_buildflags.h"
#include "components/prefs/pref_service.h"

HuhiTestingProfile::HuhiTestingProfile(const base::FilePath& path,
                                         Delegate* delegate)
    : TestingProfile(path, delegate) {
  if (huhi::IsSessionProfilePath(path)) {
    huhi::CreateParentProfileData(this);
  }
}

HuhiTestingProfile::HuhiTestingProfile()
    : TestingProfile() {
#if !BUILDFLAG(USE_GCM_FROM_PLATFORM)
  GetPrefs()->SetBoolean(kHuhiGCMChannelStatus, true);
#endif
}
