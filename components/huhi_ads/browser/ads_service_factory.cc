/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/components/huhi_ads/browser/ads_service_factory.h"

#include <memory>

#include "base/time/time.h"
#include "huhi/browser/profiles/profile_util.h"
#include "huhi/components/huhi_ads/browser/ads_service.h"
#include "huhi/components/huhi_ads/browser/buildflags/buildflags.h"
#include "huhi/components/huhi_ads/common/pref_names.h"
#include "chrome/browser/profiles/incognito_helpers.h"
#include "chrome/browser/profiles/profile.h"
#include "components/keyed_service/content/browser_context_dependency_manager.h"
#include "components/pref_registry/pref_registry_syncable.h"
#include "components/prefs/pref_store.h"

#if BUILDFLAG(HUHI_ADS_ENABLED)
#include "huhi/browser/huhi_rewards/rewards_service_factory.h"
#include "huhi/components/huhi_ads/browser/ads_service_impl.h"
#include "chrome/browser/dom_distiller/dom_distiller_service_factory.h"
#include "chrome/browser/notifications/notification_display_service_factory.h"
#endif

class PrefStore;

namespace huhi_ads {

// static
AdsService* AdsServiceFactory::GetForProfile(
    Profile* profile) {
  if (profile->IsOffTheRecord() || huhi::IsTorProfile(profile)) {
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

void AdsServiceFactory::RegisterProfilePrefs(
    user_prefs::PrefRegistrySyncable* registry) {
  registry->RegisterIntegerPref(prefs::kVersion, prefs::kCurrentVersionNumber);

  registry->RegisterIntegerPref(
      prefs::kSupportedCountryCodesLastSchemaVersion, 0);

  registry->RegisterIntegerPref(prefs::kSupportedCountryCodesSchemaVersion,
      prefs::kSupportedCountryCodesSchemaVersionNumber);

  registry->RegisterBooleanPref(prefs::kEnabled, false);

  registry->RegisterBooleanPref(prefs::kShouldAllowAdConversionTracking, true);

  registry->RegisterUint64Pref(prefs::kAdsPerHour, 2);
  registry->RegisterUint64Pref(prefs::kAdsPerDay, 20);

  registry->RegisterBooleanPref(prefs::kShouldAllowAdsSubdivisionTargeting,
      false);
  registry->RegisterStringPref(prefs::kAdsSubdivisionTargetingCode, "AUTO");
  registry->RegisterStringPref(
      prefs::kAutomaticallyDetectedAdsSubdivisionTargetingCode, "");

  registry->RegisterIntegerPref(prefs::kIdleThreshold, 15);
  registry->RegisterBooleanPref(prefs::kAdsWereDisabled, false);
  registry->RegisterBooleanPref(prefs::kHasAdsP3AState, false);

  registry->RegisterBooleanPref(prefs::kShouldShowMyFirstAdNotification, true);

  registry->RegisterBooleanPref(prefs::kShouldShowOnboarding, true);
  registry->RegisterUint64Pref(prefs::kOnboardingTimestamp, 0);
}

}  // namespace huhi_ads
