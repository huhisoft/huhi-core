/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHILEDGER_COMMON_REQUEST_UTIL_H_
#define HUHILEDGER_COMMON_REQUEST_UTIL_H_

#include <map>
#include <string>
#include <vector>

namespace ledger {
namespace util {

std::map<std::string, std::string> GetSignHeaders(
    const std::string& url,
    const std::string& body,
    const std::string& key_id,
    const std::vector<uint8_t>& private_key,
    const bool idempotency_key = false);

std::vector<std::string> BuildSignHeaders(
    const std::string& url,
    const std::string& body,
    const std::string& key_id,
    const std::vector<uint8_t>& private_key);

}  // namespace util
}  // namespace ledger

#endif  // HUHILEDGER_COMMON_REQUEST_UTIL_H_
