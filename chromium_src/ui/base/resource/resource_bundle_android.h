// Copyright (c) 2020 The Huhi Authors
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HUHI_CHROMIUM_SRC_UI_BASE_RESOURCE_RESOURCE_BUNDLE_ANDROID_H_
#define HUHI_CHROMIUM_SRC_UI_BASE_RESOURCE_RESOURCE_BUNDLE_ANDROID_H_

#include "../../../../../ui/base/resource/resource_bundle_android.h"

namespace ui {

COMPONENT_EXPORT(UI_BASE) void HuhiLoadMainAndroidPackFile(
    const char* path_within_apk,
    const base::FilePath& disk_file_path);
COMPONENT_EXPORT(UI_BASE) void HuhiLoadHuhi100PercentPackFile(
    const char* path_within_apk,
    const base::FilePath& disk_file_path);

}

#endif  // HUHI_CHROMIUM_SRC_UI_BASE_RESOURCE_RESOURCE_BUNDLE_ANDROID_H_
