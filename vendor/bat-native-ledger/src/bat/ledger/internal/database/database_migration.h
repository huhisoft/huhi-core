/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHILEDGER_DATABASE_DATABASE_MIGRATION_H_
#define HUHILEDGER_DATABASE_DATABASE_MIGRATION_H_

#include <memory>
#include <string>

#include "bat/ledger/ledger.h"

namespace ledger {
class LedgerImpl;

namespace database {

class DatabaseMigration {
 public:
  explicit DatabaseMigration(LedgerImpl* ledger);
  ~DatabaseMigration();

  void Start(
      const uint32_t table_version,
      ledger::ResultCallback callback);

 private:
  void GenerateCommand(
      type::DBTransaction* transaction,
      const std::string& query);

  LedgerImpl* ledger_;  // NOT OWNED
};

}  // namespace database
}  // namespace ledger
#endif  // HUHILEDGER_DATABASE_DATABASE_MIGRATION_H_
