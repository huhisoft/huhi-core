/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_CONTENT_SETTINGS_HUHI_AUTOPLAY_BLOCKED_IMAGE_MODEL_H_
#define HUHI_BROWSER_UI_CONTENT_SETTINGS_HUHI_AUTOPLAY_BLOCKED_IMAGE_MODEL_H_

#include "chrome/browser/ui/content_settings/content_setting_image_model.h"

class HuhiAutoplayBlockedImageModel : public ContentSettingSimpleImageModel {
 public:
  HuhiAutoplayBlockedImageModel();
  bool UpdateAndGetVisibility(content::WebContents* web_contents) override;
  std::unique_ptr<ContentSettingBubbleModel> CreateBubbleModelImpl(
      ContentSettingBubbleModel::Delegate* delegate,
      content::WebContents* web_contents) override;

 private:
  DISALLOW_COPY_AND_ASSIGN(HuhiAutoplayBlockedImageModel);
};

#endif  // HUHI_BROWSER_UI_CONTENT_SETTINGS_HUHI_AUTOPLAY_BLOCKED_IMAGE_MODEL_H_
