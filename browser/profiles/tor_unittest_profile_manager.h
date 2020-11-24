/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_PROFILES_TOR_UNITTEST_PROFILE_MANAGER_H_
#define HUHI_BROWSER_PROFILES_TOR_UNITTEST_PROFILE_MANAGER_H_

#include <memory>

#include "huhi/browser/profiles/huhi_profile_manager.h"

class TorUnittestProfileManager : public HuhiProfileManagerWithoutInit {
 public:
  explicit TorUnittestProfileManager(const base::FilePath& user_data_dir)
      : HuhiProfileManagerWithoutInit(user_data_dir) {}
  ~TorUnittestProfileManager() override = default;

 protected:
  std::unique_ptr<Profile> CreateProfileHelper(
      const base::FilePath& path) override;

  std::unique_ptr<Profile> CreateProfileAsyncHelper(
      const base::FilePath& path,
      Delegate* delegate) override;

  void InitProfileUserPrefs(Profile* profile) override;

 private:
  std::unique_ptr<Profile> CreateProfile(const base::FilePath& path,
                                         Delegate* delegate);
};

#endif  // HUHI_BROWSER_PROFILES_TOR_UNITTEST_PROFILE_MANAGER_H_
