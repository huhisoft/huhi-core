/* Copyright 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_COMPONENTS_CONTENT_SETTINGS_RENDERER_CONTENT_SETTINGS_AGENT_IMPL_H_
#define HUHI_CHROMIUM_SRC_COMPONENTS_CONTENT_SETTINGS_RENDERER_CONTENT_SETTINGS_AGENT_IMPL_H_

#define HUHI_CONTENT_SETTINGS_AGENT_IMPL_H_ \
friend class HuhiContentSettingsAgentImpl;

#define IsWhitelistedForContentSettings                                     \
  IsWhitelistedForContentSettings(const blink::WebSecurityOrigin& origin,   \
                                  const blink::WebURL& document_url) const; \
  bool IsWhitelistedForContentSettings

#include "../../../../../components/content_settings/renderer/content_settings_agent_impl.h"
#undef IsWhitelistedForContentSettings

#endif  // HUHI_CHROMIUM_SRC_COMPONENTS_CONTENT_SETTINGS_RENDERER_CONTENT_SETTINGS_AGENT_IMPL_H_
