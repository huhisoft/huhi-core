/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#define IsComponentExtensionWhitelisted IsComponentExtensionWhitelisted_ChromiumImpl  // NOLINT
#include "../../../../../../chrome/browser/extensions/component_extensions_whitelist/whitelist.cc"  // NOLINT
#undef IsComponentExtensionWhitelisted

#include "base/stl_util.h"
#include "huhi/components/huhi_extension/grit/huhi_extension.h"
#include "huhi/components/huhi_rewards/resources/extension/grit/huhi_rewards_extension_resources.h"
#include "huhi/components/huhi_webtorrent/grit/huhi_webtorrent_resources.h"
#include "components/grit/huhi_components_resources.h"
#include "extensions/common/constants.h"

namespace extensions {

  bool IsComponentExtensionWhitelisted(const std::string& extension_id) {
    const char* const kAllowed[] = {
      huhi_extension_id,
      huhi_rewards_extension_id,
      ethereum_remote_client_extension_id,
      huhi_webtorrent_extension_id
    };

    for (size_t i = 0; i < base::size(kAllowed); ++i) {
      if (extension_id == kAllowed[i])
        return true;
    }

    return IsComponentExtensionWhitelisted_ChromiumImpl(extension_id);
  }

  bool IsComponentExtensionWhitelisted(int manifest_resource_id) {
    switch (manifest_resource_id) {
      // Please keep the list in alphabetical order.
      case IDR_HUHI_EXTENSION:
      case IDR_HUHI_REWARDS:
      case IDR_HUHI_WEBTORRENT:
        return true;
    }

    return IsComponentExtensionWhitelisted_ChromiumImpl(manifest_resource_id);
  }

}  // namespace extensions
