/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_HUHI_REWARDS_REWARDS_SERVICE_FACTORY_H_
#define HUHI_BROWSER_HUHI_REWARDS_REWARDS_SERVICE_FACTORY_H_

#include "base/memory/singleton.h"
#include "huhi/components/huhi_rewards/browser/rewards_service.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"

class Profile;

namespace huhi_rewards {
class RewardsService;

// Singleton that owns all RewardsService and associates them with Profiles.
class RewardsServiceFactory : public BrowserContextKeyedServiceFactory,
                              public content::NotificationObserver {
 public:
  RewardsServiceFactory(const RewardsServiceFactory&) = delete;
  RewardsServiceFactory& operator=(const RewardsServiceFactory&) = delete;

  static huhi_rewards::RewardsService* GetForProfile(Profile* profile);

  static RewardsServiceFactory* GetInstance();

  static void SetServiceForTesting(RewardsService* service);

 private:
  friend struct base::DefaultSingletonTraits<RewardsServiceFactory>;

  RewardsServiceFactory();
  ~RewardsServiceFactory() override;

  // BrowserContextKeyedServiceFactory:
  KeyedService* BuildServiceInstanceFor(
      content::BrowserContext* context) const override;
  bool ServiceIsNULLWhileTesting() const override;

  // content::NotificationObserver:
  void Observe(int type,
               const content::NotificationSource& source,
               const content::NotificationDetails& details) override;

  content::NotificationRegistrar registrar_;
};

}  // namespace huhi_rewards

#endif  // HUHI_BROWSER_HUHI_REWARDS_REWARDS_SERVICE_FACTORY_H_
