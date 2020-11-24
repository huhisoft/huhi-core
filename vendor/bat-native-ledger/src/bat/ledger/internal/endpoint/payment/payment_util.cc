/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ledger/internal/endpoint/payment/payment_util.h"

#include "bat/ledger/ledger.h"

namespace ledger {
namespace endpoint {
namespace payment {

const char kDevelopment[] = "https://payment.rewards.huhi.software";
const char kStaging[] = "https://payment.rewards.huhisoft.com";
const char kProduction[] = "https://payment.rewards.huhisoft.com";

std::string GetServerUrl(const std::string& path) {
  DCHECK(!path.empty());

  std::string url;
  switch (ledger::_environment) {
    case type::Environment::DEVELOPMENT:
      url = kDevelopment;
      break;
    case type::Environment::STAGING:
      url = kStaging;
      break;
    case type::Environment::PRODUCTION:
      url = kProduction;
      break;
  }

  return url + path;
}

}  // namespace payment
}  // namespace endpoint
}  // namespace ledger
