/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHILEDGER_ATTESTATION_ATTESTATION_H_
#define HUHILEDGER_ATTESTATION_ATTESTATION_H_

#include <map>
#include <string>

#include "bat/ledger/ledger.h"

namespace ledger {
class LedgerImpl;

namespace attestation {

using StartCallback =
    std::function<void(const type::Result, const std::string&)>;

using ConfirmCallback =
    std::function<void(const type::Result)>;

class Attestation {
 public:
  explicit Attestation(LedgerImpl* ledger);
  virtual ~Attestation();

  virtual void Start(const std::string& payload, StartCallback callback) = 0;

  virtual void Confirm(
      const std::string& solution,
      ConfirmCallback callback) = 0;

 protected:
  LedgerImpl* ledger_;  // NOT OWNED
};

}  // namespace attestation
}  // namespace ledger
#endif  // HUHILEDGER_ATTESTATION_ATTESTATION_H_
