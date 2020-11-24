/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_VIEWS_TOOLBAR_HUHI_TOOLBAR_VIEW_H_
#define HUHI_BROWSER_UI_VIEWS_TOOLBAR_HUHI_TOOLBAR_VIEW_H_

#include "base/scoped_observer.h"
#include "chrome/browser/profiles/profile_attributes_storage.h"
#include "chrome/browser/ui/views/toolbar/toolbar_view.h"
#include "components/prefs/pref_member.h"

class BookmarkButton;
class SpeedreaderButton;

class HuhiToolbarView : public ToolbarView,
                         public ProfileAttributesStorage::Observer {
 public:
  explicit HuhiToolbarView(Browser* browser, BrowserView* browser_view);
  ~HuhiToolbarView() override;

  BookmarkButton* bookmark_button() const { return bookmark_; }
  SpeedreaderButton* speedreader_button() const { return speedreader_; }
  void Init() override;
  void Layout() override;
  void Update(content::WebContents* tab) override;
  void OnThemeChanged() override;
  void OnEditBookmarksEnabledChanged();
  void OnLocationBarIsWideChanged();
  void ShowBookmarkBubble(const GURL& url,
                          bool already_bookmarked,
                          bookmarks::BookmarkBubbleObserver* observer) override;

 private:
  void LoadImages() override;
  void ResetLocationBarBounds();
  void ResetButtonBounds();

  // ProfileAttributesStorage::Observer:
  void OnProfileAdded(const base::FilePath& profile_path) override;
  void OnProfileWasRemoved(const base::FilePath& profile_path,
      const base::string16& profile_name) override;

  BookmarkButton* bookmark_ = nullptr;
  // Tracks the preference to determine whether bookmark editing is allowed.
  BooleanPrefMember edit_bookmarks_enabled_;

  SpeedreaderButton* speedreader_ = nullptr;

  BooleanPrefMember location_bar_is_wide_;
  // Whether this toolbar has been initialized.
  bool huhi_initialized_ = false;
  // Tracks profile count to determine whether profile switcher should be shown.
  ScopedObserver<ProfileAttributesStorage, ProfileAttributesStorage::Observer>
      profile_observer_;
};

#endif  // HUHI_BROWSER_UI_VIEWS_TOOLBAR_HUHI_TOOLBAR_VIEW_H_
