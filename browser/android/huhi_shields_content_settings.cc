/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/android/huhi_shields_content_settings.h"
#include "huhi/components/huhi_shields/browser/huhi_shields_util.h"

#include <string>

#include "base/android/jni_android.h"
#include "base/android/jni_string.h"
#include "huhi/build/android/jni_headers/HuhiShieldsContentSettings_jni.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_android.h"
#include "chrome/browser/profiles/profile_manager.h"
#include "components/content_settings/core/browser/content_settings_utils.h"
#include "components/content_settings/core/browser/host_content_settings_map.h"

namespace chrome {
namespace android {


// That class is linked to a global toolbar. It's a one instance on Android
HuhiShieldsContentSettings* g_huhi_shields_content_settings = nullptr;

static void JNI_HuhiShieldsContentSettings_Init(JNIEnv* env,
    const base::android::JavaParamRef<jobject>& jcaller) {
  g_huhi_shields_content_settings =
      new HuhiShieldsContentSettings(env, jcaller);
}

HuhiShieldsContentSettings::HuhiShieldsContentSettings(
    JNIEnv* env,
    const base::android::JavaRef<jobject>& obj)
    : jobj_(base::android::ScopedJavaGlobalRef<jobject>(obj)) {
  Java_HuhiShieldsContentSettings_setNativePtr(env, obj,
      reinterpret_cast<intptr_t>(this));
}

HuhiShieldsContentSettings::~HuhiShieldsContentSettings() {
}

void HuhiShieldsContentSettings::Destroy(JNIEnv* env) {
  g_huhi_shields_content_settings = nullptr;
  delete this;
}

void HuhiShieldsContentSettings::DispatchBlockedEventToJava(int tab_id,
        const std::string& block_type, const std::string& subresource) {
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_HuhiShieldsContentSettings_blockedEvent(
      env, jobj_, tab_id,
      base::android::ConvertUTF8ToJavaString(env, block_type),
      base::android::ConvertUTF8ToJavaString(env, subresource));
}

void HuhiShieldsContentSettings::DispatchSavedBandwidthToJava(
  uint64_t savings) {
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_HuhiShieldsContentSettings_savedBandwidth(env, jobj_, savings);
}

void HuhiShieldsContentSettings::DispatchSavedBandwidth(uint64_t savings) {
  DCHECK(g_huhi_shields_content_settings);
  if (!g_huhi_shields_content_settings) {
    return;
  }
  g_huhi_shields_content_settings->DispatchSavedBandwidthToJava(savings);
}

// static
void HuhiShieldsContentSettings::DispatchBlockedEvent(int tab_id,
  const std::string& block_type, const std::string& subresource) {
  DCHECK(g_huhi_shields_content_settings);
  if (!g_huhi_shields_content_settings) {
    return;
  }
  g_huhi_shields_content_settings->DispatchBlockedEventToJava(tab_id,
      block_type, subresource);
}

void JNI_HuhiShieldsContentSettings_SetHuhiShieldsEnabled(JNIEnv* env,
    jboolean enabled,
    const base::android::JavaParamRef<jstring>& url,
    const base::android::JavaParamRef<jobject>& j_profile) {
  huhi_shields::SetHuhiShieldsEnabled(
      HostContentSettingsMapFactory::GetForProfile(
          ProfileAndroid::FromProfileAndroid(j_profile)),
      enabled,
      GURL(base::android::ConvertJavaStringToUTF8(env, url)),
      g_browser_process->local_state());
}

jboolean JNI_HuhiShieldsContentSettings_GetHuhiShieldsEnabled(JNIEnv* env,
    const base::android::JavaParamRef<jstring>& url,
    const base::android::JavaParamRef<jobject>& j_profile) {
  return huhi_shields::GetHuhiShieldsEnabled(
      HostContentSettingsMapFactory::GetForProfile(
          ProfileAndroid::FromProfileAndroid(j_profile)),
      GURL(base::android::ConvertJavaStringToUTF8(env, url)));
}

void JNI_HuhiShieldsContentSettings_SetAdControlType(JNIEnv* env,
    const base::android::JavaParamRef<jstring>& type,
    const base::android::JavaParamRef<jstring>& url,
    const base::android::JavaParamRef<jobject>& j_profile) {
  huhi_shields::SetAdControlType(
      HostContentSettingsMapFactory::GetForProfile(
          ProfileAndroid::FromProfileAndroid(j_profile)),
      huhi_shields::ControlTypeFromString(
          base::android::ConvertJavaStringToUTF8(env, type)),
      GURL(base::android::ConvertJavaStringToUTF8(env, url)),
      g_browser_process->local_state());
}

base::android::ScopedJavaLocalRef<jstring>
    JNI_HuhiShieldsContentSettings_GetAdControlType(JNIEnv* env,
    const base::android::JavaParamRef<jstring>& url,
    const base::android::JavaParamRef<jobject>& j_profile) {
  huhi_shields::ControlType control_type =
      huhi_shields::GetAdControlType(
          HostContentSettingsMapFactory::GetForProfile(
              ProfileAndroid::FromProfileAndroid(j_profile)),
          GURL(base::android::ConvertJavaStringToUTF8(env, url)));

  return base::android::ConvertUTF8ToJavaString(env,
      huhi_shields::ControlTypeToString(control_type));
}

void JNI_HuhiShieldsContentSettings_SetCookieControlType(JNIEnv* env,
    const base::android::JavaParamRef<jstring>& type,
    const base::android::JavaParamRef<jstring>& url,
    const base::android::JavaParamRef<jobject>& j_profile) {
  huhi_shields::SetCookieControlType(
      HostContentSettingsMapFactory::GetForProfile(
          ProfileAndroid::FromProfileAndroid(j_profile)),
      huhi_shields::ControlTypeFromString(
          base::android::ConvertJavaStringToUTF8(env, type)),
      GURL(base::android::ConvertJavaStringToUTF8(env, url)),
      g_browser_process->local_state());
}

base::android::ScopedJavaLocalRef<jstring>
    JNI_HuhiShieldsContentSettings_GetCookieControlType(JNIEnv* env,
    const base::android::JavaParamRef<jstring>& url,
    const base::android::JavaParamRef<jobject>& j_profile) {
  huhi_shields::ControlType control_type =
      huhi_shields::GetCookieControlType(
          HostContentSettingsMapFactory::GetForProfile(
              ProfileAndroid::FromProfileAndroid(j_profile)),
          GURL(base::android::ConvertJavaStringToUTF8(env, url)));

  return base::android::ConvertUTF8ToJavaString(env,
      huhi_shields::ControlTypeToString(control_type));
}

void JNI_HuhiShieldsContentSettings_SetFingerprintingControlType(JNIEnv* env,
    const base::android::JavaParamRef<jstring>& type,
    const base::android::JavaParamRef<jstring>& url,
    const base::android::JavaParamRef<jobject>& j_profile) {
  huhi_shields::SetFingerprintingControlType(
      HostContentSettingsMapFactory::GetForProfile(
          ProfileAndroid::FromProfileAndroid(j_profile)),
      huhi_shields::ControlTypeFromString(
          base::android::ConvertJavaStringToUTF8(env, type)),
      GURL(base::android::ConvertJavaStringToUTF8(env, url)),
      g_browser_process->local_state());
}

base::android::ScopedJavaLocalRef<jstring>
    JNI_HuhiShieldsContentSettings_GetFingerprintingControlType(JNIEnv* env,
    const base::android::JavaParamRef<jstring>& url,
    const base::android::JavaParamRef<jobject>& j_profile) {
  huhi_shields::ControlType control_type =
      huhi_shields::GetFingerprintingControlType(
          HostContentSettingsMapFactory::GetForProfile(
              ProfileAndroid::FromProfileAndroid(j_profile)),
          GURL(base::android::ConvertJavaStringToUTF8(env, url)));

  return base::android::ConvertUTF8ToJavaString(env,
      huhi_shields::ControlTypeToString(control_type));
}

void JNI_HuhiShieldsContentSettings_SetHTTPSEverywhereEnabled(JNIEnv* env,
    jboolean enabled,
    const base::android::JavaParamRef<jstring>& url,
    const base::android::JavaParamRef<jobject>& j_profile) {
  huhi_shields::SetHTTPSEverywhereEnabled(
      HostContentSettingsMapFactory::GetForProfile(
          ProfileAndroid::FromProfileAndroid(j_profile)),
      enabled,
      GURL(base::android::ConvertJavaStringToUTF8(env, url)),
      g_browser_process->local_state());
}

jboolean JNI_HuhiShieldsContentSettings_GetHTTPSEverywhereEnabled(JNIEnv* env,
    const base::android::JavaParamRef<jstring>& url,
    const base::android::JavaParamRef<jobject>& j_profile) {
  return huhi_shields::GetHTTPSEverywhereEnabled(
      HostContentSettingsMapFactory::GetForProfile(
          ProfileAndroid::FromProfileAndroid(j_profile)),
      GURL(base::android::ConvertJavaStringToUTF8(env, url)));
}

void JNI_HuhiShieldsContentSettings_SetNoScriptControlType(JNIEnv* env,
    const base::android::JavaParamRef<jstring>& type,
    const base::android::JavaParamRef<jstring>& url,
    const base::android::JavaParamRef<jobject>& j_profile) {
  huhi_shields::SetNoScriptControlType(
      HostContentSettingsMapFactory::GetForProfile(
          ProfileAndroid::FromProfileAndroid(j_profile)),
      huhi_shields::ControlTypeFromString(
          base::android::ConvertJavaStringToUTF8(env, type)),
      GURL(base::android::ConvertJavaStringToUTF8(env, url)),
      g_browser_process->local_state());
}

base::android::ScopedJavaLocalRef<jstring>
    JNI_HuhiShieldsContentSettings_GetNoScriptControlType(JNIEnv* env,
    const base::android::JavaParamRef<jstring>& url,
    const base::android::JavaParamRef<jobject>& j_profile) {
  huhi_shields::ControlType control_type =
      huhi_shields::GetNoScriptControlType(
          HostContentSettingsMapFactory::GetForProfile(
              ProfileAndroid::FromProfileAndroid(j_profile)),
          GURL(base::android::ConvertJavaStringToUTF8(env, url)));

  return base::android::ConvertUTF8ToJavaString(env,
      huhi_shields::ControlTypeToString(control_type));
}

}  // namespace android
}  // namespace chrome
