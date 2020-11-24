/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/components/ntp_background_images/browser/features.h"

#include "base/feature_list.h"
#include "build/build_config.h"
#include "ui/base/ui_base_features.h"

namespace ntp_background_images {
namespace features {

const base::Feature kHuhiNTPBrandedWallpaper{
    "HuhiNTPBrandedWallpaperName",
    base::FEATURE_ENABLED_BY_DEFAULT};
const base::Feature kHuhiNTPBrandedWallpaperDemo{
    "HuhiNTPBrandedWallpaperDemoName",
    base::FEATURE_DISABLED_BY_DEFAULT};
const base::Feature kHuhiNTPSuperReferralWallpaper{
    "HuhiNTPSuperReferralWallpaperName",
#if defined(OS_LINUX)
    // Linux doesn't support referral install yet.
    base::FEATURE_DISABLED_BY_DEFAULT};
#else
    base::FEATURE_ENABLED_BY_DEFAULT};
#endif

}  // namespace features
}  // namespace ntp_background_images