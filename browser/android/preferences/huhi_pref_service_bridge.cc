/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 3.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/build/android/jni_headers/HuhiPrefServiceBridge_jni.h"

#include "build/build_config.h"
#include "base/android/jni_string.h"
#include "huhi/common/pref_names.h"
#include "huhi/components/huhi_perf_predictor/browser/buildflags.h"
#include "huhi/components/huhi_referrals/common/pref_names.h"
#include "huhi/components/huhi_rewards/common/pref_names.h"
#include "huhi/components/huhi_shields/browser/huhi_shields_util.h"
#include "huhi/components/huhi_sync/huhi_sync_prefs.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_android.h"
#include "chrome/browser/profiles/profile_manager.h"
#include "components/content_settings/core/browser/host_content_settings_map.h"
#include "components/prefs/pref_service.h"

#if BUILDFLAG(ENABLE_HUHI_PERF_PREDICTOR)
#include "huhi/components/huhi_perf_predictor/common/pref_names.h"
#endif

using base::android::ConvertUTF8ToJavaString;
using base::android::JavaParamRef;
using base::android::ScopedJavaLocalRef;
using huhi_shields::ControlType;

namespace {

Profile* GetOriginalProfile() {
  return ProfileManager::GetActiveUserProfile()->GetOriginalProfile();
}

}  // namespace

namespace chrome {
namespace android {

void JNI_HuhiPrefServiceBridge_SetHTTPSEEnabled(
    JNIEnv* env,
    jboolean enabled) {
  huhi_shields::SetHTTPSEverywhereEnabled(
      HostContentSettingsMapFactory::GetForProfile(
          GetOriginalProfile()),
      enabled,
      GURL(),
      g_browser_process->local_state());
}

void JNI_HuhiPrefServiceBridge_SetThirdPartyGoogleLoginEnabled(
    JNIEnv* env,
    jboolean enabled) {
  GetOriginalProfile()->GetPrefs()->SetBoolean(
      kGoogleLoginControlType, enabled);
}

void JNI_HuhiPrefServiceBridge_SetThirdPartyFacebookEmbedEnabled(
    JNIEnv* env,
    jboolean enabled) {
  GetOriginalProfile()->GetPrefs()->SetBoolean(
      kFBEmbedControlType, enabled);
}

void JNI_HuhiPrefServiceBridge_SetThirdPartyTwitterEmbedEnabled(
    JNIEnv* env,
    jboolean enabled) {
  GetOriginalProfile()->GetPrefs()->SetBoolean(
      kTwitterEmbedControlType, enabled);
}

void JNI_HuhiPrefServiceBridge_SetThirdPartyLinkedinEmbedEnabled(
    JNIEnv* env,
    jboolean enabled) {
  GetOriginalProfile()->GetPrefs()->SetBoolean(
      kLinkedInEmbedControlType, enabled);
}

void JNI_HuhiPrefServiceBridge_SetAdBlockEnabled(
    JNIEnv* env,
    jboolean enabled) {
  huhi_shields::SetAdControlType(
      HostContentSettingsMapFactory::GetForProfile(
          GetOriginalProfile()),
      static_cast<bool>(enabled) ? ControlType::BLOCK : ControlType::ALLOW,
      GURL(),
      g_browser_process->local_state());
}

void JNI_HuhiPrefServiceBridge_SetFingerprintingProtectionEnabled(
    JNIEnv* env,
    jboolean enabled) {
  huhi_shields::SetFingerprintingControlType(
      HostContentSettingsMapFactory::GetForProfile(
          GetOriginalProfile()),
      static_cast<bool>(enabled) ? ControlType::BLOCK : ControlType::ALLOW,
      GURL(),
      g_browser_process->local_state());
}

void JNI_HuhiPrefServiceBridge_SetPlayYTVideoInBrowserEnabled(
    JNIEnv* env,
    jboolean enabled) {
  return GetOriginalProfile()->GetPrefs()->SetBoolean(
      kPlayYTVideoInBrowserEnabled, enabled);
}

jboolean JNI_HuhiPrefServiceBridge_GetPlayYTVideoInBrowserEnabled(
    JNIEnv* env) {
  return GetOriginalProfile()->GetPrefs()->GetBoolean(
      kPlayYTVideoInBrowserEnabled);
}

void JNI_HuhiPrefServiceBridge_SetBackgroundVideoPlaybackEnabled(
    JNIEnv* env,
    jboolean enabled) {
  return GetOriginalProfile()->GetPrefs()->SetBoolean(
      kBackgroundVideoPlaybackEnabled,
      enabled);
}

jboolean JNI_HuhiPrefServiceBridge_GetBackgroundVideoPlaybackEnabled(
    JNIEnv* env) {
  return GetOriginalProfile()->GetPrefs()->GetBoolean(
      kBackgroundVideoPlaybackEnabled);
}

void JNI_HuhiPrefServiceBridge_SetDesktopModeEnabled(
    JNIEnv* env,
    jboolean enabled) {
  return GetOriginalProfile()->GetPrefs()->SetBoolean(kDesktopModeEnabled,
                                                      enabled);
}

jboolean JNI_HuhiPrefServiceBridge_GetDesktopModeEnabled(
    JNIEnv* env) {
  return GetOriginalProfile()->GetPrefs()->GetBoolean(kDesktopModeEnabled);
}

jlong JNI_HuhiPrefServiceBridge_GetTrackersBlockedCount(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile) {
  Profile* profile = ProfileAndroid::FromProfileAndroid(j_profile);
  return profile->GetPrefs()->GetUint64(kTrackersBlocked);
}

jlong JNI_HuhiPrefServiceBridge_GetAdsBlockedCount(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile) {
  Profile* profile = ProfileAndroid::FromProfileAndroid(j_profile);
  return profile->GetPrefs()->GetUint64(kAdsBlocked);
}

jlong JNI_HuhiPrefServiceBridge_GetDataSaved(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile) {
#if BUILDFLAG(ENABLE_HUHI_PERF_PREDICTOR)
  Profile* profile = ProfileAndroid::FromProfileAndroid(j_profile);
  return profile->GetPrefs()->GetUint64(
      huhi_perf_predictor::prefs::kBandwidthSavedBytes);
#endif
  return 0;
}

void JNI_HuhiPrefServiceBridge_SetOldTrackersBlockedCount(JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile,
    jlong count) {
  if (count <= 0) {
    return;
  }
  Profile* profile = ProfileAndroid::FromProfileAndroid(j_profile);
  profile->GetPrefs()->SetUint64(kTrackersBlocked,
    count + profile->GetPrefs()->GetUint64(kTrackersBlocked));
}

void JNI_HuhiPrefServiceBridge_SetOldAdsBlockedCount(JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile,
    jlong count) {
  if (count <= 0) {
    return;
  }
  Profile* profile = ProfileAndroid::FromProfileAndroid(j_profile);
  profile->GetPrefs()->SetUint64(kAdsBlocked,
    count + profile->GetPrefs()->GetUint64(kAdsBlocked));
}

void JNI_HuhiPrefServiceBridge_SetOldHttpsUpgradesCount(JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile,
    jlong count) {
  if (count <= 0) {
    return;
  }
  Profile* profile = ProfileAndroid::FromProfileAndroid(j_profile);
  profile->GetPrefs()->SetUint64(kHttpsUpgrades,
    count + profile->GetPrefs()->GetUint64(kHttpsUpgrades));
}

void JNI_HuhiPrefServiceBridge_SetSafetynetCheckFailed(
    JNIEnv* env,
    jboolean value) {
  GetOriginalProfile()->GetPrefs()->SetBoolean(kSafetynetCheckFailed, value);
}

jboolean JNI_HuhiPrefServiceBridge_GetSafetynetCheckFailed(JNIEnv* env) {
  return GetOriginalProfile()->GetPrefs()->GetBoolean(kSafetynetCheckFailed);
}

void JNI_HuhiPrefServiceBridge_SetSafetynetStatus(
    JNIEnv* env,
    const JavaParamRef<jstring>& status) {
  g_browser_process->local_state()->SetString(
      kSafetynetStatus, ConvertJavaStringToUTF8(env, status));
}

void JNI_HuhiPrefServiceBridge_SetUseRewardsStagingServer(
    JNIEnv* env,
    jboolean enabled) {
  GetOriginalProfile()->GetPrefs()->SetBoolean(
      huhi_rewards::prefs::kUseRewardsStagingServer, enabled);
}

void JNI_HuhiPrefServiceBridge_ResetPromotionLastFetchStamp(JNIEnv* env) {
  GetOriginalProfile()->GetPrefs()->SetUint64(
      huhi_rewards::prefs::kPromotionLastFetchStamp, 0);
}

jboolean JNI_HuhiPrefServiceBridge_GetUseRewardsStagingServer(JNIEnv* env) {
  return GetOriginalProfile()->GetPrefs()->GetBoolean(
      huhi_rewards::prefs::kUseRewardsStagingServer);
}

jboolean JNI_HuhiPrefServiceBridge_GetBooleanForContentSetting(JNIEnv* env,
    jint type) {
  HostContentSettingsMap* content_settings =
      HostContentSettingsMapFactory::GetForProfile(GetOriginalProfile());
  switch (content_settings->GetDefaultContentSetting((ContentSettingsType)type,
      nullptr)) {
    case CONTENT_SETTING_ALLOW:
      return true;
    case CONTENT_SETTING_BLOCK:
    default:
      return false;
  }

  return false;
}

void JNI_HuhiPrefServiceBridge_SetReferralAndroidFirstRunTimestamp(
    JNIEnv* env,
    jlong time) {
  return g_browser_process->local_state()->SetTime(
      kReferralAndroidFirstRunTimestamp, base::Time::FromJavaTime(time));
}

void JNI_HuhiPrefServiceBridge_SetReferralCheckedForPromoCodeFile(
    JNIEnv* env,
    jboolean value) {
  return g_browser_process->local_state()->SetBoolean(
      kReferralCheckedForPromoCodeFile, value);
}

void JNI_HuhiPrefServiceBridge_SetReferralInitialization(
    JNIEnv* env,
    jboolean value) {
  return g_browser_process->local_state()->SetBoolean(
      kReferralInitialization, value);
}

void JNI_HuhiPrefServiceBridge_SetReferralPromoCode(
    JNIEnv* env,
    const JavaParamRef<jstring>& promoCode) {
  return g_browser_process->local_state()->SetString(
      kReferralPromoCode, ConvertJavaStringToUTF8(env, promoCode));
}

void JNI_HuhiPrefServiceBridge_SetReferralDownloadId(
    JNIEnv* env,
    const JavaParamRef<jstring>& downloadId) {
  return g_browser_process->local_state()->SetString(
      kReferralDownloadID, ConvertJavaStringToUTF8(env, downloadId));
}

}  // namespace android
}  // namespace chrome
