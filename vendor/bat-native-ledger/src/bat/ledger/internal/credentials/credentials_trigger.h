/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHILEDGER_CREDENTIALS_CREDENTIALS_TRIGGER_H_
#define HUHILEDGER_CREDENTIALS_CREDENTIALS_TRIGGER_H_

#include <vector>
#include <string>

#include "bat/ledger/ledger.h"

namespace ledger {
namespace credential {

struct CredentialsTrigger {
  CredentialsTrigger();
  CredentialsTrigger(const CredentialsTrigger& info);
  ~CredentialsTrigger();

  std::string id;
  type::CredsBatchType type;
  int size;
  std::vector<std::string> data;
};

}  // namespace credential
}  // namespace ledger

#endif  // HUHILEDGER_CREDENTIALS_CREDENTIALS_TRIGGER_H_
