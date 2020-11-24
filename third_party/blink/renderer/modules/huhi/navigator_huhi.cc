/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/third_party/blink/renderer/modules/huhi/navigator_huhi.h"

#include "third_party/blink/renderer/core/frame/navigator.h"
#include "huhi/third_party/blink/renderer/modules/huhi/huhi.h"

namespace blink {

NavigatorHuhi::NavigatorHuhi(Navigator& navigator)
    : Supplement<Navigator>(navigator) {}

// static
const char NavigatorHuhi::kSupplementName[] = "NavigatorHuhi";

NavigatorHuhi& NavigatorHuhi::From(Navigator& navigator) {
  NavigatorHuhi* supplement =
      Supplement<Navigator>::From<NavigatorHuhi>(navigator);
  if (!supplement) {
    supplement = MakeGarbageCollected<NavigatorHuhi>(navigator);
    ProvideTo(navigator, supplement);
  }
  return *supplement;
}

Huhi* NavigatorHuhi::huhi(Navigator& navigator) {
  return NavigatorHuhi::From(navigator).huhi();
}

Huhi* NavigatorHuhi::huhi() {
  if (!huhi_) {
    huhi_ = MakeGarbageCollected<Huhi>();
  }
  return huhi_;
}

void NavigatorHuhi::Trace(blink::Visitor* visitor) const {
  visitor->Trace(huhi_);
  Supplement<Navigator>::Trace(visitor);
}

}  // namespace blink
