/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/common/channel_info.h"

#include "base/files/file_path.h"
#include "chrome/common/chrome_paths_internal.h"
#include "components/version_info/channel.h"
#include "testing/gtest/include/gtest/gtest.h"

#if defined(OS_LINUX)
#include "base/environment.h"
#endif

#if defined(OS_MAC)
// GetChannelByName is only supported on MacOS.
TEST(HuhiChannelInfoTest, ChannelByNameTest) {
#if defined(OFFICIAL_BUILD)
  EXPECT_EQ(version_info::Channel::STABLE,
            chrome::GetChannelByName(""));
  EXPECT_EQ(version_info::Channel::BETA,
            chrome::GetChannelByName("beta"));
  EXPECT_EQ(version_info::Channel::DEV,
            chrome::GetChannelByName("dev"));
  EXPECT_EQ(version_info::Channel::CANARY,
            chrome::GetChannelByName("nightly"));
#else
  EXPECT_EQ(version_info::Channel::UNKNOWN,
            chrome::GetChannelByName(""));
#endif
}
#endif  // OS_MAC

#if defined(OS_LINUX)
TEST(HuhiChannelInfoTest, ParentDirectoryOfUserDataDirectoryTest) {
  base::FilePath path;
  EXPECT_TRUE(chrome::GetDefaultUserDataDirectory(&path));
  EXPECT_EQ("HuhiSoftware", path.DirName().BaseName().AsUTF8Unsafe());
}

TEST(HuhiChannelInfoTest, DefaultUserDataDirectoryAndChannelTest) {
  base::FilePath path;
#if defined(OFFICIAL_BUILD)
  auto env = base::Environment::Create();

  env->SetVar("CHROME_VERSION_EXTRA", LINUX_CHANNEL_STABLE);
  EXPECT_TRUE(chrome::GetDefaultUserDataDirectory(&path));
  EXPECT_EQ("Huhi-Browser", path.BaseName().AsUTF8Unsafe());
  EXPECT_EQ(version_info::Channel::STABLE, chrome::GetChannel());
  EXPECT_EQ(HUHI_LINUX_CHANNEL_STABLE, chrome::GetChannelName());

  env->SetVar("CHROME_VERSION_EXTRA", LINUX_CHANNEL_BETA);
  EXPECT_TRUE(chrome::GetDefaultUserDataDirectory(&path));
  EXPECT_EQ("Huhi-Browser-Beta", path.BaseName().AsUTF8Unsafe());
  EXPECT_EQ(version_info::Channel::BETA, chrome::GetChannel());
  EXPECT_EQ(LINUX_CHANNEL_BETA, chrome::GetChannelName());

  env->SetVar("CHROME_VERSION_EXTRA", HUHI_LINUX_CHANNEL_DEV);
  EXPECT_TRUE(chrome::GetDefaultUserDataDirectory(&path));
  EXPECT_EQ("Huhi-Browser-Dev", path.BaseName().AsUTF8Unsafe());
  EXPECT_EQ(version_info::Channel::DEV, chrome::GetChannel());
  EXPECT_EQ(HUHI_LINUX_CHANNEL_DEV, chrome::GetChannelName());

  env->SetVar("CHROME_VERSION_EXTRA", LINUX_CHANNEL_DEV);
  EXPECT_TRUE(chrome::GetDefaultUserDataDirectory(&path));
  EXPECT_EQ("Huhi-Browser-Dev", path.BaseName().AsUTF8Unsafe());
  EXPECT_EQ(version_info::Channel::DEV, chrome::GetChannel());
  EXPECT_EQ(HUHI_LINUX_CHANNEL_DEV, chrome::GetChannelName());

  env->SetVar("CHROME_VERSION_EXTRA", HUHI_LINUX_CHANNEL_NIGHTLY);
  EXPECT_TRUE(chrome::GetDefaultUserDataDirectory(&path));
  EXPECT_EQ("Huhi-Browser-Nightly", path.BaseName().AsUTF8Unsafe());
  EXPECT_EQ(version_info::Channel::CANARY, chrome::GetChannel());
  EXPECT_EQ(HUHI_LINUX_CHANNEL_NIGHTLY, chrome::GetChannelName());
#else  // OFFICIAL_BUILD
  EXPECT_TRUE(chrome::GetDefaultUserDataDirectory(&path));
  EXPECT_EQ("Huhi-Browser-Development", path.BaseName().AsUTF8Unsafe());
  EXPECT_EQ(version_info::Channel::UNKNOWN, chrome::GetChannel());
  EXPECT_EQ(HUHI_LINUX_CHANNEL_STABLE, chrome::GetChannelName());
#endif  // !OFFICIAL_BUILD
}
#endif
