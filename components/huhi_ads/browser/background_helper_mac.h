/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_ADS_BROWSER_BACKGROUND_HELPER_MAC_H_
#define HUHI_COMPONENTS_HUHI_ADS_BROWSER_BACKGROUND_HELPER_MAC_H_

#include "base/compiler_specific.h"
#include "base/mac/scoped_nsobject.h"
#include "base/macros.h"
#include "base/memory/singleton.h"
#include "huhi/components/huhi_ads/browser/background_helper.h"

@class BackgroundHelperDelegate;

namespace huhi_ads {

class BackgroundHelperMac : public BackgroundHelper {
 public:
  BackgroundHelperMac(const BackgroundHelperMac&) = delete;
  BackgroundHelperMac& operator=(const BackgroundHelperMac&) = delete;

  static BackgroundHelperMac* GetInstance();

 private:
  friend struct base::DefaultSingletonTraits<BackgroundHelperMac>;

  BackgroundHelperMac();
  ~BackgroundHelperMac() override;

  base::scoped_nsobject<BackgroundHelperDelegate> delegate_;

  // BackgroundHelper impl
  bool IsForeground() const override;
};

}  // namespace huhi_ads

#endif  // HUHI_COMPONENTS_HUHI_ADS_BROWSER_BACKGROUND_HELPER_MAC_H_
