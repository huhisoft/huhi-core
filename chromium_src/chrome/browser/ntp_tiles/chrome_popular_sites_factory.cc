/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/browser/ntp_tiles/chrome_popular_sites_factory.h"

#include "huhi/components/ntp_tiles/huhi_popular_sites_impl.h"

#define PopularSitesImpl HuhiPopularSitesImpl
#include "../../../../../chrome/browser/ntp_tiles/chrome_popular_sites_factory.cc"  // NOLINT
#undef PopularSitesImpl
