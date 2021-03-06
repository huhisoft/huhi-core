/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHILEDGER_DATABASE_DATABASE_RECURRING_TIP_H_
#define HUHILEDGER_DATABASE_DATABASE_RECURRING_TIP_H_

#include <string>

#include "bat/ledger/internal/database/database_table.h"

namespace ledger {
namespace database {

class DatabaseRecurringTip: public DatabaseTable {
 public:
  explicit DatabaseRecurringTip(LedgerImpl* ledger);
  ~DatabaseRecurringTip() override;

  void InsertOrUpdate(
      type::RecurringTipPtr info,
      ledger::ResultCallback callback);

  void GetAllRecords(ledger::PublisherInfoListCallback callback);

  void DeleteRecord(
      const std::string& publisher_key,
      ledger::ResultCallback callback);

 private:
  void OnGetAllRecords(
      type::DBCommandResponsePtr response,
      ledger::PublisherInfoListCallback callback);
};

}  // namespace database
}  // namespace ledger

#endif  // HUHILEDGER_DATABASE_DATABASE_RECURRING_TIP_H_
