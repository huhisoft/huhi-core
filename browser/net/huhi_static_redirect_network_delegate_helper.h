/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_NET_HUHI_STATIC_REDIRECT_NETWORK_DELEGATE_HELPER_H_
#define HUHI_BROWSER_NET_HUHI_STATIC_REDIRECT_NETWORK_DELEGATE_HELPER_H_

#include <memory>
#include <string>

#include "huhi/browser/net/url_context.h"

struct HuhiRequestInfo;

namespace huhi {

extern const char kSafeBrowsingTestingEndpoint[];

int OnBeforeURLRequest_StaticRedirectWork(
    const ResponseCallback& next_callback,
    std::shared_ptr<HuhiRequestInfo> ctx);

int OnBeforeURLRequest_StaticRedirectWorkForGURL(
    const GURL& request_url,
    GURL* new_url);

void SetSafeBrowsingEndpointForTesting(bool testing);

}  // namespace huhi

#endif  // HUHI_BROWSER_NET_HUHI_STATIC_REDIRECT_NETWORK_DELEGATE_HELPER_H_
