/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_PAGE_PLUGIN_DATA_H_
#define HUHI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_PAGE_PLUGIN_DATA_H_

#define HUHI_PLUGIN_DATA_H                                  \
  void SetName(const String& new_name) { name_ = new_name; } \
  void SetFilename(const String& new_filename) { filename_ = new_filename; }

#include "../../../../../../../third_party/blink/renderer/core/page/plugin_data.h"

#undef HUHI_PLUGIN_DATA_H

#endif  // HUHI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_PAGE_PLUGIN_DATA_H_
