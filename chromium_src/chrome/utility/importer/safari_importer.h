/* Copyright 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_CHROME_UTILITY_IMPORTER_SAFARI_IMPORTER_H_
#define HUHI_CHROMIUM_SRC_CHROME_UTILITY_IMPORTER_SAFARI_IMPORTER_H_

#define HUHI_SAFARI_IMPORTER_H \
  friend class HuhiSafariImporter;

#define ImportHistory virtual ImportHistory

#include "../../../../../chrome/utility/importer/safari_importer.h"

#undef HUHI_SAFARI_IMPORTER_H
#undef ImportHistory

#endif  // HUHI_CHROMIUM_SRC_CHROME_UTILITY_IMPORTER_SAFARI_IMPORTER_H_
