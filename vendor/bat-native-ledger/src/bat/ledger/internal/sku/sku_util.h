/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHILEDGER_SKU_SKU_UTIL_H_
#define HUHILEDGER_SKU_SKU_UTIL_H_

#include <string>
#include <vector>

#include "bat/ledger/mojom_structs.h"

namespace ledger {
namespace sku {

std::string GetHuhiDestination(const std::string& wallet_type);

std::string GetAnonCardDestination();

std::string GetUpholdDestination();

}  // namespace sku
}  // namespace ledger

#endif  // HUHILEDGER_SKU_SKU_UTIL_H_
