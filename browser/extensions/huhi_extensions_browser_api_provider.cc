/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/extensions/huhi_extensions_browser_api_provider.h"

#include "huhi/common/extensions/api/generated_api_registration.h"
#include "extensions/browser/extension_function_registry.h"

// TOOD: I don't know why this isn't automatically linked in
#include "../gen/huhi/common/extensions/api/generated_api_registration.cc"

namespace extensions {

HuhiExtensionsBrowserAPIProvider::HuhiExtensionsBrowserAPIProvider() =
    default;
HuhiExtensionsBrowserAPIProvider::~HuhiExtensionsBrowserAPIProvider() =
    default;

void HuhiExtensionsBrowserAPIProvider::RegisterExtensionFunctions(
    ExtensionFunctionRegistry* registry) {
  // Generated APIs from Huhi.
  api::HuhiGeneratedFunctionRegistry::RegisterAll(registry);
}

}  // namespace extensions
