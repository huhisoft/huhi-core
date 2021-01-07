/* Copyright 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/profiles/huhi_bookmark_model_loaded_observer.h"

#include "huhi/common/pref_names.h"
#include "huhi/components/huhi_sync/huhi_sync_prefs.h"
#include "chrome/browser/profiles/profile.h"
#include "components/bookmarks/browser/bookmark_model.h"
#include "components/prefs/pref_service.h"

using bookmarks::BookmarkModel;

HuhiBookmarkModelLoadedObserver::HuhiBookmarkModelLoadedObserver(
    Profile* profile)
    : BookmarkModelLoadedObserver(profile) {}

void HuhiBookmarkModelLoadedObserver::BookmarkModelLoaded(
    BookmarkModel* model,
    bool ids_reassigned) {
  if (!profile_->GetPrefs()->GetBoolean(kOtherBookmarksMigrated)) {
    HuhiMigrateOtherNodeFolder(model);
    profile_->GetPrefs()->SetBoolean(kOtherBookmarksMigrated, true);
  }

  huhi_sync::Prefs huhi_sync_prefs(profile_->GetPrefs());
  if (!huhi_sync_prefs.IsSyncV1MetaInfoCleared()) {
    HuhiClearSyncV1MetaInfo(model);
    huhi_sync_prefs.SetSyncV1MetaInfoCleared(true);
  }

  BookmarkModelLoadedObserver::BookmarkModelLoaded(model, ids_reassigned);
}
