/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#define AddProfilesExtraParts AddProfilesExtraParts_ChromiumImpl
#include "../../../../../chrome/browser/profiles/chrome_browser_main_extra_parts_profiles.cc"
#undef AddProfilesExtraParts

#include "huhi/browser/browser_context_keyed_service_factories.h"

namespace {

class HuhiBrowserMainExtraPartsProfiles
    : public ChromeBrowserMainExtraPartsProfiles {
 public:
  HuhiBrowserMainExtraPartsProfiles()
      : ChromeBrowserMainExtraPartsProfiles() {}

  void PreProfileInit() override {
    ChromeBrowserMainExtraPartsProfiles::PreProfileInit();
    huhi::EnsureBrowserContextKeyedServiceFactoriesBuilt();
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(HuhiBrowserMainExtraPartsProfiles);
};

}  // namespace

namespace chrome {

void AddProfilesExtraParts(ChromeBrowserMainParts* main_parts) {
  main_parts->AddParts(std::make_unique<HuhiBrowserMainExtraPartsProfiles>());
}

}  // namespace chrome
