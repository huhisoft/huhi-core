/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_ADS_BROWSER_BACKGROUND_HELPER_WIN_H_
#define HUHI_COMPONENTS_HUHI_ADS_BROWSER_BACKGROUND_HELPER_WIN_H_

#include <windows.h>
#include <memory>

#include "base/macros.h"
#include "base/memory/singleton.h"
#include "huhi/components/huhi_ads/browser/background_helper.h"
#include "ui/gfx/win/singleton_hwnd_observer.h"

namespace huhi_ads {

class BackgroundHelperWin : public BackgroundHelper {
 public:
  BackgroundHelperWin(const BackgroundHelperWin&) = delete;
  BackgroundHelperWin& operator=(const BackgroundHelperWin&) = delete;

  static BackgroundHelperWin* GetInstance();

 private:
  friend struct base::DefaultSingletonTraits<BackgroundHelperWin>;

  BackgroundHelperWin();
  ~BackgroundHelperWin() override;

  void OnWndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

  std::unique_ptr<gfx::SingletonHwndObserver> singleton_hwnd_observer_;

  // BackgroundHelper impl
  bool IsForeground() const override;
};

}  // namespace huhi_ads

#endif  // HUHI_COMPONENTS_HUHI_ADS_BROWSER_BACKGROUND_HELPER_WIN_H_
