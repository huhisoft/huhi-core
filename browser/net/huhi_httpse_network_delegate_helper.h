/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_NET_HUHI_HTTPSE_NETWORK_DELEGATE_H_
#define HUHI_BROWSER_NET_HUHI_HTTPSE_NETWORK_DELEGATE_H_

#include "huhi/browser/net/url_context.h"

namespace huhi {

int OnBeforeURLRequest_HttpsePreFileWork(
    const ResponseCallback& next_callback,
    std::shared_ptr<HuhiRequestInfo> ctx);

}  // namespace huhi

#endif  // HUHI_BROWSER_NET_HUHI_NETWORK_DELEGATE_H_
