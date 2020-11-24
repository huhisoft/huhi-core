/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_HUHI_REFERRALS_HUHI_REFERRALS_SERVICE_FACTORY_H_
#define HUHI_BROWSER_HUHI_REFERRALS_HUHI_REFERRALS_SERVICE_FACTORY_H_

#include <memory>

#include "base/memory/singleton.h"
#include "huhi/common/pref_names.h"
#include "components/prefs/pref_service.h"

namespace huhi {
class HuhiReferralsService;

class HuhiReferralsServiceFactory {
 public:
  static std::unique_ptr<HuhiReferralsService> GetForPrefs(
        PrefService* pref_service);
  static HuhiReferralsServiceFactory* GetInstance();

 private:
  friend struct base::DefaultSingletonTraits<HuhiReferralsServiceFactory>;

  HuhiReferralsServiceFactory();
  ~HuhiReferralsServiceFactory();

  DISALLOW_COPY_AND_ASSIGN(HuhiReferralsServiceFactory);
};

}  // namespace huhi

#endif  // HUHI_BROWSER_HUHI_REFERRALS_HUHI_REFERRALS_SERVICE_FACTORY_H_
