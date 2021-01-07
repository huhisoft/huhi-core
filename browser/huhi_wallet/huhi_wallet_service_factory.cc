/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/huhi_wallet/huhi_wallet_service_factory.h"

#include <memory>

#include "huhi/browser/huhi_wallet/huhi_wallet_delegate_impl.h"
#include "huhi/components/huhi_wallet/huhi_wallet_service.h"
#include "chrome/browser/profiles/incognito_helpers.h"
#include "chrome/browser/profiles/profile.h"
#include "components/keyed_service/content/browser_context_dependency_manager.h"
#include "extensions/browser/extension_registry_factory.h"
#include "extensions/browser/extension_system.h"
#include "extensions/browser/extension_system_provider.h"
#include "extensions/browser/extensions_browser_client.h"

// static
HuhiWalletServiceFactory* HuhiWalletServiceFactory::GetInstance() {
  return base::Singleton<HuhiWalletServiceFactory>::get();
}

// static
HuhiWalletService* HuhiWalletServiceFactory::GetForProfile(Profile* profile) {
  return static_cast<HuhiWalletService*>(
      GetInstance()->GetServiceForBrowserContext(profile, true));
}

HuhiWalletServiceFactory::HuhiWalletServiceFactory()
    : BrowserContextKeyedServiceFactory(
          "HuhiWalletService",
          BrowserContextDependencyManager::GetInstance()) {
  DependsOn(extensions::ExtensionRegistryFactory::GetInstance());
  DependsOn(
      extensions::ExtensionsBrowserClient::Get()->GetExtensionSystemFactory());
}

HuhiWalletServiceFactory::~HuhiWalletServiceFactory() {}

KeyedService* HuhiWalletServiceFactory::BuildServiceInstanceFor(
    content::BrowserContext* context) const {
  return new HuhiWalletService(Profile::FromBrowserContext(context),
                                std::make_unique<HuhiWalletDelegateImpl>());
}

content::BrowserContext* HuhiWalletServiceFactory::GetBrowserContextToUse(
    content::BrowserContext* context) const {
  return chrome::GetBrowserContextRedirectedInIncognito(context);
}
