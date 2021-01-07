/* Copyright 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_CHROME_APP_CHROME_MAIN_DELEGATE_H_
#define HUHI_CHROMIUM_SRC_CHROME_APP_CHROME_MAIN_DELEGATE_H_

#include "../../../../chrome/common/chrome_content_client.h"

#include "huhi/common/huhi_content_client.h"

#define ChromeContentClient HuhiContentClient
#include "../../../../chrome/app/chrome_main_delegate.h"
#undef ChromeContentClient

#endif  // HUHI_CHROMIUM_SRC_CHROME_APP_CHROME_MAIN_DELEGATE_H_
