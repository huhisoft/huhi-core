/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/components/content_settings/renderer/huhi_content_settings_agent_impl_helper.h"

#define HUHI_WEBGL2_RENDERING_CONTEXT_BASE                                 \
  if (canvas() && !AllowFingerprinting(canvas()->GetDocument().GetFrame())) \
    return ScriptValue::CreateNull(script_state->GetIsolate());

#include "../../../../../../../third_party/blink/renderer/modules/webgl/webgl2_rendering_context_base.cc"
#undef HUHI_WEBGL2_RENDERING_CONTEXT_BASE
