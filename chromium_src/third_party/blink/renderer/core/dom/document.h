/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_DOM_DOCUMENT_H_
#define HUHI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_DOM_DOCUMENT_H_

#include "../../../../../../../third_party/blink/renderer/core/dom/document.h"

#include <random>

#include "base/callback.h"

using blink::Document;
using blink::GarbageCollected;
using blink::HeapObjectHeader;
using blink::MakeGarbageCollected;
using blink::Supplement;
using blink::TraceDescriptor;
using blink::TraceTrait;

namespace blink {
class LocalFrame;
class StaticBitmapImage;
}  // namespace blink

namespace huhi {

typedef base::RepeatingCallback<float(float, size_t)> AudioFarblingCallback;

class CORE_EXPORT HuhiSessionCache final
    : public GarbageCollected<HuhiSessionCache>,
      public Supplement<Document> {

 public:
  static const char kSupplementName[];

  explicit HuhiSessionCache(Document&);
  virtual ~HuhiSessionCache() = default;

  static HuhiSessionCache& From(Document&);

  AudioFarblingCallback GetAudioFarblingCallback(blink::LocalFrame* frame);
  scoped_refptr<blink::StaticBitmapImage> PerturbPixels(
      blink::LocalFrame* frame,
      scoped_refptr<blink::StaticBitmapImage> image_bitmap);
  WTF::String GenerateRandomString(std::string seed, wtf_size_t length);
  std::mt19937_64 MakePseudoRandomGenerator();

 private:
  bool farbling_enabled_;
  uint64_t session_key_;
  uint8_t domain_key_[32];

  scoped_refptr<blink::StaticBitmapImage> PerturbPixelsInternal(
      scoped_refptr<blink::StaticBitmapImage> image_bitmap);
};
}  // namespace huhi

#endif  // HUHI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_DOM_DOCUMENT_H_
