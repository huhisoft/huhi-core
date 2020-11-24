/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/profiles/huhi_profile_shortcut_manager_win.h"

#include "huhi/browser/profiles/profile_util.h"
#include "chrome/browser/profiles/profile_attributes_storage.h"
#include "chrome/browser/profiles/profile_manager.h"

HuhiProfileShortcutManagerWin::HuhiProfileShortcutManagerWin(
    ProfileManager* manager)
    : ProfileShortcutManagerWin(manager),
      profile_manager_(manager) {}

void HuhiProfileShortcutManagerWin::GetShortcutProperties(
    const base::FilePath& profile_path,
    base::CommandLine* command_line,
    base::string16* name,
    base::FilePath* icon_path) {
  // Session profiles are currently not added into storage because they will
  // return early in ProfileManager::AddProfileToStorage because of the profile
  // path is not directly under user_data_dir. To avoid DCHECK(has_entry) in
  // chromium's GetShortcutProperties and invalid access to the entry, return
  // early here when entry cannot be found.
  //
  // TODO(jocelyn): Properly add session profiles into the storage and remove
  // this override.
  if (huhi::IsSessionProfilePath(profile_path)) {
    ProfileAttributesStorage& storage =
        profile_manager_->GetProfileAttributesStorage();
    ProfileAttributesEntry* entry;
    bool has_entry =
        storage.GetProfileAttributesWithPath(profile_path, &entry);
    if (!has_entry)
      return;
  }

  ProfileShortcutManagerWin::GetShortcutProperties(profile_path,
                                                   command_line,
                                                   name,
                                                   icon_path);
}
