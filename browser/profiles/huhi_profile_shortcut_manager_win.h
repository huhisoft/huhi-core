/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_PROFILES_HUHI_PROFILE_SHORTCUT_MANAGER_WIN_H_
#define HUHI_BROWSER_PROFILES_HUHI_PROFILE_SHORTCUT_MANAGER_WIN_H_

#include "chrome/browser/profiles/profile_shortcut_manager_win.h"

class HuhiProfileShortcutManagerWin : public ProfileShortcutManagerWin {
 public:
  explicit HuhiProfileShortcutManagerWin(ProfileManager* manager);
  ~HuhiProfileShortcutManagerWin() override = default;

  void GetShortcutProperties(const base::FilePath& profile_path,
                             base::CommandLine* command_line,
                             base::string16* name,
                             base::FilePath* icon_path) override;

 private:
  ProfileManager* profile_manager_;

  DISALLOW_COPY_AND_ASSIGN(HuhiProfileShortcutManagerWin);
};

#endif  // HUHI_BROWSER_PROFILES_HUHI_PROFILE_SHORTCUT_MANAGER_WIN_H_
