/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/common/chrome_paths_internal.h"

#define GetDefaultUserDataDirectory GetDefaultUserDataDirectory_Disabled
#include "../../../../chrome/common/chrome_paths_linux.cc"
#undef GetDefaultUserDataDirectory

#include "huhi/common/huhi_channel_info_posix.h"

namespace chrome {

bool GetDefaultUserDataDirectory(base::FilePath* result) {
  std::unique_ptr<base::Environment> env(base::Environment::Create());
  base::FilePath config_dir;
  std::string chrome_config_home_str;
  config_dir =
      GetXDGDirectory(env.get(), kXdgConfigHomeEnvVar, kDotConfigDir);

  std::string data_dir_suffix;
  huhi::GetChannelImpl(nullptr, &data_dir_suffix);

  *result = config_dir.Append("HuhiSoftware/Huhi-Browser" + data_dir_suffix);
  return true;
}

}  // namespace chrome
