/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_NET_HUHI_BLOCK_SAFEBROWSING_URLS_H_
#define HUHI_BROWSER_NET_HUHI_BLOCK_SAFEBROWSING_URLS_H_

class GURL;

namespace huhi {

int OnBeforeURLRequest_BlockSafeBrowsingReportingURLs(const GURL& url,
                                                      GURL* new_url);

}  // namespace huhi

#endif  // HUHI_BROWSER_NET_HUHI_BLOCK_SAFEBROWSING_URLS_H_
