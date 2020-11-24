/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/renderer/huhi_content_renderer_client.h"
#include "third_party/blink/public/platform/web_runtime_features.h"

HuhiContentRendererClient::HuhiContentRendererClient()
    : ChromeContentRendererClient() {}

void HuhiContentRendererClient::
SetRuntimeFeaturesDefaultsBeforeBlinkInitialization() {
  ChromeContentRendererClient::
      SetRuntimeFeaturesDefaultsBeforeBlinkInitialization();

  blink::WebRuntimeFeatures::EnableSharedArrayBuffer(false);
}
HuhiContentRendererClient::~HuhiContentRendererClient() = default;
