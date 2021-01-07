// Copyright (c) 2020 The Huhi Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HUHI_THIRD_PARTY_BLINK_RENDERER_MODULES_HUHI_NAVIGATOR_HUHI_H_
#define HUHI_THIRD_PARTY_BLINK_RENDERER_MODULES_HUHI_NAVIGATOR_HUHI_H_

#include "third_party/blink/renderer/core/frame/navigator.h"
#include "third_party/blink/renderer/platform/bindings/name_client.h"
#include "third_party/blink/renderer/platform/heap/handle.h"
#include "third_party/blink/renderer/platform/supplementable.h"

namespace blink {

class Huhi;
class Navigator;

class NavigatorHuhi final
    : public GarbageCollected<NavigatorHuhi>,
      public Supplement<Navigator>,
      public NameClient {

 public:
  static const char kSupplementName[];

  static NavigatorHuhi& From(Navigator&);
  static Huhi* huhi(Navigator&);
  Huhi* huhi();

  explicit NavigatorHuhi(Navigator&);

  void Trace(blink::Visitor*) const override;
  const char* NameInHeapSnapshot() const override {
    return "NavigatorHuhi";
  }

 private:
  Member<Huhi> huhi_;
};

}  // namespace blink

#endif  // HUHI_THIRD_PARTY_BLINK_RENDERER_MODULES_HUHI_NAVIGATOR_HUHI_H_
