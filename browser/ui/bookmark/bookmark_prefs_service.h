/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_BOOKMARK_BOOKMARK_PREFS_SERVICE_H_
#define HUHI_BROWSER_UI_BOOKMARK_BOOKMARK_PREFS_SERVICE_H_

#include "components/keyed_service/core/keyed_service.h"
#include "components/prefs/pref_change_registrar.h"
#include "content/public/browser/browser_thread.h"

class PrefService;
class Profile;

class BookmarkPrefsService : public KeyedService {
 public:
  explicit BookmarkPrefsService(Profile* profile);
  ~BookmarkPrefsService() override;

 private:
  void OnPreferenceChanged();

  Profile* profile_;
  PrefService* prefs_;
  PrefChangeRegistrar pref_change_registrar_;

  DISALLOW_COPY_AND_ASSIGN(BookmarkPrefsService);
};

#endif  // HUHI_BROWSER_UI_BOOKMARK_BOOKMARK_PREFS_SERVICE_H_
