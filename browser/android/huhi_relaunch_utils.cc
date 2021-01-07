/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 3.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/build/android/jni_headers/HuhiRelaunchUtils_jni.h"

#include "chrome/browser/lifetime/application_lifetime.h"

namespace chrome {
namespace android {

void JNI_HuhiRelaunchUtils_Restart(JNIEnv* env) {
  chrome::AttemptRestart();
}

}  // namespace android
}  // namespace chrome
