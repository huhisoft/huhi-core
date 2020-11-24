/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_NET_HUHI_SITE_HACKS_NETWORK_DELEGATE_HELPER_H_
#define HUHI_BROWSER_NET_HUHI_SITE_HACKS_NETWORK_DELEGATE_HELPER_H_

#include <memory>

#include "huhi/browser/net/url_context.h"

namespace net {
class URLRequest;
}

namespace huhi {

int OnBeforeURLRequest_SiteHacksWork(
    const ResponseCallback& next_callback,
    std::shared_ptr<HuhiRequestInfo> ctx);

int OnBeforeStartTransaction_SiteHacksWork(
    net::HttpRequestHeaders* headers,
    const ResponseCallback& next_callback,
    std::shared_ptr<HuhiRequestInfo> ctx);

}  // namespace huhi

#endif  // HUHI_BROWSER_NET_HUHI_SITE_HACKS_NETWORK_DELEGATE_HELPER_H_
