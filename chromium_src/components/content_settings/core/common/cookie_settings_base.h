/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_COMPONENTS_CONTENT_SETTINGS_CORE_COMMON_COOKIE_SETTINGS_BASE_H_
#define HUHI_CHROMIUM_SRC_COMPONENTS_CONTENT_SETTINGS_CORE_COMMON_COOKIE_SETTINGS_BASE_H_

#define HUHI_COOKIE_SETTINGS_BASE_H                                      \
 private:                                                                 \
  bool IsChromiumCookieAccessAllowed(const GURL& url,                     \
                                     const GURL& first_party_url) const;  \
  bool IsChromiumCookieAccessAllowed(                                     \
      const GURL& url,                                                    \
      const GURL& site_for_cookies,                                       \
      const base::Optional<url::Origin>& top_frame_origin) const;

#include "../../../../../../components/content_settings/core/common/cookie_settings_base.h"

#undef HUHI_COOKIE_SETTINGS_BASE_H

#endif  // HUHI_CHROMIUM_SRC_COMPONENTS_CONTENT_SETTINGS_CORE_COMMON_COOKIE_SETTINGS_BASE_H_
