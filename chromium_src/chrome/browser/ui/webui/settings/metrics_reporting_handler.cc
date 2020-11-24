/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#if defined(HUHI_CHROMIUM_BUILD)
#define GOOGLE_CHROME_BUILD
#endif

#include "../../../../../../../chrome/browser/ui/webui/settings/metrics_reporting_handler.cc"

#if defined(HUHI_CHROMIUM_BUILD)
#undef GOOGLE_CHROME_BUILD
#endif
