/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "base/callback.h"
#include "huhi/third_party/blink/renderer/huhi_farbling_constants.h"
#include "third_party/blink/public/platform/web_content_settings_client.h"
#include "third_party/blink/renderer/core/frame/local_dom_window.h"
#include "third_party/blink/renderer/modules/webaudio/analyser_node.h"

#define HUHI_AUDIOBUFFER_GETCHANNELDATA                                   \
  NotShared<DOMFloat32Array> array = getChannelData(channel_index);        \
  LocalDOMWindow* window = LocalDOMWindow::From(script_state);             \
  if (window) {                                                            \
    LocalFrame* frame = window->document()->GetFrame();                    \
    if (frame && frame->GetContentSettingsClient()) {                      \
      DOMFloat32Array* destination_array = array.View();                   \
      size_t len = destination_array->lengthAsSizeT();                     \
      if (len > 0) {                                                       \
        float* destination = destination_array->Data();                    \
        huhi::AudioFarblingCallback audio_farbling_callback =             \
            huhi::HuhiSessionCache::From(*(window->document()))          \
                .GetAudioFarblingCallback(frame);                          \
        for (unsigned i = 0; i < len; ++i) {                               \
          destination[i] = audio_farbling_callback.Run(destination[i], i); \
        }                                                                  \
      }                                                                    \
    }                                                                      \
  }

#define HUHI_AUDIOBUFFER_COPYFROMCHANNEL                              \
  LocalDOMWindow* window = LocalDOMWindow::From(script_state);         \
  if (window) {                                                        \
    huhi::AudioFarblingCallback audio_farbling_callback =             \
        huhi::HuhiSessionCache::From(*(window->document()))          \
            .GetAudioFarblingCallback(window->document()->GetFrame()); \
    for (unsigned i = 0; i < count; i++) {                             \
      dst[i] = audio_farbling_callback.Run(dst[i], i);                 \
    }                                                                  \
  }

#include "../../../../../../../third_party/blink/renderer/modules/webaudio/audio_buffer.cc"

#undef HUHI_AUDIOBUFFER_GETCHANNELDATA
#undef HUHI_AUDIOBUFFER_COPYFROMCHANNEL
