/* Copyright 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_VIEWS_FRAME_HUHI_BROWSER_VIEW_H_
#define HUHI_BROWSER_UI_VIEWS_FRAME_HUHI_BROWSER_VIEW_H_

#include <string>

#include "chrome/browser/ui/views/frame/browser_view.h"

class HuhiBrowserView : public BrowserView {
 public:
  using BrowserView::BrowserView;

  void SetStarredState(bool is_starred) override;
  void ShowUpdateChromeDialog() override;
  ShowTranslateBubbleResult ShowTranslateBubble(
      content::WebContents* web_contents,
      translate::TranslateStep step,
      const std::string& source_language,
      const std::string& target_language,
      translate::TranslateErrors::Type error_type,
      bool is_user_gesture) override;

 private:
  DISALLOW_COPY_AND_ASSIGN(HuhiBrowserView);
};

#endif  // HUHI_BROWSER_UI_VIEWS_FRAME_HUHI_BROWSER_VIEW_H_
