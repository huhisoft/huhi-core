/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/translate/buildflags/buildflags.h"

#if BUILDFLAG(ENABLE_HUHI_TRANSLATE_GO)
#include "../../../../../../components/translate/core/browser/translate_url_fetcher.cc"
#endif
