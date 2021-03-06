/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "bat/ledger/internal/endpoint/rewards/rewards_util.h"

#include "bat/ledger/ledger.h"

namespace ledger {
namespace endpoint {
namespace rewards {

const char kDevelopment[] = "https://rewards-dev.huhi.software";
const char kStaging[] = "https://rewards-stg.huhisoft.com";
const char kProduction[] = "https://rewards.huhisoft.com";

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

}  // namespace rewards
}  // namespace endpoint
}  // namespace ledger
