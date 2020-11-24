/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_CHROME_BROWSER_UI_PAGE_INFO_CHROME_PAGE_INFO_DELEGATE_H_
#define HUHI_CHROMIUM_SRC_CHROME_BROWSER_UI_PAGE_INFO_CHROME_PAGE_INFO_DELEGATE_H_

#include "components/page_info/page_info_delegate.h"

#define IsContentDisplayedInVrHeadset                           \
  HuhiShouldShowPermission(ContentSettingsType type) override; \
  virtual bool IsContentDisplayedInVrHeadset

#include "../../../../../../chrome/browser/ui/page_info/chrome_page_info_delegate.h"
#undef IsContentDisplayedInVrHeadset

#endif  // HUHI_CHROMIUM_SRC_CHROME_BROWSER_UI_PAGE_INFO_CHROME_PAGE_INFO_DELEGATE_H_
