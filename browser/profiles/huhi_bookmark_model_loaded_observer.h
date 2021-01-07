/* Copyright 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_PROFILES_HUHI_BOOKMARK_MODEL_LOADED_OBSERVER_H_
#define HUHI_BROWSER_PROFILES_HUHI_BOOKMARK_MODEL_LOADED_OBSERVER_H_

#include "chrome/browser/profiles/bookmark_model_loaded_observer.h"

class HuhiBookmarkModelLoadedObserver
    : public BookmarkModelLoadedObserver {
 public:
  explicit HuhiBookmarkModelLoadedObserver(Profile* profile);

 private:
  void BookmarkModelLoaded(bookmarks::BookmarkModel* model,
                           bool ids_reassigned) override;

  DISALLOW_COPY_AND_ASSIGN(HuhiBookmarkModelLoadedObserver);
};

#endif  // HUHI_BROWSER_PROFILES_HUHI_BOOKMARK_MODEL_LOADED_OBSERVER_H_
