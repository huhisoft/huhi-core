/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_ADS_BROWSER_BACKGROUND_HELPER_ANDROID_H_
#define HUHI_COMPONENTS_HUHI_ADS_BROWSER_BACKGROUND_HELPER_ANDROID_H_

#include <memory>

#include "base/macros.h"
#include "base/memory/singleton.h"
#include "base/memory/weak_ptr.h"
#include "huhi/components/huhi_ads/browser/background_helper.h"
#include "base/android/application_status_listener.h"

namespace huhi_ads {

class BackgroundHelperAndroid :
    public BackgroundHelper,
    public base::SupportsWeakPtr<BackgroundHelperAndroid> {
 public:
  BackgroundHelperAndroid(const BackgroundHelperAndroid&) = delete;
  BackgroundHelperAndroid& operator=(const BackgroundHelperAndroid&) = delete;

  static BackgroundHelperAndroid* GetInstance();

 private:
  friend struct base::DefaultSingletonTraits<BackgroundHelperAndroid>;

  BackgroundHelperAndroid();
  ~BackgroundHelperAndroid() override;

  std::unique_ptr<base::android::ApplicationStatusListener>
    app_status_listener_;

  base::android::ApplicationState last_state_;

  void OnApplicationStateChange(base::android::ApplicationState state);

  // BackgroundHelper impl
  bool IsForeground() const override;
};

}  // namespace huhi_ads

#endif  // HUHI_COMPONENTS_HUHI_ADS_BROWSER_BACKGROUND_HELPER_ANDROID_H_
