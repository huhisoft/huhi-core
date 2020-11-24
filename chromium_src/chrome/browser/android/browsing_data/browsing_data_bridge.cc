/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#define HUHI_CLEAR_BROWSING_DATA                          \
  remove_mask |= BrowsingDataRemover::DATA_TYPE_DOWNLOADS; \
  break;                                                   \

#include "../../../../../../chrome/browser/android/browsing_data/browsing_data_bridge.cc"
#undef HUHI_CLEAR_BROWSING_DATA
