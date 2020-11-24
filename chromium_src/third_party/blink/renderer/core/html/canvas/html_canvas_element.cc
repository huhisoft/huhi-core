/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#define HUHI_TO_DATA_URL_INTERNAL                             \
  image_bitmap = huhi::HuhiSessionCache::From(GetDocument()) \
                     .PerturbPixels(GetDocument().GetFrame(), image_bitmap);

#include "../../../../../../../../third_party/blink/renderer/core/html/canvas/html_canvas_element.cc"

#undef HUHI_TO_DATA_URL_INTERNAL
