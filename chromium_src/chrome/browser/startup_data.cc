/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "base/macros.h"
#include "huhi/browser/browser_context_keyed_service_factories.h"
#include "chrome/browser/profiles/chrome_browser_main_extra_parts_profiles.h"

namespace {

class HuhiBrowserMainExtraPartsProfiles
    : public ChromeBrowserMainExtraPartsProfiles {
 public:
  HuhiBrowserMainExtraPartsProfiles() = default;
  ~HuhiBrowserMainExtraPartsProfiles() override = default;

  static void EnsureBrowserContextKeyedServiceFactoriesBuilt() {
    ChromeBrowserMainExtraPartsProfiles::
        EnsureBrowserContextKeyedServiceFactoriesBuilt();
    huhi::EnsureBrowserContextKeyedServiceFactoriesBuilt();
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(HuhiBrowserMainExtraPartsProfiles);
};

}  // namespace

#define ChromeBrowserMainExtraPartsProfiles HuhiBrowserMainExtraPartsProfiles
#include "../../../../chrome/browser/startup_data.cc"
#undef ChromeBrowserMainExtraPartsProfiles
