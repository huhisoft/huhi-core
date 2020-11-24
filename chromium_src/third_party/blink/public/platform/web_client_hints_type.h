/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_THIRD_PARTY_BLINK_PUBLIC_PLATFORM_WEB_CLIENT_HINTS_TYPE_H_
#define HUHI_CHROMIUM_SRC_THIRD_PARTY_BLINK_PUBLIC_PLATFORM_WEB_CLIENT_HINTS_TYPE_H_

#include "services/network/public/mojom/web_client_hints_types.mojom-shared.h"

namespace blink {

// WebEnabledClientHints stores all the client hints along with whether the hint
// is enabled or not.
struct WebEnabledClientHints {
  WebEnabledClientHints() = default;

  bool IsEnabled(network::mojom::WebClientHintsType type) const {
    return false;
  }

  void SetIsEnabled(network::mojom::WebClientHintsType type, bool should_send) {
    enabled_types_[static_cast<int>(type)] = false;
  }

  bool enabled_types_[static_cast<int>(
                          network::mojom::WebClientHintsType::kMaxValue) +
                      1] = {};
};

}  // namespace blink

#endif  // HUHI_CHROMIUM_SRC_THIRD_PARTY_BLINK_PUBLIC_PLATFORM_WEB_CLIENT_HINTS_TYPE_H_
