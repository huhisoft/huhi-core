/* Copyright 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_P3A_HUHI_P3A_UTILS_H_
#define HUHI_COMPONENTS_P3A_HUHI_P3A_UTILS_H_

#include "base/metrics/histogram_functions.h"
#include "components/prefs/pref_service.h"

namespace huhi {

template<class Enumeration>
void RecordValueIfGreater(Enumeration value,
                          const char* hist_name,
                          const char* pref_name,
                          PrefService* local_state) {
  // May be null in tests.
  if (!local_state) {
    return;
  }
  const int usage_int = static_cast<int>(value);
  int last_value = local_state->GetInteger(pref_name);
  if (last_value < usage_int) {
    base::UmaHistogramExactLinear(hist_name, usage_int,
                                  static_cast<int>(Enumeration::kSize));
    local_state->SetInteger(pref_name, usage_int);
  }
}

}  // namespace huhi

#endif  // HUHI_COMPONENTS_P3A_HUHI_P3A_UTILS_H_
