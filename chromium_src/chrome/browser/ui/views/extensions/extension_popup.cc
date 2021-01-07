/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/browser/extensions/extension_view_host.h"
#include "extensions/common/constants.h"

namespace {
bool IsHuhiExtension(extensions::ExtensionViewHost* host) {
  // Clipping issue is not present on linux.
#if defined(OS_MAC) || defined(OS_WIN)
  const auto extensionId = host->extension()->id();
  return (extensionId == huhi_extension_id ||
          extensionId == huhi_rewards_extension_id);
#endif
  return false;
}
}  // namespace

// HACK: removes border radius for huhi extensions
//       as webview does not support radius clipping which results
//       in white strips at top and bottom of popup.
// TODO(mkarolin): add huhi extension radius back in when macOS and Windows
//       popups support web dialog window radius clipping.
#define HUHI_ADDED_TO_WIDGET                      \
  const int radius = IsHuhiExtension(host_.get()) \
                         ? 0                       \
                         : GetBubbleFrameView()->corner_radius();

#include "../../../../../../../chrome/browser/ui/views/extensions/extension_popup.cc"
#undef HUHI_ADDED_TO_WIDGET
