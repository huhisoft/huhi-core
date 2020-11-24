/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_NET_HUHI_SYSTEM_REQUEST_HANDLER_H_
#define HUHI_BROWSER_NET_HUHI_SYSTEM_REQUEST_HANDLER_H_

#include <string>

namespace network {
struct ResourceRequest;
}

extern const char kHuhiServicesKeyHeader[];

namespace huhi {

std::string HuhiServicesKeyForTesting();

void AddHuhiServicesKeyHeader(network::ResourceRequest* url_request);

network::ResourceRequest OnBeforeSystemRequest(
    const network::ResourceRequest& url_request);

}  // namespace huhi

#endif  // HUHI_BROWSER_NET_HUHI_SYSTEM_REQUEST_HANDLER_H_
