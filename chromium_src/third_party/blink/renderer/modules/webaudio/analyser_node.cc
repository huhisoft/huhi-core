/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "third_party/blink/renderer/modules/webaudio/analyser_node.h"

#include "third_party/blink/renderer/core/frame/local_dom_window.h"

#define HUHI_ANALYSERHANDLER_CONSTRUCTOR                                 \
  if (ExecutionContext* context = node.GetExecutionContext()) {           \
    if (LocalDOMWindow* local_dom_window =                                \
            DynamicTo<LocalDOMWindow>(context)) {                         \
      analyser_.audio_farbling_callback_ =                                \
          huhi::HuhiSessionCache::From(*(local_dom_window->document())) \
              .GetAudioFarblingCallback(                                  \
                  local_dom_window->document()->GetFrame());              \
    }                                                                     \
  }

#include "../../../../../../../third_party/blink/renderer/modules/webaudio/analyser_node.cc"

#undef HUHI_ANALYSERNODE_CONSTRUCTOR
