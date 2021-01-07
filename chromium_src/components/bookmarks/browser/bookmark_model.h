/* Copyright 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_COMPONENTS_BOOKMARKS_BROWSER_BOOKMARK_MODEL_H_
#define HUHI_CHROMIUM_SRC_COMPONENTS_BOOKMARKS_BROWSER_BOOKMARK_MODEL_H_

class HuhiSyncServiceTestDelayedLoadModel;

#define HUHI_BOOKMARK_MODEL_H \
 private: \
  friend class ::HuhiSyncServiceTestDelayedLoadModel;

#include "../../../../../components/bookmarks/browser/bookmark_model.h"

namespace bookmarks {
void HuhiMigrateOtherNodeFolder(BookmarkModel* model);
void HuhiClearSyncV1MetaInfo(BookmarkModel* model);
}  // namespace bookmarks

#endif  // HUHI_CHROMIUM_SRC_COMPONENTS_BOOKMARKS_BROWSER_BOOKMARK_MODEL_H_
