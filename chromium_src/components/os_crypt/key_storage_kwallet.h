/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_COMPONENTS_OS_CRYPT_KEY_STORAGE_KWALLET_H_
#define HUHI_CHROMIUM_SRC_COMPONENTS_OS_CRYPT_KEY_STORAGE_KWALLET_H_

#define InitFolder             \
  InitFolder();                \
  const char* GetFolderName(); \
  const char* GetKeyName

#include "../../../../components/os_crypt/key_storage_kwallet.h"
#undef InitFolder

#endif  // HUHI_CHROMIUM_SRC_COMPONENTS_OS_CRYPT_KEY_STORAGE_KWALLET_H_
