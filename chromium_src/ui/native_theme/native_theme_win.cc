// Copyright (c) 2020 The Huhi Software Authors
// This Source Code Form is subject to the terms of the Huhi Software
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

namespace {
bool s_ignore_system_dark_mode_change = false;
}  // namespace

#define HUHI_NATIVETHEMEWIN_UPDATEDARKMODESTATUS \
  if (s_ignore_system_dark_mode_change) {         \
    return;                                       \
  }

#include "../../../../ui/native_theme/native_theme_win.cc"  // NOLINT

namespace ui {

void NATIVE_THEME_EXPORT IgnoreSystemDarkModeChange(bool ignore) {
  s_ignore_system_dark_mode_change = ignore;
}

}  // namespace ui
