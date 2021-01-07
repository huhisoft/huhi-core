/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_RENDERER_HUHI_CONTENT_RENDERER_CLIENT_H_
#define HUHI_RENDERER_HUHI_CONTENT_RENDERER_CLIENT_H_

#include "chrome/renderer/chrome_content_renderer_client.h"

class HuhiContentRendererClient : public ChromeContentRendererClient {
 public:
  HuhiContentRendererClient();
  ~HuhiContentRendererClient() override;
  void SetRuntimeFeaturesDefaultsBeforeBlinkInitialization() override;

 private:
  DISALLOW_COPY_AND_ASSIGN(HuhiContentRendererClient);
};

#endif  // HUHI_RENDERER_HUHI_CONTENT_RENDERER_CLIENT_H_
