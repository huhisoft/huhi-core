/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_MODULES_WEBAUDIO_REALTIME_ANALYSER_H_
#define HUHI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_MODULES_WEBAUDIO_REALTIME_ANALYSER_H_

#include "base/callback.h"

#define HUHI_REALTIMEANALYSER_H \
  base::RepeatingCallback<float(float, size_t)> audio_farbling_callback_;

#include "../../../../../../../third_party/blink/renderer/modules/webaudio/realtime_analyser.h"

#undef HUHI_REALTIMEANALYSER_H

#endif  // HUHI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_MODULES_WEBAUDIO_REALTIME_ANALYSER_H_
