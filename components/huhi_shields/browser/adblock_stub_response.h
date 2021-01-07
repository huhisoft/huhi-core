/* Copyright 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_SHIELDS_BROWSER_ADBLOCK_STUB_RESPONSE_H_
#define HUHI_COMPONENTS_HUHI_SHIELDS_BROWSER_ADBLOCK_STUB_RESPONSE_H_

#include <string>
#include "base/optional.h"
#include "services/network/public/mojom/url_response_head.mojom-forward.h"

namespace network {
struct ResourceRequest;
}  // namespace network

namespace huhi_shields {

// Intercepts certain requests and blocks them by silently returning 200 OK
// and not allowing them to hit the network.
void MakeStubResponse(const base::Optional<std::string>& data_url,
                      const network::ResourceRequest& request,
                      network::mojom::URLResponseHeadPtr* response,
                      std::string* data);

}  // namespace huhi_shields

#endif  // HUHI_COMPONENTS_HUHI_SHIELDS_BROWSER_ADBLOCK_STUB_RESPONSE_H_
