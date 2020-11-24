/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/common/huhi_features.h"
#include "third_party/blink/public/common/features.h"

namespace chrome {
namespace android {

namespace {

const base::Feature* kHuhiFeaturesExposedToJava[] = {
    &features::kHuhiRewards,
    &blink::features::kForceWebContentsDarkMode,
};

const base::Feature* HuhiFindFeatureExposedToJava(
    const std::string& feature_name) {
  for (size_t i = 0; i < base::size(kHuhiFeaturesExposedToJava); ++i) {
    if (kHuhiFeaturesExposedToJava[i]->name == feature_name)
      return kHuhiFeaturesExposedToJava[i];
  }

  return nullptr;
}

}  // namespace

}  // namespace android
}  // namespace chrome

#define HUHI_FIND_FEATURE_EXPOSED_TO_JAVA                                    \
  const base::Feature* feature = HuhiFindFeatureExposedToJava(feature_name); \
  if (feature)                                                                \
    return feature;

#include "../../../../../../chrome/browser/flags/android/chrome_feature_list.cc"
#undef HUHI_FIND_FEATURE_EXPOSED_TO_JAVA
