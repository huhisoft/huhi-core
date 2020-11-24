/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHILEDGER_PROPERTIES_WALLET_INFO_PROPERTIES_H_
#define HUHILEDGER_PROPERTIES_WALLET_INFO_PROPERTIES_H_

#include <stdint.h>
#include <string>
#include <vector>

namespace ledger {

struct WalletInfoProperties {
  WalletInfoProperties();
  WalletInfoProperties(
      const WalletInfoProperties& properties);
  ~WalletInfoProperties();

  bool operator==(
      const WalletInfoProperties& rhs) const;

  bool operator!=(
      const WalletInfoProperties& rhs) const;

  std::string payment_id;
  std::string address_card_id;
  std::vector<uint8_t> key_info_seed;
};

}  // namespace ledger

#endif  // HUHILEDGER_PROPERTIES_WALLET_INFO_PROPERTIES_H_
