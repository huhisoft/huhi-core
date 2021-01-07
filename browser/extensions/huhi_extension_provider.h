/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_EXTENSIONS_HUHI_EXTENSION_PROVIDER_H_
#define HUHI_BROWSER_EXTENSIONS_HUHI_EXTENSION_PROVIDER_H_

#include <string>

#include "extensions/browser/management_policy.h"

namespace extensions {

class HuhiExtensionProvider : public ManagementPolicy::Provider {
 public:
  HuhiExtensionProvider();
  ~HuhiExtensionProvider() override;
  std::string GetDebugPolicyProviderName() const override;
  bool UserMayLoad(const Extension* extension,
                   base::string16* error) const override;
  bool MustRemainInstalled(const Extension* extension,
                           base::string16* error) const override;

 private:
  DISALLOW_COPY_AND_ASSIGN(HuhiExtensionProvider);
};

}  // namespace extensions

#endif  // HUHI_BROWSER_EXTENSIONS_HUHI_EXTENSION_PROVIDER_H_
