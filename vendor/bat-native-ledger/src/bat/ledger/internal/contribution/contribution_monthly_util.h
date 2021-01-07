/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHILEDGER_CONTRIBUTION_CONTRIBUTION_MONTHLY_UTIL_H_
#define HUHILEDGER_CONTRIBUTION_CONTRIBUTION_MONTHLY_UTIL_H_

#include "base/values.h"
#include "bat/ledger/mojom_structs.h"

namespace ledger {
class LedgerImpl;

namespace contribution {

double GetTotalFromVerifiedTips(
    const type::PublisherInfoList& publisher_list);

}  // namespace contribution
}  // namespace ledger

#endif  // HUHILEDGER_CONTRIBUTION_CONTRIBUTION_MONTHLY_UTIL_H_
