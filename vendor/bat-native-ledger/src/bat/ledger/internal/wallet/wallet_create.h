/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHILEDGER_WALLET_WALLET_CREATE_H_
#define HUHILEDGER_WALLET_WALLET_CREATE_H_

#include <stdint.h>

#include <memory>
#include <string>

#include "bat/ledger/internal/endpoint/promotion/promotion_server.h"
#include "bat/ledger/ledger.h"

namespace ledger {
class LedgerImpl;

namespace wallet {

class WalletCreate {
 public:
  explicit WalletCreate(LedgerImpl* ledger);
  ~WalletCreate();

  void Start(ledger::ResultCallback callback);

 private:
  void OnCreate(
      const type::Result result,
      const std::string& payment_id,
      ledger::ResultCallback callback);

  LedgerImpl* ledger_;  // NOT OWNED
  std::unique_ptr<endpoint::PromotionServer> promotion_server_;
};

}  // namespace wallet
}  // namespace ledger
#endif  // HUHILEDGER_WALLET_WALLET_CREATE_H_
