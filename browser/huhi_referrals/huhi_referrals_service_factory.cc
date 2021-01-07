/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/huhi_referrals/huhi_referrals_service_factory.h"

#include <memory>

#include "huhi/components/huhi_referrals/browser/huhi_referrals_service.h"
#include "huhi/components/huhi_stats/browser/huhi_stats_updater_util.h"

namespace huhi {

// static
std::unique_ptr<HuhiReferralsService>
  HuhiReferralsServiceFactory::GetForPrefs(
    PrefService* pref_service) {
  return std::make_unique<HuhiReferralsService>(
      pref_service,
      huhi_stats::GetAPIKey(),
      huhi_stats::GetPlatformIdentifier());
}

// static
HuhiReferralsServiceFactory* HuhiReferralsServiceFactory::GetInstance() {
  return base::Singleton<HuhiReferralsServiceFactory>::get();
}

HuhiReferralsServiceFactory::HuhiReferralsServiceFactory() {}

HuhiReferralsServiceFactory::~HuhiReferralsServiceFactory() {}

}  // namespace huhi
