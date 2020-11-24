/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHILEDGER_PROMOTION_PROMOTION_UTIL_H_
#define HUHILEDGER_PROMOTION_PROMOTION_UTIL_H_

#include <memory>
#include <string>
#include <vector>

#include "bat/ledger/mojom_structs.h"

namespace ledger {
namespace promotion {

std::string ParseOSToString(type::OperatingSystem os);

std::string ParseClientInfoToString(type::ClientInfoPtr info);

type::PromotionType ConvertStringToPromotionType(const std::string& type);

type::ReportType ConvertPromotionTypeToReportType(
    const type::PromotionType type);

std::vector<type::PromotionType> GetEligiblePromotions();

}  // namespace promotion
}  // namespace ledger

#endif  // HUHILEDGER_PROMOTION_PROMOTION_UTIL_H_
