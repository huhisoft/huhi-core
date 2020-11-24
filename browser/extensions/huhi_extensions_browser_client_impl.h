/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_EXTENSIONS_HUHI_EXTENSIONS_BROWSER_CLIENT_IMPL_H_
#define HUHI_BROWSER_EXTENSIONS_HUHI_EXTENSIONS_BROWSER_CLIENT_IMPL_H_

#include "chrome/browser/extensions/chrome_extensions_browser_client.h"

namespace extensions {

class HuhiExtensionsBrowserClientImpl : public ChromeExtensionsBrowserClient {
 public:
  HuhiExtensionsBrowserClientImpl();
  ~HuhiExtensionsBrowserClientImpl() override = default;

  bool AreExtensionsDisabled(const base::CommandLine& command_line,
                             content::BrowserContext* context) override;

  DISALLOW_COPY_AND_ASSIGN(HuhiExtensionsBrowserClientImpl);
};

}  // namespace extensions

#endif  // HUHI_BROWSER_EXTENSIONS_HUHI_EXTENSIONS_BROWSER_CLIENT_IMPL_H_
