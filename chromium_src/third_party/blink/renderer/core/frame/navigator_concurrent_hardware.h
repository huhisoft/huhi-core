/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_FRAME_NAVIGATOR_CONCURRENT_HARDWARE_H_
#define HUHI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_FRAME_NAVIGATOR_CONCURRENT_HARDWARE_H_

#include "third_party/blink/renderer/core/core_export.h"

namespace blink {

class ScriptState;

class CORE_EXPORT NavigatorConcurrentHardware {
 public:
  unsigned hardwareConcurrency(ScriptState*) const;
};

}  // namespace blink

#endif  // HUHI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_FRAME_NAVIGATOR_CONCURRENT_HARDWARE_H_
