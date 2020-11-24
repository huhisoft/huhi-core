/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_NET_HUHI_TORRENT_REDIRECT_NETWORK_DELEGATE_HELPER_H_
#define HUHI_BROWSER_NET_HUHI_TORRENT_REDIRECT_NETWORK_DELEGATE_HELPER_H_

#include <memory>

#include "huhi/browser/net/url_context.h"

namespace huhi {
struct HuhiRequestInfo;
}

namespace net {
class URLRequest;
}

namespace webtorrent {

int OnHeadersReceived_TorrentRedirectWork(
    const net::HttpResponseHeaders* original_response_headers,
    scoped_refptr<net::HttpResponseHeaders>* override_response_headers,
    GURL* allowed_unsafe_redirect_url,
    const huhi::ResponseCallback& next_callback,
    std::shared_ptr<huhi::HuhiRequestInfo> ctx);

}  // namespace webtorrent

#endif  // HUHI_BROWSER_NET_HUHI_TORRENT_REDIRECT_NETWORK_DELEGATE_HELPER_H_
