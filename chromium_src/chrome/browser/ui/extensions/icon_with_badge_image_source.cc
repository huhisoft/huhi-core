/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#define HUHI_ICON_WITH_BADGE_IMAGE_SOURCE_DRAW_1 \
  true ? ScaleImageSkiaRep(rep,                             \
                           GetCustomGraphicSize().value_or( \
                               extensions::ExtensionAction::ActionIconSize()), \
                           canvas->image_scale()) :

#define HUHI_ICON_WITH_BADGE_IMAGE_SOURCE_DRAW_2 \
  if (GetCustomGraphicXOffset().has_value())      \
    x_offset = GetCustomGraphicXOffset().value(); \
  if (GetCustomGraphicYOffset().has_value())      \
    y_offset = GetCustomGraphicYOffset().value();

#include "../../../../../../chrome/browser/ui/extensions/icon_with_badge_image_source.cc"
#undef HUHI_ICON_WITH_BADGE_IMAGE_SOURCE_DRAW_2
#undef HUHI_ICON_WITH_BADGE_IMAGE_SOURCE_DRAW_1

// Implement default virtual methods
base::Optional<int> IconWithBadgeImageSource::GetCustomGraphicSize() {
  return base::nullopt;
}

base::Optional<int> IconWithBadgeImageSource::GetCustomGraphicXOffset() {
  return base::nullopt;
}

base::Optional<int> IconWithBadgeImageSource::GetCustomGraphicYOffset() {
  return base::nullopt;
}
