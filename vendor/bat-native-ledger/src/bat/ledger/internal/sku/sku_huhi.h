/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHILEDGER_SKU_HUHI_H_
#define HUHILEDGER_SKU_HUHI_H_

#include <memory>
#include <string>
#include <vector>

#include "bat/ledger/internal/sku/sku.h"
#include "bat/ledger/internal/sku/sku_common.h"
#include "bat/ledger/ledger.h"

namespace ledger {
class LedgerImpl;

namespace sku {

class SKUHuhi : public SKU  {
 public:
  explicit SKUHuhi(LedgerImpl* ledger);
  ~SKUHuhi() override;

  void Process(
      const std::vector<type::SKUOrderItem>& items,
      type::ExternalWalletPtr wallet,
      ledger::SKUOrderCallback callback,
      const std::string& contribution_id = "") override;

  void Retry(
      const std::string& order_id,
      type::ExternalWalletPtr wallet,
      ledger::SKUOrderCallback callback) override;

 private:
  void OrderCreated(
      const type::Result result,
      const std::string& order_id,
      const type::ExternalWallet& wallet,
      const std::string& contribution_id,
      ledger::SKUOrderCallback callback);

  void ContributionIdSaved(
      const type::Result result,
      const std::string& order_id,
      const type::ExternalWallet& wallet,
      ledger::SKUOrderCallback callback);

  void CreateTransaction(
      type::SKUOrderPtr order,
      const type::ExternalWallet& wallet,
      ledger::SKUOrderCallback callback);

  void OnOrder(
      type::SKUOrderPtr order,
      const type::ExternalWallet& wallet,
      ledger::SKUOrderCallback callback);

  LedgerImpl* ledger_;  // NOT OWNED
  std::unique_ptr<SKUCommon> common_;
};

}  // namespace sku
}  // namespace ledger

#endif  // HUHILEDGER_SKU_HUHI_H_
