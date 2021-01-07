/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/extensions/huhi_extensions_browser_client_impl.h"

#include <memory>

#include "base/macros.h"
#include "huhi/browser/extensions/huhi_extensions_browser_api_provider.h"
#include "huhi/browser/profiles/profile_util.h"
#include "chrome/browser/extensions/chrome_component_extension_resource_manager.h"
#include "components/prefs/pref_service.h"

namespace extensions {

HuhiExtensionsBrowserClientImpl::HuhiExtensionsBrowserClientImpl() {
  AddAPIProvider(std::make_unique<HuhiExtensionsBrowserAPIProvider>());
  // ChromeComponentExtensionResourceManager's Data needs to be LazyInit'ed on
  // the UI thread (due to pdf_extension_util::AddStrings calling
  // g_browser_process->GetApplicationLocale() that has a DCHECK to that
  // regard).
  ignore_result(GetComponentExtensionResourceManager()
                    ->GetTemplateReplacementsForExtension(""));
}

bool HuhiExtensionsBrowserClientImpl::AreExtensionsDisabled(
    const base::CommandLine& command_line,
    content::BrowserContext* context) {
  if (huhi::IsTorProfile(context))
    return true;

  return ChromeExtensionsBrowserClient::AreExtensionsDisabled(command_line,
                                                              context);
}

}  // namespace extensions
