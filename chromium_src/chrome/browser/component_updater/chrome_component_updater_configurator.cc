/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/component_updater/huhi_component_updater_configurator.h"

#define MakeChromeComponentUpdaterConfigurator \
    MakeChromeComponentUpdaterConfigurator_ChromiumImpl
#include "../../../../../chrome/browser/component_updater/chrome_component_updater_configurator.cc"  // NOLINT
#undef MakeChromeComponentUpdaterConfigurator

namespace component_updater {

scoped_refptr<update_client::Configurator>
MakeChromeComponentUpdaterConfigurator(const base::CommandLine* cmdline,
                                       PrefService* pref_service) {
  return base::MakeRefCounted<HuhiConfigurator>(cmdline, pref_service);
}

}  // namespace component_updater
