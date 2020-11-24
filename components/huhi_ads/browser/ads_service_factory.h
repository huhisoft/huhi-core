/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_ADS_BROWSER_ADS_SERVICE_FACTORY_H_
#define HUHI_COMPONENTS_HUHI_ADS_BROWSER_ADS_SERVICE_FACTORY_H_

#include "base/memory/singleton.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

class Profile;

namespace huhi_ads {
class AdsService;

// Singleton that owns all AdsService and associates them with Profiles.
class AdsServiceFactory : public BrowserContextKeyedServiceFactory {
 public:
  AdsServiceFactory(const AdsServiceFactory&) = delete;
  AdsServiceFactory& operator=(const AdsServiceFactory&) = delete;

  static huhi_ads::AdsService* GetForProfile(Profile* profile);

  static AdsServiceFactory* GetInstance();

  void RegisterProfilePrefs(
      user_prefs::PrefRegistrySyncable* registry) override;

 private:
  friend struct base::DefaultSingletonTraits<AdsServiceFactory>;

  AdsServiceFactory();
  ~AdsServiceFactory() override;

  // BrowserContextKeyedServiceFactory:
  KeyedService* BuildServiceInstanceFor(
      content::BrowserContext* context) const override;
  bool ServiceIsNULLWhileTesting() const override;
};

}  // namespace huhi_ads

#endif  // HUHI_COMPONENTS_HUHI_ADS_BROWSER_ADS_SERVICE_FACTORY_H_
