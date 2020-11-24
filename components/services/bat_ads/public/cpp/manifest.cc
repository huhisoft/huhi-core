/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/components/services/bat_ads/public/cpp/manifest.h"

#include "base/no_destructor.h"
#include "huhi/components/services/bat_ads/public/interfaces/bat_ads.mojom.h"
#include "services/service_manager/public/cpp/manifest_builder.h"

namespace bat_ads {

const service_manager::Manifest& GetManifest() {
  static base::NoDestructor<service_manager::Manifest> manifest{
      service_manager::ManifestBuilder()
          .WithServiceName(mojom::kServiceName)
          .WithDisplayName("Bat Ads Service")
          .WithOptions(
              service_manager::ManifestOptionsBuilder()
                  .WithInstanceSharingPolicy(
                      service_manager::Manifest::InstanceSharingPolicy::
                          kSharedAcrossGroups)
                  .WithExecutionMode(service_manager::Manifest::ExecutionMode::
                                         kOutOfProcessBuiltin)
                  .WithSandboxType("utility")
                  .Build())
          .ExposeCapability(
              "bat_ads",
              service_manager::Manifest::InterfaceList<mojom::BatAdsService>())
          .Build()};
  return *manifest;
}

}  // namespace bat_ads
