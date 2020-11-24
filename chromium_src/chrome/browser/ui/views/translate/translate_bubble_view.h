/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_TRANSLATE_TRANSLATE_BUBBLE_VIEW_H_
#define HUHI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_TRANSLATE_TRANSLATE_BUBBLE_VIEW_H_

#define HUHI_TRANSLATE_BUBBLE_VIEW_H_ \
  private: \
    friend class HuhiTranslateBubbleView; \
    friend class HuhiTranslateBubbleViewTest; \
    FRIEND_TEST_ALL_PREFIXES(HuhiTranslateBubbleViewTest, \
                             HuhiBeforeTranslateView); \
    FRIEND_TEST_ALL_PREFIXES(HuhiTranslateBubbleViewTest, TranslateButton); \
    FRIEND_TEST_ALL_PREFIXES(HuhiTranslateBubbleViewTest, CancelButton); \
  public:
// define HUHI_TRANSLATE_BUBBLE_VIEW_H_

class HuhiTranslateBubbleView;
#include "../../../../../../../chrome/browser/ui/views/translate/translate_bubble_view.h"

#endif  // HUHI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_TRANSLATE_TRANSLATE_BUBBLE_VIEW_H_
