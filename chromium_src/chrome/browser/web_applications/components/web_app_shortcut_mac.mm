/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

namespace base {
class FilePath;
}  // namespace base

namespace {
base::FilePath GetLocalizableHuhiAppShortcutsSubdirName();
}

#include "../../../../../../chrome/browser/web_applications/components/web_app_shortcut_mac.mm"  // NOLINT

namespace {
base::FilePath GetLocalizableHuhiAppShortcutsSubdirName() {
  static const char kHuhiBrowserDevelopmentAppDirName[] =
      "Huhi Browser Development Apps.localized";
  static const char kHuhiBrowserAppDirName[] =
      "Huhi Browser Apps.localized";
  static const char kHuhiBrowserBetaAppDirName[] =
      "Huhi Browser Beta Apps.localized";
  static const char kHuhiBrowserDevAppDirName[] =
      "Huhi Browser Dev Apps.localized";
  static const char kHuhiBrowserNightlyAppDirName[] =
      "Huhi Browser Nightly Apps.localized";

  switch (chrome::GetChannel()) {
    case version_info::Channel::STABLE:
      return base::FilePath(kHuhiBrowserAppDirName);
    case version_info::Channel::BETA:
      return base::FilePath(kHuhiBrowserBetaAppDirName);
    case version_info::Channel::DEV:
      return base::FilePath(kHuhiBrowserDevAppDirName);
    case version_info::Channel::CANARY:
      return base::FilePath(kHuhiBrowserNightlyAppDirName);
    case version_info::Channel::UNKNOWN:
      return base::FilePath(kHuhiBrowserDevelopmentAppDirName);
    default:
      NOTREACHED();
      return base::FilePath(kHuhiBrowserDevelopmentAppDirName);
  }
}
}  // namespace
