/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_EXTENSIONS_HUHI_EXTENSIONS_BROWSER_API_PROVIDER_H_
#define HUHI_BROWSER_EXTENSIONS_HUHI_EXTENSIONS_BROWSER_API_PROVIDER_H_

#include "base/macros.h"
#include "extensions/browser/extensions_browser_api_provider.h"

namespace extensions {

class HuhiExtensionsBrowserAPIProvider : public ExtensionsBrowserAPIProvider {
 public:
  HuhiExtensionsBrowserAPIProvider();
  ~HuhiExtensionsBrowserAPIProvider() override;

  void RegisterExtensionFunctions(ExtensionFunctionRegistry* registry) override;

 private:
  DISALLOW_COPY_AND_ASSIGN(HuhiExtensionsBrowserAPIProvider);
};

}  // namespace extensions

#endif  // HUHI_BROWSER_EXTENSIONS_HUHI_EXTENSIONS_BROWSER_API_PROVIDER_H_
