/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <random>

#include "third_party/blink/public/platform/web_content_settings_client.h"
#include "third_party/blink/renderer/core/frame/local_frame.h"
#include "third_party/blink/renderer/core/loader/frame_loader.h"

#define HUHI_NAVIGATOR_USERAGENT                                      \
  if (blink::WebContentSettingsClient* settings =                      \
          huhi::GetContentSettingsClientFor(GetExecutionContext())) { \
    if (!settings->AllowFingerprinting(true)) {                        \
      return huhi::HuhiSessionCache::From(*(GetExecutionContext()))  \
          .FarbledUserAgent(GetFrame()->Loader().UserAgent());         \
    }                                                                  \
  }

#include "../../../../../../../third_party/blink/renderer/core/frame/navigator.cc"

#undef HUHI_NAVIGATOR_USERAGENT
