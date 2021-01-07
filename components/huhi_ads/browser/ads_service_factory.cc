/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/components/huhi_ads/browser/ads_service_factory.h"

#include <memory>

#include "base/time/time.h"
#include "huhi/browser/profiles/profile_util.h"
#include "huhi/components/huhi_ads/browser/ads_service.h"
#include "huhi/components/huhi_ads/browser/buildflags/buildflags.h"
#include "chrome/browser/profiles/incognito_helpers.h"
#include "chrome/browser/profiles/profile.h"
#include "components/keyed_service/content/browser_context_dependency_manager.h"

#if BUILDFLAG(HUHI_ADS_ENABLED)
#include "huhi/browser/huhi_rewards/rewards_service_factory.h"
#include "huhi/components/huhi_ads/browser/ads_service_impl.h"
#include "chrome/browser/dom_distiller/dom_distiller_service_factory.h"
#include "chrome/browser/notifications/notification_display_service_factory.h"
#endif

namespace huhi_ads {

// static
AdsService* AdsServiceFactory::GetForProfile(
    Profile* profile) {
  if (!huhi::IsRegularProfile(profile)) {
    return nullptr;
  }

  return static_cast<AdsService*>(
      GetInstance()->GetServiceForBrowserContext(profile, true));
}

// static
AdsServiceFactory* AdsServiceFactory::GetInstance() {
  return base::Singleton<AdsServiceFactory>::get();
}

AdsServiceFactory::AdsServiceFactory()
    : BrowserContextKeyedServiceFactory(
          "AdsService",
          BrowserContextDependencyManager::GetInstance()) {
#if BUILDFLAG(HUHI_ADS_ENABLED)
  DependsOn(NotificationDisplayServiceFactory::GetInstance());
  DependsOn(dom_distiller::DomDistillerServiceFactory::GetInstance());
  DependsOn(huhi_rewards::RewardsServiceFactory::GetInstance());
#endif
}

AdsServiceFactory::~AdsServiceFactory() {}

KeyedService* AdsServiceFactory::BuildServiceInstanceFor(
    content::BrowserContext* context) const {
#if BUILDFLAG(HUHI_ADS_ENABLED)
  std::unique_ptr<AdsServiceImpl> ads_service(
      new AdsServiceImpl(Profile::FromBrowserContext(context)));
  return ads_service.release();
#else
  return nullptr;
#endif
}

bool AdsServiceFactory::ServiceIsNULLWhileTesting() const {
  return false;
}

}  // namespace huhi_ads
