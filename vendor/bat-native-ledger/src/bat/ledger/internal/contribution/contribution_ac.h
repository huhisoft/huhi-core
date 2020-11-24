/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHILEDGER_CONTRIBUTION_CONTRIBUTION_AC_H_
#define HUHILEDGER_CONTRIBUTION_CONTRIBUTION_AC_H_

#include "bat/ledger/ledger.h"

namespace ledger {
class LedgerImpl;

namespace contribution {

class ContributionAC {
 public:
  explicit ContributionAC(LedgerImpl* ledger);

  ~ContributionAC();

  void Process(const uint64_t reconcile_stamp);

 private:
  void PreparePublisherList(type::PublisherInfoList list);

  void QueueSaved(const type::Result result);

  LedgerImpl* ledger_;  // NOT OWNED
};

}  // namespace contribution
}  // namespace ledger
#endif  // HUHILEDGER_CONTRIBUTION_CONTRIBUTION_AC_H_
