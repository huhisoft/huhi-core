/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_PROFILES_HUHI_PROFILE_AVATAR_DOWNLOADER_H_
#define HUHI_BROWSER_PROFILES_HUHI_PROFILE_AVATAR_DOWNLOADER_H_

#include "chrome/browser/profiles/profile_avatar_downloader.h"

class HuhiProfileAvatarDownloader : public ProfileAvatarDownloader {
 public:
  HuhiProfileAvatarDownloader(size_t icon_index,
                               FetchCompleteCallback callback);
  ~HuhiProfileAvatarDownloader() override;

  void Start();

 private:
  FetchCompleteCallback callback_;
};

#endif  // HUHI_BROWSER_PROFILES_HUHI_PROFILE_AVATAR_DOWNLOADER_H_
