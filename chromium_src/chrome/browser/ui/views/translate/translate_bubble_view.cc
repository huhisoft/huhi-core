/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/ui/views/translate/huhi_translate_bubble_view.h"
#include "huhi/grit/huhi_generated_resources.h"
#include "chrome/grit/generated_resources.h"

#if BUILDFLAG(ENABLE_HUHI_TRANSLATE_GO)
#undef IDS_TRANSLATE_BUBBLE_BEFORE_TRANSLATE_TITLE
#define IDS_TRANSLATE_BUBBLE_BEFORE_TRANSLATE_TITLE \
  IDS_HUHI_TRANSLATE_BUBBLE_BEFORE_TRANSLATE_TITLE
#elif BUILDFLAG(ENABLE_HUHI_TRANSLATE_EXTENSION)
#undef IDS_TRANSLATE_BUBBLE_BEFORE_TRANSLATE_TITLE
#define IDS_TRANSLATE_BUBBLE_BEFORE_TRANSLATE_TITLE \
  IDS_HUHI_TRANSLATE_BUBBLE_BEFORE_TRANSLATE_INSTALL_TITLE
#endif

#if BUILDFLAG(ENABLE_HUHI_TRANSLATE_EXTENSION)
#define HUHI_TRANSLATE_BUBBLE_VIEW_ HuhiTranslateBubbleView
#else
#define HUHI_TRANSLATE_BUBBLE_VIEW_ TranslateBubbleView
#endif

#include "../../../../../../../chrome/browser/ui/views/translate/translate_bubble_view.cc"
