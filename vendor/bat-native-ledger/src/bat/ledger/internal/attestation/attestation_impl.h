/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHILEDGER_ATTESTATION_ATTESTATION_IMPL_H_
#define HUHILEDGER_ATTESTATION_ATTESTATION_IMPL_H_

#include <memory>
#include <string>

#include "bat/ledger/internal/attestation/attestation.h"

namespace ledger {
class LedgerImpl;

namespace attestation {

class AttestationDesktop;
class AttestationAndroid;
class AttestationIOS;

class AttestationImpl : public Attestation {
 public:
  explicit AttestationImpl(LedgerImpl* ledger);
  ~AttestationImpl() override;

  void Start(const std::string& payload, StartCallback callback) override;

  void Confirm(
      const std::string& solution,
      ConfirmCallback callback) override;

 private:
  std::unique_ptr<Attestation> platform_instance_;
};

}  // namespace attestation
}  // namespace ledger
#endif  // HUHILEDGER_ATTESTATION_ATTESTATION_IMPL_H_
