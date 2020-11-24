/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_HUHI_SHIELDS_COOKIE_PREF_SERVICE_FACTORY_H_
#define HUHI_BROWSER_HUHI_SHIELDS_COOKIE_PREF_SERVICE_FACTORY_H_

#include "base/memory/singleton.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

namespace huhi_shields {

class CookiePrefService;

class CookiePrefServiceFactory : public BrowserContextKeyedServiceFactory {
 public:
  static CookiePrefService* GetForBrowserContext(
      content::BrowserContext* context);

  static CookiePrefServiceFactory* GetInstance();

 private:
  friend struct base::DefaultSingletonTraits<CookiePrefServiceFactory>;

  CookiePrefServiceFactory();
  ~CookiePrefServiceFactory() override;

  // BrowserContextKeyedServiceFactory:
  KeyedService* BuildServiceInstanceFor(
      content::BrowserContext* profile) const override;

  bool ServiceIsCreatedWithBrowserContext() const override;

  DISALLOW_COPY_AND_ASSIGN(CookiePrefServiceFactory);
};

}  // namespace huhi_shields

#endif  // HUHI_BROWSER_HUHI_SHIELDS_COOKIE_PREF_SERVICE_FACTORY_H_
