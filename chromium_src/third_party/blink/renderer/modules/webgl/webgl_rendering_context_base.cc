/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/components/content_settings/renderer/huhi_content_settings_agent_impl_helper.h"
#include "third_party/blink/renderer/core/dom/document.h"

#define HUHI_WEBGL_RENDERING_CONTEXT_BASE_RETURN                           \
  if (canvas() && !AllowFingerprinting(canvas()->GetDocument().GetFrame())) \
    return;

#define HUHI_WEBGL_RENDERING_CONTEXT_BASE_NULLPTR                          \
  if (canvas() && !AllowFingerprinting(canvas()->GetDocument().GetFrame())) \
    return nullptr;

#define HUHI_WEBGL_RENDERING_CONTEXT_BASE_NULLOPT                          \
  if (canvas() && !AllowFingerprinting(canvas()->GetDocument().GetFrame())) \
    return base::nullopt;

#define HUHI_WEBGL_RENDERING_CONTEXT_BASE_ZERO                             \
  if (canvas() && !AllowFingerprinting(canvas()->GetDocument().GetFrame())) \
    return 0;

#define HUHI_WEBGL_RENDERING_CONTEXT_BASE_MINUS_ONE                        \
  if (canvas() && !AllowFingerprinting(canvas()->GetDocument().GetFrame())) \
    return -1;

#define HUHI_WEBGL_RENDERING_CONTEXT_BASE_SCRIPT_VALUE                     \
  if (canvas() && !AllowFingerprinting(canvas()->GetDocument().GetFrame())) \
    return ScriptValue::CreateNull(script_state->GetIsolate());

#define HUHI_WEBGL_RENDERING_CONTEXT_BASE_STRING                           \
  if (canvas() && !AllowFingerprinting(canvas()->GetDocument().GetFrame())) \
    return String();

#define HUHI_WEBGL_GET_PARAMETER_UNMASKED_RENDERER                    \
  if (ExtensionEnabled(kWebGLDebugRendererInfoName) && canvas() &&     \
      !AllowFingerprinting(canvas()->GetDocument().GetFrame()))        \
    return WebGLAny(                                                   \
        script_state,                                                  \
        String(huhi::HuhiSessionCache::From(canvas()->GetDocument()) \
                   .GenerateRandomString("UNMASKED_RENDERER_WEBGL", 8)));

#define HUHI_WEBGL_GET_PARAMETER_UNMASKED_VENDOR                      \
  if (ExtensionEnabled(kWebGLDebugRendererInfoName) && canvas() &&     \
      !AllowFingerprinting(canvas()->GetDocument().GetFrame()))        \
    return WebGLAny(                                                   \
        script_state,                                                  \
        String(huhi::HuhiSessionCache::From(canvas()->GetDocument()) \
                   .GenerateRandomString("UNMASKED_VENDOR_WEBGL", 8)));

#include "../../../../../../../third_party/blink/renderer/modules/webgl/webgl_rendering_context_base.cc"
#undef HUHI_WEBGL_GET_PARAMETER_UNMASKED_RENDERER
#undef HUHI_WEBGL_GET_PARAMETER_UNMASKED_VENDOR
#undef HUHI_WEBGL_RENDERING_CONTEXT_BASE_STRING
#undef HUHI_WEBGL_RENDERING_CONTEXT_BASE_SCRIPT_VALUE
#undef HUHI_WEBGL_RENDERING_CONTEXT_BASE_MINUS_ONE
#undef HUHI_WEBGL_RENDERING_CONTEXT_BASE_ZERO
#undef HUHI_WEBGL_RENDERING_CONTEXT_BASE_NULLOPT
#undef HUHI_WEBGL_RENDERING_CONTEXT_BASE_NULLPTR
#undef HUHI_WEBGL_RENDERING_CONTEXT_BASE_RETURN
