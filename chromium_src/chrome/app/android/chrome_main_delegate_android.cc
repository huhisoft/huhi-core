/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/app/huhi_main_delegate.h"

#define ChromeMainDelegate HuhiMainDelegate
#include "../../../../../chrome/app/android/chrome_main_delegate_android.cc"
#undef ChromeMainDelegate
