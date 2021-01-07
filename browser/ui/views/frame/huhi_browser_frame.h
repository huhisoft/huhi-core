/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_VIEWS_FRAME_HUHI_BROWSER_FRAME_H_
#define HUHI_BROWSER_UI_VIEWS_FRAME_HUHI_BROWSER_FRAME_H_

#include "chrome/browser/ui/views/frame/browser_frame.h"

class HuhiBrowserFrame : public BrowserFrame {
 public:
  explicit HuhiBrowserFrame(BrowserView* browser_view);

  // BrowserFrame overrides:
  const ui::NativeTheme* GetNativeTheme() const override;

 private:
  BrowserView* view_;

  DISALLOW_COPY_AND_ASSIGN(HuhiBrowserFrame);
};

#endif  // HUHI_BROWSER_UI_VIEWS_FRAME_HUHI_BROWSER_FRAME_H_
