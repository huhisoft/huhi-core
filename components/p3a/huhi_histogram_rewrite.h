/* Copyright 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_P3A_HUHI_HISTOGRAM_REWRITE_H_
#define HUHI_COMPONENTS_P3A_HUHI_HISTOGRAM_REWRITE_H_

namespace huhi {

// Set callbacks for existing Chromium histograms that will be braveized,
// i.e. reemitted using a different name and custom buckets.
void SetupHistogramsHuhiization();

}  // namespace huhi

#endif  // HUHI_COMPONENTS_P3A_HUHI_HISTOGRAM_REWRITE_H_
