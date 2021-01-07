/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_CHROME_RENDERER_WORKER_CONTENT_SETTINGS_CLIENT_H_
#define HUHI_CHROMIUM_SRC_CHROME_RENDERER_WORKER_CONTENT_SETTINGS_CLIENT_H_

#define HUHI_WORKER_CONTENT_SETTINGS_CLIENT_H         \
  HuhiFarblingLevel GetHuhiFarblingLevel() override; \
  bool AllowFingerprinting(bool enabled_per_settings) override;

#include "../../../../chrome/renderer/worker_content_settings_client.h"

#undef HUHI_WORKER_CONTENT_SETTINGS_CLIENT_H

#endif  // HUHI_CHROMIUM_SRC_CHROME_RENDERER_WORKER_CONTENT_SETTINGS_CLIENT_H_
