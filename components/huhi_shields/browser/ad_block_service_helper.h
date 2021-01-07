/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_SHIELDS_BROWSER_AD_BLOCK_SERVICE_HELPER_H_
#define HUHI_COMPONENTS_HUHI_SHIELDS_BROWSER_AD_BLOCK_SERVICE_HELPER_H_

#include <stdint.h>
#include <string>
#include <vector>

#include "base/values.h"
#include "huhi/vendor/adblock_rust_ffi/src/wrapper.hpp"

namespace huhi_shields {

std::vector<adblock::FilterList>::const_iterator FindAdBlockFilterListByUUID(
    const std::vector<adblock::FilterList>& region_lists,
    const std::string& uuid);
std::vector<adblock::FilterList>::const_iterator FindAdBlockFilterListByLocale(
    const std::vector<adblock::FilterList>& region_lists,
    const std::string& locale);

std::vector<adblock::FilterList> RegionalCatalogFromJSON(
    const std::string& catalog_json);

void MergeResourcesInto(base::Value from, base::Value* into, bool force_hide);

}  // namespace huhi_shields

#endif  // HUHI_COMPONENTS_HUHI_SHIELDS_BROWSER_AD_BLOCK_SERVICE_HELPER_H_
