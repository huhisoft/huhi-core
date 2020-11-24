/* Copyright 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_UTILITY_IMPORTER_HUHI_SAFARI_IMPORTER_H_
#define HUHI_UTILITY_IMPORTER_HUHI_SAFARI_IMPORTER_H_

#include "chrome/utility/importer/safari_importer.h"

class HuhiSafariImporter : public SafariImporter {
 public:
  using SafariImporter::SafariImporter;

  HuhiSafariImporter(const HuhiSafariImporter&) = delete;
  HuhiSafariImporter& operator=(const HuhiSafariImporter&) = delete;

 private:
  // SafariImporter overrides:
  void ImportHistory() override;

  ~HuhiSafariImporter() override;
};

#endif  // HUHI_UTILITY_IMPORTER_HUHI_SAFARI_IMPORTER_H_
