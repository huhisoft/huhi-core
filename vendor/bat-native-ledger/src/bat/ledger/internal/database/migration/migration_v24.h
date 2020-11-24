/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHILEDGER_DATABASE_MIGRATION_MIGRATION_V24_H_
#define HUHILEDGER_DATABASE_MIGRATION_MIGRATION_V24_H_

namespace ledger {
namespace database {
namespace migration {

const char v24[] = R"(
  ALTER TABLE contribution_queue ADD completed_at TIMESTAMP NOT NULL DEFAULT 0;
)";

}  // namespace migration
}  // namespace database
}  // namespace ledger

#endif  // HUHILEDGER_DATABASE_MIGRATION_MIGRATION_V24_H_
