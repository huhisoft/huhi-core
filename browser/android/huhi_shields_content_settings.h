/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_ANDROID_HUHI_SHIELDS_CONTENT_SETTINGS_H_
#define HUHI_BROWSER_ANDROID_HUHI_SHIELDS_CONTENT_SETTINGS_H_

#include <jni.h>
#include <string>
#include "base/android/scoped_java_ref.h"

namespace chrome {
namespace android {

class HuhiShieldsContentSettings {
 public:
  HuhiShieldsContentSettings(JNIEnv* env,
                              const base::android::JavaRef<jobject>& obj);
  ~HuhiShieldsContentSettings();

  void Destroy(JNIEnv* env);
  void DispatchBlockedEventToJava(int tab_id,
                                  const std::string& block_type,
                                  const std::string& subresource);
  void DispatchSavedBandwidthToJava(uint64_t savings);

  static void DispatchSavedBandwidth(uint64_t savings);

  static void DispatchBlockedEvent(int tab_id,
                                   const std::string& block_type,
                                   const std::string& subresource);

 private:
  base::android::ScopedJavaGlobalRef<jobject> jobj_;
};

}  // namespace android
}  // namespace chrome

#endif  // HUHI_BROWSER_ANDROID_HUHI_SHIELDS_CONTENT_SETTINGS_H_
