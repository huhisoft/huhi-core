/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/browser/ui/content_settings/content_setting_bubble_model.h"

#include "huhi/browser/ui/content_settings/huhi_content_setting_bubble_model.h"

#define CreateContentSettingBubbleModel \
  CreateContentSettingBubbleModel_ChromiumImpl
#include "../../../../../../chrome/browser/ui/content_settings/content_setting_bubble_model.cc"
#undef CreateContentSettingBubbleModel

// static
std::unique_ptr<ContentSettingBubbleModel>
ContentSettingBubbleModel::CreateContentSettingBubbleModel(
    Delegate* delegate,
    WebContents* web_contents,
    ContentSettingsType content_type) {
  DCHECK(web_contents);
  if (content_type == ContentSettingsType::PLUGINS) {
    return std::make_unique<HuhiContentSettingPluginBubbleModel>(delegate,
                                                                  web_contents);
  }
  return ContentSettingBubbleModel::
      CreateContentSettingBubbleModel_ChromiumImpl(delegate, web_contents,
                                                   content_type);
}
