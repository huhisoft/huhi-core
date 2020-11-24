/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
+ * This Source Code Form is subject to the terms of the Huhi Software
+ * License, v. 2.0. If a copy of the MPL was not distributed with this file,
+ * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/huhi_wallet/huhi_wallet_delegate_impl.h"

#include "huhi/browser/extensions/huhi_component_loader.h"
#include "chrome/browser/extensions/extension_service.h"
#include "content/public/browser/browser_context.h"
#include "extensions/browser/extension_system.h"

HuhiWalletDelegateImpl::~HuhiWalletDelegateImpl() {
}

void HuhiWalletDelegateImpl::LoadCryptoWalletsExtension(
    content::BrowserContext* context) {
  extensions::ExtensionService* service =
      extensions::ExtensionSystem::Get(context)->extension_service();
  if (service) {
    extensions::ComponentLoader* loader = service->component_loader();
    static_cast<extensions::HuhiComponentLoader*>(loader)->
        AddEthereumRemoteClientExtension();
  }
}
