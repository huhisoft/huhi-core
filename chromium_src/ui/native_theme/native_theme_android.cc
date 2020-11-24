// Copyright (c) 2020 The Huhi Software Authors
// This Source Code Form is subject to the terms of the Huhi Software
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#include "../../../../ui/native_theme/native_theme_android.cc"

ui::NativeTheme* ui::NativeTheme::HuhiGetInstanceForNativeUi() {
  struct StubNativeThemeAndroid : public ui::NativeThemeAndroid {
    bool ShouldUseDarkColors() const override { return false; }
  };
  static base::NoDestructor<StubNativeThemeAndroid> s_native_theme;
  return s_native_theme.get();
}
