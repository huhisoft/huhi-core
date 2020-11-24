/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_VIEWS_TRANSLATE_HUHI_TRANSLATE_BUBBLE_VIEW_H_
#define HUHI_BROWSER_UI_VIEWS_TRANSLATE_HUHI_TRANSLATE_BUBBLE_VIEW_H_

#include <memory>
#include <utility>

#include "chrome/browser/ui/views/translate/translate_bubble_view.h"

#include "huhi/browser/translate/buildflags/buildflags.h"
#include "extensions/buildflags/buildflags.h"

class HuhiTranslateIconView;

// The purpose of this subclass is to repurpose the translate bubble to install
// google translate extension, this is only used when
// ENABLE_HUHI_TRANSLATE_EXTENSION is true.
class HuhiTranslateBubbleView : public TranslateBubbleView {
 public:
  HuhiTranslateBubbleView(views::View* anchor_view,
                           std::unique_ptr<TranslateBubbleModel> model,
                           translate::TranslateErrors::Type error_type,
                           content::WebContents* web_contents);
  ~HuhiTranslateBubbleView() override;

  // views::BubbleDialogDelegateView methods.
  void Init() override;
  void ButtonPressed(views::Button* sender, const ui::Event& event) override;

  // views::View methods.
  bool AcceleratorPressed(const ui::Accelerator& accelerator) override;

  // LocationBarBubbleDelegateView methods.
  bool ShouldShowWindowTitle() const override;

 protected:
  virtual void InstallGoogleTranslate();

 private:
  friend class HuhiTranslateBubbleViewTest;
  views::View* HuhiCreateViewBeforeTranslate();
  void DisableOfferTranslatePref();

  DISALLOW_COPY_AND_ASSIGN(HuhiTranslateBubbleView);
};

#endif  // HUHI_BROWSER_UI_VIEWS_TRANSLATE_HUHI_TRANSLATE_BUBBLE_VIEW_H_
