/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHILEDGER_ENDPOINT_PROMOTION_POST_DEVICECEHCK_POST_DEVICECEHCK_H_
#define HUHILEDGER_ENDPOINT_PROMOTION_POST_DEVICECEHCK_POST_DEVICECEHCK_H_

#include <string>

#include "bat/ledger/ledger.h"

// POST /v1/devicecheck/attestations
//
// Request body:
// {
//   "paymentId": "83b3b77b-e7c3-455b-adda-e476fa0656d2"
//   "publicKeyHash": "f3f2f3ffqdwfqwfwqfd"
// }
//
// Success code:
// HTTP_OK (200)
//
// Error codes:
// HTTP_BAD_REQUEST (400)
// HTTP_UNAUTHORIZED (401)
//
// Response body:
// {
//   "nonce": "c4645786-052f-402f-8593-56af2f7a21ce"
// }

namespace ledger {
class LedgerImpl;

namespace endpoint {
namespace promotion {

using PostDevicecheckCallback = std::function<void(
    const type::Result result,
    const std::string& nonce)>;

class PostDevicecheck {
 public:
  explicit PostDevicecheck(LedgerImpl* ledger);
  ~PostDevicecheck();

  void Request(const std::string& key, PostDevicecheckCallback callback);

 private:
  std::string GetUrl();

  std::string GeneratePayload(const std::string& key);

  type::Result CheckStatusCode(const int status_code);

  type::Result ParseBody(
      const std::string& body,
      std::string* nonce);

  void OnRequest(
      const type::UrlResponse& response,
      PostDevicecheckCallback callback);

  LedgerImpl* ledger_;  // NOT OWNED
};

}  // namespace promotion
}  // namespace endpoint
}  // namespace ledger

#endif  // HUHILEDGER_ENDPOINT_PROMOTION_POST_DEVICECEHCK_POST_DEVICECEHCK_H_
