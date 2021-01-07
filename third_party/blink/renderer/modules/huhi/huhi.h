// Copyright (c) 2020 The Huhi Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HUHI_THIRD_PARTY_BLINK_RENDERER_MODULES_HUHI_HUHI_H_
#define HUHI_THIRD_PARTY_BLINK_RENDERER_MODULES_HUHI_HUHI_H_

#include "third_party/blink/renderer/modules/modules_export.h"
#include "third_party/blink/renderer/platform/bindings/script_wrappable.h"
#include "third_party/blink/renderer/platform/heap/handle.h"

namespace blink {

class ScriptPromise;
class ScriptState;

class MODULES_EXPORT Huhi final
    : public ScriptWrappable {
  DEFINE_WRAPPERTYPEINFO();

 public:
  Huhi() = default;
  ScriptPromise isHuhi(ScriptState*);
};

}  // namespace blink

#endif  // HUHI_THIRD_PARTY_BLINK_RENDERER_MODULES_HUHI_HUHI_H_
