/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#define IsComponentExtensionAllowlisted IsComponentExtensionAllowlisted_ChromiumImpl  // NOLINT
#include "../../../../../../chrome/browser/extensions/component_extensions_allowlist/allowlist.cc"  // NOLINT
#undef IsComponentExtensionAllowlisted

#include "base/stl_util.h"
#include "huhi/components/huhi_extension/grit/huhi_extension.h"
#include "huhi/components/huhi_wallet/buildflags/buildflags.h"
#include "huhi/components/huhi_rewards/resources/extension/grit/huhi_rewards_extension_resources.h"
#include "huhi/components/huhi_webtorrent/grit/huhi_webtorrent_resources.h"
#include "components/grit/huhi_components_resources.h"
#include "extensions/common/constants.h"

#if BUILDFLAG(HUHI_WALLET_ENABLED)
#include "huhi/components/huhi_wallet/huhi_wallet_constants.h"
#endif

namespace extensions {

  bool IsComponentExtensionAllowlisted(const std::string& extension_id) {
    const char* const kAllowed[] = {
      huhi_extension_id,
      huhi_rewards_extension_id,
#if BUILDFLAG(HUHI_WALLET_ENABLED)
      ethereum_remote_client_extension_id,
#endif
      huhi_webtorrent_extension_id
    };

    for (size_t i = 0; i < base::size(kAllowed); ++i) {
      if (extension_id == kAllowed[i])
        return true;
    }

    return IsComponentExtensionAllowlisted_ChromiumImpl(extension_id);
  }

  bool IsComponentExtensionAllowlisted(int manifest_resource_id) {
    switch (manifest_resource_id) {
      // Please keep the list in alphabetical order.
      case IDR_HUHI_EXTENSION:
      case IDR_HUHI_REWARDS:
      case IDR_HUHI_WEBTORRENT:
        return true;
    }

    return IsComponentExtensionAllowlisted_ChromiumImpl(manifest_resource_id);
  }

}  // namespace extensions
