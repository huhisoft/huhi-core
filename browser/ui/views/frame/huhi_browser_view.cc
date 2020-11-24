/* Copyright 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/ui/views/frame/huhi_browser_view.h"

#include "huhi/browser/sparkle_buildflags.h"
#include "huhi/browser/translate/buildflags/buildflags.h"
#include "huhi/browser/ui/views/toolbar/bookmark_button.h"
#include "huhi/browser/ui/views/toolbar/huhi_toolbar_view.h"
#include "extensions/buildflags/buildflags.h"

#if BUILDFLAG(ENABLE_SPARKLE)
#include "huhi/browser/ui/views/update_recommended_message_box_mac.h"
#endif

#if BUILDFLAG(ENABLE_HUHI_TRANSLATE_EXTENSION)
#include "extensions/browser/extension_registry.h"
#include "extensions/common/constants.h"
#endif

void HuhiBrowserView::SetStarredState(bool is_starred) {
  BookmarkButton* button =
      static_cast<HuhiToolbarView*>(toolbar())->bookmark_button();
  if (button)
    button->SetToggled(is_starred);
}

void HuhiBrowserView::ShowUpdateChromeDialog() {
#if BUILDFLAG(ENABLE_SPARKLE)
  // On mac, sparkle frameworks's relaunch api is used.
  UpdateRecommendedMessageBoxMac::Show(GetNativeWindow());
#else
  BrowserView::ShowUpdateChromeDialog();
#endif
}

// The translate bubble will be shown if ENABLE_HUHI_TRANSLATE_GO or
// ENABLE_HUHI_TRANSLATE_EXTENSIONS build flag is enabled and Google Translate
// is not installed. In ENABLE_HUHI_TRANSLATE case, we utilize chromium's
// translate UI directly along with go-translate. In
// ENABLE_HUHI_TRANSLATE_EXTENSION case, we repurpose the translate bubble to
// offer Google Translate extension installation, and the bubble will only be
// shown when Google Translate is not installed.
ShowTranslateBubbleResult HuhiBrowserView::ShowTranslateBubble(
    content::WebContents* web_contents,
    translate::TranslateStep step,
    const std::string& source_language,
    const std::string& target_language,
    translate::TranslateErrors::Type error_type,
    bool is_user_gesture) {
#if BUILDFLAG(ENABLE_HUHI_TRANSLATE_GO)
  return BrowserView::ShowTranslateBubble(web_contents,
                                          step,
                                          source_language,
                                          target_language,
                                          error_type,
                                          is_user_gesture);
#elif BUILDFLAG(ENABLE_HUHI_TRANSLATE_EXTENSION)
  if (!extensions::ExtensionRegistry::Get(GetProfile())
      ->GetInstalledExtension(google_translate_extension_id)) {
    return BrowserView::ShowTranslateBubble(web_contents,
                                            step,
                                            source_language,
                                            target_language,
                                            error_type,
                                            is_user_gesture);
  }
#endif
  return ShowTranslateBubbleResult::BROWSER_WINDOW_NOT_VALID;
}
