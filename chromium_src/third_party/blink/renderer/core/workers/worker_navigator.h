/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_WORKERS_WORKER_NAVIGATOR_H_
#define HUHI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_WORKERS_WORKER_NAVIGATOR_H_

#include "third_party/blink/renderer/core/frame/navigator_id.h"

#define userAgent                 \
  userAgent_ChromiumImpl() const; \
  String userAgent

#include "../../../../../../../third_party/blink/renderer/core/workers/worker_navigator.h"

#undef userAgent

#endif  // HUHI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_WORKERS_WORKER_NAVIGATOR_H_
