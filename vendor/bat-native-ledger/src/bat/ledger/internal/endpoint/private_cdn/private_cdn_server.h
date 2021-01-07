/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHILEDGER_ENDPOINT_PRIVATE_CDN_PRIVATE_CDN_SERVER_H_
#define HUHILEDGER_ENDPOINT_PRIVATE_CDN_PRIVATE_CDN_SERVER_H_

#include <memory>

#include "bat/ledger/ledger.h"
#include "bat/ledger/internal/endpoint/private_cdn/get_publisher/get_publisher.h"

namespace ledger {
class LedgerImpl;

namespace endpoint {

class PrivateCDNServer {
 public:
  explicit PrivateCDNServer(LedgerImpl* ledger);
  ~PrivateCDNServer();

  private_cdn::GetPublisher* get_publisher() const;

 private:
  std::unique_ptr<private_cdn::GetPublisher> get_publisher_;
};

}  // namespace endpoint
}  // namespace ledger

#endif  // HUHILEDGER_ENDPOINT_PRIVATE_CDN_PRIVATE_CDN_SERVER_H_
