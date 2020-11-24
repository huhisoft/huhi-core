/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_DOWNLOAD_DOWNLOAD_ITEM_VIEW_H_
#define HUHI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_DOWNLOAD_DOWNLOAD_ITEM_VIEW_H_

#define HUHI_DOWNLOAD_DOWNLOAD_ITEM_VIEW_H_ \
 private:                                    \
  friend class HuhiDownloadItemView;        \
                                             \
 public:                                     \
 protected:                                  \
  bool IsShowingWarningDialog() const;

#define UpdateMode virtual UpdateMode
#include "../../../../../../../chrome/browser/ui/views/download/download_item_view.h"
#undef UpdateMode
#undef HUHI_DOWNLOAD_DOWNLOAD_ITEM_VIEW_H_

#endif  // HUHI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_DOWNLOAD_DOWNLOAD_ITEM_VIEW_H_
