/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHILEDGER_COMMON_TIME_UTIL_H_
#define HUHILEDGER_COMMON_TIME_UTIL_H_

#include <stdint.h>

#include <string>

#include "base/time/time.h"
#include "bat/ledger/mojom_structs.h"

namespace ledger {
namespace util {

type::ActivityMonth GetCurrentMonth();

type::ActivityMonth GetMonth(const base::Time& time);

uint32_t GetCurrentYear();

uint32_t GetYear(const base::Time& time);

uint64_t GetCurrentTimeStamp();

base::TimeDelta GetRandomizedDelay(base::TimeDelta delay);

base::TimeDelta GetRandomizedDelayWithBackoff(
    base::TimeDelta delay,
    base::TimeDelta max_delay,
    int backoff_count);

}  // namespace util
}  // namespace ledger

#endif  // HUHILEDGER_COMMON_TIME_UTIL_H_
