/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHILEDGER_COMMON_BROTLI_UTIL_H_
#define HUHILEDGER_COMMON_BROTLI_UTIL_H_

#include <string>

#include "base/strings/string_piece.h"

namespace ledger {
namespace util {

bool DecodeBrotliString(
    base::StringPiece input,
    size_t uncompressed_size,
    std::string* output);

bool DecodeBrotliStringWithBuffer(
    base::StringPiece input,
    size_t buffer_size,
    std::string* output);

}  // namespace util
}  // namespace ledger

#endif  // HUHILEDGER_COMMON_BROTLI_UTIL_H_
