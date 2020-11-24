/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHILEDGER_PROPERTIES_CLIENT_PROPERTIES_H_
#define HUHILEDGER_PROPERTIES_CLIENT_PROPERTIES_H_

#include <stdint.h>
#include <map>
#include <string>

#include "bat/ledger/internal/legacy/wallet_info_properties.h"
#include "bat/ledger/mojom_structs.h"

namespace ledger {

struct ClientProperties {
  ClientProperties();
  ClientProperties(
      const ClientProperties& properties);
  ~ClientProperties();

  bool operator==(
      const ClientProperties& rhs) const;

  bool operator!=(
      const ClientProperties& rhs) const;

  WalletInfoProperties wallet_info;
  uint64_t boot_timestamp;
  uint64_t reconcile_timestamp;
  double fee_amount;
  bool user_changed_fee;
  bool auto_contribute;
  bool rewards_enabled;
  std::map<std::string, bool> inline_tips;
};

}  // namespace ledger

#endif  // HUHILEDGER_PROPERTIES_CLIENT_PROPERTIES_H_
