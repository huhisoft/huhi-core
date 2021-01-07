/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "../../../../chrome/browser/flag_descriptions.cc"

namespace flag_descriptions {
const char kUseDevUpdaterUrlName[] =
    "Use dev updater url";
const char kUseDevUpdaterUrlDescription[] =
    "Use the dev url for the component updater. "
    "This is for internal testing only.";
const char kHuhiNTPBrandedWallpaperName[] =
    "New Tab Page Branded Wallpapers";
const char kHuhiNTPBrandedWallpaperDescription[] =
    "Allow New Tab Page Branded Wallpapers and user preference.";
const char kHuhiNTPBrandedWallpaperDemoName[] =
    "New Tab Page Demo Branded Wallpaper";
const char kHuhiNTPBrandedWallpaperDemoDescription[] =
    "Force dummy data for the Branded Wallpaper New Tab Page Experience. "
    "View rate and user opt-in conditionals will still be followed to decide "
    "when to display the Branded Wallpaper.";
const char kHuhiAdblockCosmeticFilteringName[] = "Enable cosmetic filtering";
const char kHuhiAdblockCosmeticFilteringDescription[] =
    "Enable support for cosmetic filtering";
const char kHuhiSpeedreaderName[] = "Enable SpeedReader";
const char kHuhiSpeedreaderDescription[] =
    "Enables faster loading of simplified article-style web pages.";
const char kHuhiSyncName[] = "Enable Huhi Sync v2";
const char kHuhiSyncDescription[] =
    "Huhi Sync v2 integrates with chromium sync engine with Huhi specific "
    "authentication flow and enforce client side encryption";
const char kHuhiIpfsName[] = "Enable IPFS";
const char kHuhiIpfsDescription[] =
    "Enable native support of IPFS.";
const char kHuhiSuperReferralName[] = "Enable Huhi Super Referral";
const char kHuhiSuperReferralDescription[] =
    "Use custom theme for Huhi Super Referral";
const char kHuhiEphemeralStorageName[] = "Enable Ephemeral Storage";
const char kHuhiEphemeralStorageDescription[] =
    "Use ephemeral storage for third-party frames";
}  // namespace flag_descriptions
