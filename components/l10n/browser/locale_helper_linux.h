/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_L10N_BROWSER_LOCALE_HELPER_LINUX_H_
#define HUHI_COMPONENTS_L10N_BROWSER_LOCALE_HELPER_LINUX_H_

#include <string>

#include "huhi/components/l10n/browser/locale_helper.h"

namespace huhi_l10n {

class LocaleHelperLinux : public LocaleHelper {
 public:
  LocaleHelperLinux(const LocaleHelperLinux&) = delete;
  LocaleHelperLinux& operator=(const LocaleHelperLinux&) = delete;

  static LocaleHelperLinux* GetInstanceImpl();

 private:
  friend struct base::DefaultSingletonTraits<LocaleHelperLinux>;

  LocaleHelperLinux();
  ~LocaleHelperLinux() override;

  // LocaleHelper impl
  std::string GetLocale() const override;
};

}  // namespace huhi_l10n

#endif  // HUHI_COMPONENTS_L10N_BROWSER_LOCALE_HELPER_LINUX_H_
