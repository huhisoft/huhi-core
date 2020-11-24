/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_SERVICES_BAT_LEDGER_PUBLIC_CPP_MANIFEST_H_
#define HUHI_COMPONENTS_SERVICES_BAT_LEDGER_PUBLIC_CPP_MANIFEST_H_

#include "services/service_manager/public/cpp/manifest.h"

namespace bat_ledger {

const service_manager::Manifest& GetManifest();

}  // namespace bat_ledger

#endif  // HUHI_COMPONENTS_SERVICES_BAT_LEDGER_PUBLIC_CPP_MANIFEST_H_
