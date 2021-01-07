/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 3.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <string>

#include "base/android/jni_string.h"
#include "base/feature_list.h"
#include "huhi/browser/huhi_browser_process_impl.h"
#include "huhi/build/android/jni_headers/HuhiFeatureList_jni.h"
#include "chrome/browser/about_flags.h"
#include "components/flags_ui/pref_service_flags_storage.h"

namespace chrome {
namespace android {

static void JNI_HuhiFeatureList_EnableFeature(JNIEnv* env,
    const base::android::JavaParamRef<jstring>& featureName,
    jboolean enabled) {
  std::string feature_name = ConvertJavaStringToUTF8(env, featureName);
  enabled ? feature_name += "@1" : feature_name += "@0";
  flags_ui::PrefServiceFlagsStorage flags_storage(
      g_huhi_browser_process->local_state());
  about_flags::SetFeatureEntryEnabled(&flags_storage, feature_name, true);
}

}  // namespace android
}  // namespace chrome
