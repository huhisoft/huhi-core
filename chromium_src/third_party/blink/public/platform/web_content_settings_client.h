/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_THIRD_PARTY_BLINK_PUBLIC_PLATFORM_WEB_CONTENT_SETTINGS_CLIENT_H_
#define HUHI_CHROMIUM_SRC_THIRD_PARTY_BLINK_PUBLIC_PLATFORM_WEB_CONTENT_SETTINGS_CLIENT_H_

#include "huhi/third_party/blink/renderer/huhi_farbling_constants.h"

#define AllowStorageAccessSync                                           \
  AllowAutoplay(bool default_value) { return default_value; }   \
  virtual bool AllowFingerprinting(bool enabled_per_settings) { \
    return enabled_per_settings;                                \
  }                                                             \
  virtual HuhiFarblingLevel GetHuhiFarblingLevel() {          \
    return HuhiFarblingLevel::OFF;                             \
  }                                                             \
  virtual bool AllowStorageAccessSync


#include "../../../../../../third_party/blink/public/platform/web_content_settings_client.h"

#undef AllowStorageAccessSync

#endif  // HUHI_CHROMIUM_SRC_THIRD_PARTY_BLINK_PUBLIC_PLATFORM_WEB_CONTENT_SETTINGS_CLIENT_H_
