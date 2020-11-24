/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_L10N_COMMON_LOCALE_UTIL_H_
#define HUHI_COMPONENTS_L10N_COMMON_LOCALE_UTIL_H_

#include <string>

namespace huhi_l10n {

std::string GetLanguageCode(
    const std::string& locale);

std::string GetCountryCode(
    const std::string& locale);

}  // namespace huhi_l10n

#endif  // HUHI_COMPONENTS_L10N_COMMON_LOCALE_UTIL_H_
