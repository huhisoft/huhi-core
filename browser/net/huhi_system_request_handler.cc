/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/net/huhi_system_request_handler.h"

#include "huhi/browser/net/huhi_block_safebrowsing_urls.h"
#include "huhi/browser/net/huhi_common_static_redirect_network_delegate_helper.h"
#include "huhi/browser/net/huhi_static_redirect_network_delegate_helper.h"
#include "huhi/common/network_constants.h"
#include "extensions/common/url_pattern.h"
#include "services/network/public/cpp/resource_request.h"
#include "url/gurl.h"

namespace huhi {

std::string HuhiServicesKeyForTesting() {
  return HUHI_SERVICES_KEY;
}

void AddHuhiServicesKeyHeader(network::ResourceRequest* url_request) {
  static URLPattern huhi_proxy_pattern(URLPattern::SCHEME_HTTPS,
                                        kHuhiProxyPattern);
  static URLPattern huhisoftware_proxy_pattern(URLPattern::SCHEME_HTTPS,
                                                kHuhiSoftwareProxyPattern);
  if (huhi_proxy_pattern.MatchesURL(url_request->url) ||
      huhisoftware_proxy_pattern.MatchesURL(url_request->url)) {
    url_request->headers.SetHeaderIfMissing(kHuhiServicesKeyHeader,
                                            HUHI_SERVICES_KEY);
  }
  return;
}

network::ResourceRequest OnBeforeSystemRequest(
    const network::ResourceRequest& url_request) {
  GURL new_url;
  huhi::OnBeforeURLRequest_BlockSafeBrowsingReportingURLs(url_request.url,
                                                           &new_url);
  huhi::OnBeforeURLRequest_StaticRedirectWorkForGURL(url_request.url,
                                                      &new_url);
  huhi::OnBeforeURLRequest_CommonStaticRedirectWorkForGURL(url_request.url,
                                                            &new_url);
  network::ResourceRequest patched_request = url_request;
  if (!new_url.is_empty()) {
    patched_request.url = new_url;
  }
  AddHuhiServicesKeyHeader(&patched_request);
  return patched_request;
}

}  // namespace huhi
