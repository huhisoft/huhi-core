/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "huhi/browser/extensions/api/huhi_extensions_api_client.h"
#include "huhi/browser/extensions/updater/huhi_update_client_config.h"
#include "chrome/browser/extensions/updater/chrome_update_client_config.h"

#define ChromeExtensionsAPIClient HuhiExtensionsAPIClient
#define ChromeUpdateClientConfig HuhiUpdateClientConfig
#include "../../../../../chrome/browser/extensions/chrome_extensions_browser_client.cc"
#undef ChromeExtensionsAPIClient
#undef ChromeUpdateClientConfig
