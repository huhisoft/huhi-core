/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <string>

#include "base/android/jni_android.h"
#include "huhi/browser/huhi_browser_process_impl.h"
#include "huhi/browser/huhi_stats/huhi_stats_updater.h"
#include "huhi/build/android/jni_headers/HuhiActivity_jni.h"

namespace chrome {
namespace android {

static void JNI_HuhiActivity_RestartStatsUpdater(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& jcaller) {
  g_huhi_browser_process->huhi_stats_updater()->Stop();
  g_huhi_browser_process->huhi_stats_updater()->Start();
}

}  // namespace android
}  // namespace chrome
