/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/ui/huhi_browser_content_setting_bubble_model_delegate.h"

#include "huhi/common/url_constants.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_tabstrip.h"

const char kHuhiCommunitySupportUrl[] = "https://community.hnq.vn/";

HuhiBrowserContentSettingBubbleModelDelegate::
HuhiBrowserContentSettingBubbleModelDelegate(Browser* browser) :
    BrowserContentSettingBubbleModelDelegate(browser),
    browser_(browser) {
}

HuhiBrowserContentSettingBubbleModelDelegate::
~HuhiBrowserContentSettingBubbleModelDelegate() {
}

void
HuhiBrowserContentSettingBubbleModelDelegate::ShowWidevineLearnMorePage() {
  GURL learn_more_url = GURL(kWidevineTOS);
  chrome::AddSelectedTabWithURL(browser_, learn_more_url,
                                ui::PAGE_TRANSITION_LINK);
}

void HuhiBrowserContentSettingBubbleModelDelegate::ShowLearnMorePage(
    ContentSettingsType type) {
  // TODO: Use specific support pages for each content setting type
  GURL learn_more_url(kHuhiCommunitySupportUrl);
  chrome::AddSelectedTabWithURL(browser_, learn_more_url,
                                ui::PAGE_TRANSITION_LINK);
}
