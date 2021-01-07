/* Copyright 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_VIEWS_FRAME_HUHI_BROWSER_VIEW_H_
#define HUHI_BROWSER_UI_VIEWS_FRAME_HUHI_BROWSER_VIEW_H_

#include <memory>
#include <string>

#include "huhi/browser/ui/tabs/huhi_tab_strip_model.h"
#include "chrome/browser/ui/views/frame/browser_view.h"

class HuhiBrowserView : public BrowserView {
 public:
  explicit HuhiBrowserView(std::unique_ptr<Browser> browser);
  ~HuhiBrowserView() override;

  void SetStarredState(bool is_starred) override;
  void ShowUpdateChromeDialog() override;
  ShowTranslateBubbleResult ShowTranslateBubble(
      content::WebContents* web_contents,
      translate::TranslateStep step,
      const std::string& source_language,
      const std::string& target_language,
      translate::TranslateErrors::Type error_type,
      bool is_user_gesture) override;

  void StartTabCycling() override;

 private:
  class TabCyclingEventHandler;

  // BrowserView overrides:
  void OnTabStripModelChanged(
      TabStripModel* tab_strip_model,
      const TabStripModelChange& change,
      const TabStripSelectionChange& selection) override;

  void StopTabCycling();

  std::unique_ptr<TabCyclingEventHandler> tab_cycling_event_handler_;

  DISALLOW_COPY_AND_ASSIGN(HuhiBrowserView);
};

#endif  // HUHI_BROWSER_UI_VIEWS_FRAME_HUHI_BROWSER_VIEW_H_
