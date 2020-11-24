/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_L10N_BROWSER_LOCALE_HELPER_WIN_H_
#define HUHI_COMPONENTS_L10N_BROWSER_LOCALE_HELPER_WIN_H_

#include <windows.h>
#include <string>

#include "huhi/components/l10n/browser/locale_helper.h"

namespace huhi_l10n {

class LocaleHelperWin : public LocaleHelper {
 public:
  LocaleHelperWin(const LocaleHelperWin&) = delete;
  LocaleHelperWin& operator=(const LocaleHelperWin&) = delete;

  static LocaleHelperWin* GetInstanceImpl();

 private:
  friend struct base::DefaultSingletonTraits<LocaleHelperWin>;

  LocaleHelperWin();
  ~LocaleHelperWin() override;

  // LocaleHelper impl
  std::string GetLocale() const override;
};

}  // namespace huhi_l10n

#endif  // HUHI_COMPONENTS_L10N_BROWSER_LOCALE_HELPER_WIN_H_
