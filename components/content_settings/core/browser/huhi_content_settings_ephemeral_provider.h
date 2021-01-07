/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_CONTENT_SETTINGS_CORE_BROWSER_HUHI_CONTENT_SETTINGS_EPHEMERAL_PROVIDER_H_
#define HUHI_COMPONENTS_CONTENT_SETTINGS_CORE_BROWSER_HUHI_CONTENT_SETTINGS_EPHEMERAL_PROVIDER_H_

#include <memory>

#include "components/content_settings/core/browser/content_settings_ephemeral_provider.h"

namespace content_settings {

// See the comments of HuhiPrefProvider.
class HuhiEphemeralProvider : public EphemeralProvider {
 public:
  using EphemeralProvider::EphemeralProvider;
  ~HuhiEphemeralProvider() override {}

 private:
  // EphemeralProvider overrides:
  bool SetWebsiteSetting(
      const ContentSettingsPattern& primary_pattern,
      const ContentSettingsPattern& secondary_pattern,
      ContentSettingsType content_type,
      const ResourceIdentifier& resource_identifier,
      std::unique_ptr<base::Value>&& value,
      const ContentSettingConstraints& constraints = {}) override;

  DISALLOW_COPY_AND_ASSIGN(HuhiEphemeralProvider);
};

}  // namespace content_settings

#endif  // HUHI_COMPONENTS_CONTENT_SETTINGS_CORE_BROWSER_HUHI_CONTENT_SETTINGS_EPHEMERAL_PROVIDER_H_
