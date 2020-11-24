/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMMON_IMPORTER_CHROME_IMPORTER_UTILS_H_
#define HUHI_COMMON_IMPORTER_CHROME_IMPORTER_UTILS_H_

#include <string>
#include <vector>

#include "extensions/buildflags/buildflags.h"

namespace base {
class FilePath;
class ListValue;
class Value;
}  // namespace base

base::FilePath GetChromeUserDataFolder();
#if !defined(OS_LINUX)
base::FilePath GetCanaryUserDataFolder();
#endif
base::FilePath GetChromiumUserDataFolder();

base::ListValue* GetChromeSourceProfiles(
  const base::FilePath& user_data_folder);

bool ChromeImporterCanImport(const base::FilePath& profile,
                             uint16_t* services_supported);

#if BUILDFLAG(ENABLE_EXTENSIONS)
std::vector<std::string> GetImportableListFromChromeExtensionsList(
    const base::Value& extension_list);
#endif

#endif  // HUHI_COMMON_IMPORTER_CHROME_IMPORTER_UTILS_H_
