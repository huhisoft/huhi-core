/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_CONTENT_PUBLIC_BROWSER_CONTENT_BROWSER_CLIENT_H_
#define HUHI_CHROMIUM_SRC_CONTENT_PUBLIC_BROWSER_CONTENT_BROWSER_CLIENT_H_

#include "third_party/blink/public/mojom/loader/referrer.mojom.h"

// Huhi-specific: allows the embedder to modify the referrer string
// according to user preferences.
#define HUHI_CONTENT_BROWSER_CLIENT_H                          \
  virtual void MaybeHideReferrer(                               \
      BrowserContext* browser_context, const GURL& request_url, \
      const GURL& document_url, bool is_main_frame,             \
      const std::string& method,                                \
      blink::mojom::ReferrerPtr* referrer) {}

#include "../../../../../content/public/browser/content_browser_client.h"

#undef HUHI_CONTENT_BROWSER_CLIENT_H

#endif  // HUHI_CHROMIUM_SRC_CONTENT_PUBLIC_BROWSER_CONTENT_BROWSER_CLIENT_H_
