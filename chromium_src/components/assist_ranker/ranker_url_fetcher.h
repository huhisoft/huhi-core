/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * you can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_COMPONENTS_ASSIST_RANKER_RANKER_URL_FETCHER_H_
#define HUHI_CHROMIUM_SRC_COMPONENTS_ASSIST_RANKER_RANKER_URL_FETCHER_H_

#define Request                                                               \
  Request_ChromiumImpl(const GURL& url, Callback callback,                    \
                       network::mojom::URLLoaderFactory* url_loader_factory); \
  bool Request

#include "../../../../components/assist_ranker/ranker_url_fetcher.h"
#undef Request

#endif  // HUHI_CHROMIUM_SRC_COMPONENTS_ASSIST_RANKER_RANKER_URL_FETCHER_H_
