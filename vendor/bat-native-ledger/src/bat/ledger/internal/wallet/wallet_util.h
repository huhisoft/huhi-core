/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHILEDGER_WALLET_WALLET_UTIL_H_
#define HUHILEDGER_WALLET_WALLET_UTIL_H_

#include <map>
#include <string>

#include "bat/ledger/ledger.h"

namespace ledger {
namespace wallet {

type::ExternalWalletPtr GetWallet(
    const std::string& wallet_type,
    std::map<std::string, type::ExternalWalletPtr> wallets);

type::ExternalWalletPtr ResetWallet(type::ExternalWalletPtr wallet);

}  // namespace wallet
}  // namespace ledger

#endif  // HUHILEDGER_WALLET_WALLET_UTIL_H_
