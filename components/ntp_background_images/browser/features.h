/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_NTP_BACKGROUND_IMAGES_BROWSER_FEATURES_H_
#define HUHI_COMPONENTS_NTP_BACKGROUND_IMAGES_BROWSER_FEATURES_H_

namespace base {
struct Feature;
}  // namespace base

namespace ntp_background_images {
namespace features {
extern const base::Feature kHuhiNTPBrandedWallpaper;
extern const base::Feature kHuhiNTPBrandedWallpaperDemo;
extern const base::Feature kHuhiNTPSuperReferralWallpaper;
}  // namespace features
}  // namespace ntp_background_images

#endif  // HUHI_COMPONENTS_NTP_BACKGROUND_IMAGES_BROWSER_FEATURES_H_
