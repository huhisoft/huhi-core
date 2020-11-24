/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/components/huhi_ads/browser/ads_service.h"

namespace huhi_ads {

AdsService::AdsService() = default;

AdsService::~AdsService() = default;

void AdsService::AddObserver(
    AdsServiceObserver* observer) {
  observers_.AddObserver(observer);
}

void AdsService::RemoveObserver(
    AdsServiceObserver* observer) {
  observers_.RemoveObserver(observer);
}

}  // namespace huhi_ads
