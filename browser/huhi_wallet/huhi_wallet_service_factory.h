/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_HUHI_WALLET_HUHI_WALLET_SERVICE_FACTORY_H_
#define HUHI_BROWSER_HUHI_WALLET_HUHI_WALLET_SERVICE_FACTORY_H_

#include "base/memory/singleton.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

class HuhiWalletService;
class Profile;

class HuhiWalletServiceFactory : public BrowserContextKeyedServiceFactory {
 public:
  static HuhiWalletService* GetForProfile(Profile* profile);
  static HuhiWalletServiceFactory* GetInstance();

 private:
  friend struct base::DefaultSingletonTraits<HuhiWalletServiceFactory>;

  HuhiWalletServiceFactory();
  ~HuhiWalletServiceFactory() override;

  KeyedService* BuildServiceInstanceFor(
      content::BrowserContext* context) const override;
  content::BrowserContext* GetBrowserContextToUse(
      content::BrowserContext* context) const override;

  DISALLOW_COPY_AND_ASSIGN(HuhiWalletServiceFactory);
};

#endif  // HUHI_BROWSER_HUHI_WALLET_HUHI_WALLET_SERVICE_FACTORY_H_
