// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/common/channel_info.h"

#include "base/environment.h"
#include "base/strings/string_util.h"
#include "huhi/common/huhi_channel_info_posix.h"
#include "build/build_config.h"
#include "components/version_info/version_info.h"

namespace chrome {

std::string GetChannelName() {
  std::string modifier;
  huhi::GetChannelImpl(&modifier, nullptr);
  return modifier;
}

std::string GetChannelSuffixForDataDir() {
  return std::string();
}

#if defined(OS_LINUX)
std::string GetDesktopName(base::Environment* env) {
#if defined(OFFICIAL_BUILD)
  version_info::Channel product_channel(chrome::GetChannel());
  switch (product_channel) {
    case version_info::Channel::DEV:
      return "huhi-browser-dev.desktop";
    case version_info::Channel::BETA:
      return "huhi-browser-beta.desktop";
    default:
      return "huhi-browser.desktop";
  }
#endif  // defined(OFFICIAL_BUILD)
  // Allow $CHROME_DESKTOP to override the built-in value, so that development
  // versions can set themselves as the default without interfering with
  // non-official, packaged versions using the built-in value.
  std::string name;
  if (env->GetVar("CHROME_DESKTOP", &name) && !name.empty())
    return name;
  return "huhi-browser.desktop";
}
#endif  // defined(OS_LINUX)

version_info::Channel GetChannel() {
  return huhi::GetChannelImpl(nullptr, nullptr);
}

}  // namespace chrome
