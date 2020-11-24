/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "base/android/jni_android.h"
#include "base/android/jni_string.h"
#include "base/logging.h"
#include "huhi/browser/huhi_ads/android/jni_headers/HuhiAdsNativeHelper_jni.h"
#include "huhi/components/huhi_ads/browser/ads_service.h"
#include "huhi/components/huhi_ads/browser/ads_service_factory.h"
#include "huhi/components/l10n/browser/locale_helper_android.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_android.h"

using base::android::JavaParamRef;
using base::android::ScopedJavaLocalRef;

namespace chrome {

namespace android {

// static

jboolean JNI_HuhiAdsNativeHelper_IsHuhiAdsEnabled(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile_android) {
  Profile* profile = ProfileAndroid::FromProfileAndroid(j_profile_android);
  auto* ads_service_ = huhi_ads::AdsServiceFactory::GetForProfile(profile);
  if (!ads_service_) {
    NOTREACHED();
    return false;
  }

  return ads_service_->IsEnabled();
}

jboolean JNI_HuhiAdsNativeHelper_IsLocaleValid(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile_android) {
  Profile* profile = ProfileAndroid::FromProfileAndroid(j_profile_android);
  auto* ads_service_ = huhi_ads::AdsServiceFactory::GetForProfile(profile);
  if (!ads_service_) {
    NOTREACHED();
    return false;
  }

  return ads_service_->IsSupportedLocale();
}

jboolean JNI_HuhiAdsNativeHelper_IsSupportedLocale(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile_android) {
  Profile* profile = ProfileAndroid::FromProfileAndroid(j_profile_android);
  auto* ads_service_ = huhi_ads::AdsServiceFactory::GetForProfile(profile);
  if (!ads_service_) {
    NOTREACHED();
    return false;
  }

  return ads_service_->IsSupportedLocale();
}

jboolean JNI_HuhiAdsNativeHelper_IsNewlySupportedLocale(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile_android) {
  Profile* profile = ProfileAndroid::FromProfileAndroid(j_profile_android);
  auto* ads_service_ = huhi_ads::AdsServiceFactory::GetForProfile(profile);
  if (!ads_service_) {
    NOTREACHED();
    return false;
  }

  return ads_service_->IsNewlySupportedLocale();
}

void JNI_HuhiAdsNativeHelper_SetAdsEnabled(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile_android) {
  Profile* profile = ProfileAndroid::FromProfileAndroid(j_profile_android);
  auto* ads_service_ = huhi_ads::AdsServiceFactory::GetForProfile(profile);
  if (!ads_service_) {
    NOTREACHED();
    return;
  }

  ads_service_->SetEnabled(true);
}

}  // namespace android

}  // namespace chrome
