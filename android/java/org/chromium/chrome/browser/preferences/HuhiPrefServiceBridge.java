/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.preferences;

import androidx.annotation.NonNull;

import org.chromium.base.ThreadUtils;
import org.chromium.base.annotations.JNINamespace;
import org.chromium.base.annotations.NativeMethods;
import org.chromium.chrome.browser.profiles.Profile;

@JNINamespace("chrome::android")
public class HuhiPrefServiceBridge {
    private HuhiPrefServiceBridge() {
    }

    private static HuhiPrefServiceBridge sInstance;

    public static HuhiPrefServiceBridge getInstance() {
        ThreadUtils.assertOnUiThread();
        if (sInstance == null) {
            sInstance = new HuhiPrefServiceBridge();
        }
        return sInstance;
    }

    /**
     * @param whether HTTPSE should be enabled.
     */
    public void setHTTPSEEnabled(boolean enabled) {
        HuhiPrefServiceBridgeJni.get().setHTTPSEEnabled(enabled);
    }

    /**
     * @param whether google login is enabled on third party sites.
     */
    public void setThirdPartyGoogleLoginEnabled(boolean enabled) {
        HuhiPrefServiceBridgeJni.get().setThirdPartyGoogleLoginEnabled(enabled);
    }

    /**
     * @param whether facebook embeds are allowed on third party sites.
     */
    public void setThirdPartyFacebookEmbedEnabled(boolean enabled) {
        HuhiPrefServiceBridgeJni.get().setThirdPartyFacebookEmbedEnabled(enabled);
    }

    /**
     * @param whether twitter embeds are allowed on third party sites.
     */
    public void setThirdPartyTwitterEmbedEnabled(boolean enabled) {
        HuhiPrefServiceBridgeJni.get().setThirdPartyTwitterEmbedEnabled(enabled);
    }

    /**
     * @param whether linkedin embeds are allowed on third party sites.
     */
    public void setThirdPartyLinkedinEmbedEnabled(boolean enabled) {
        HuhiPrefServiceBridgeJni.get().setThirdPartyLinkedinEmbedEnabled(enabled);
    }

    /**
     * @param whether AdBlock should be enabled.
     */
    public void setAdBlockEnabled(boolean enabled) {
        HuhiPrefServiceBridgeJni.get().setAdBlockEnabled(enabled);
    }

    /**
     * @param whether Fingerprinting Protection should be enabled.
     */
    public void setFingerprintingProtectionEnabled(boolean enabled) {
        HuhiPrefServiceBridgeJni.get().setFingerprintingProtectionEnabled(enabled);
    }

    public void setPlayYTVideoInBrowserEnabled(boolean enabled) {
        HuhiPrefServiceBridgeJni.get().setPlayYTVideoInBrowserEnabled(enabled);
    }

    public boolean getPlayYTVideoInBrowserEnabled() {
        return HuhiPrefServiceBridgeJni.get().getPlayYTVideoInBrowserEnabled();
    }

    public void setDesktopModeEnabled(boolean enabled) {
        HuhiPrefServiceBridgeJni.get().setDesktopModeEnabled(enabled);
    }

    public boolean getDesktopModeEnabled() {
        return HuhiPrefServiceBridgeJni.get().getDesktopModeEnabled();
    }

    public void setBackgroundVideoPlaybackEnabled(boolean enabled) {
        HuhiPrefServiceBridgeJni.get().setBackgroundVideoPlaybackEnabled(enabled);
    }

    public boolean getBackgroundVideoPlaybackEnabled() {
        return HuhiPrefServiceBridgeJni.get().getBackgroundVideoPlaybackEnabled();
    }

    public long getTrackersBlockedCount(Profile profile) {
        return HuhiPrefServiceBridgeJni.get().getTrackersBlockedCount(profile);
    }

    public long getAdsBlockedCount(Profile profile) {
        return HuhiPrefServiceBridgeJni.get().getAdsBlockedCount(profile);
    }

    public long getDataSaved(Profile profile) {
        return HuhiPrefServiceBridgeJni.get().getDataSaved(profile);
    }

    /**
     * @param whether SafetyNet check failed.
     */
    public void setSafetynetCheckFailed(boolean value) {
        HuhiPrefServiceBridgeJni.get().setSafetynetCheckFailed(value);
    }

    public boolean getSafetynetCheckFailed() {
        return HuhiPrefServiceBridgeJni.get().getSafetynetCheckFailed();
    }

    public void setSafetynetStatus(String status) {
        HuhiPrefServiceBridgeJni.get().setSafetynetStatus(status);
    }

    public void setUseRewardsStagingServer(boolean enabled) {
        HuhiPrefServiceBridgeJni.get().setUseRewardsStagingServer(enabled);
    }

    public void resetPromotionLastFetchStamp() {
        HuhiPrefServiceBridgeJni.get().resetPromotionLastFetchStamp();
    }

    public boolean getUseRewardsStagingServer() {
        return HuhiPrefServiceBridgeJni.get().getUseRewardsStagingServer();
    }

    public void setOldTrackersBlockedCount(Profile profile, long count) {
        HuhiPrefServiceBridgeJni.get().setOldTrackersBlockedCount(profile, count);
    }

    public void setOldAdsBlockedCount(Profile profile, long count) {
        HuhiPrefServiceBridgeJni.get().setOldAdsBlockedCount(profile, count);
    }

    public void setOldHttpsUpgradesCount(Profile profile, long count) {
        HuhiPrefServiceBridgeJni.get().setOldHttpsUpgradesCount(profile, count);
    }

    public boolean GetBooleanForContentSetting(int content_type) {
        return HuhiPrefServiceBridgeJni.get().getBooleanForContentSetting(content_type);
    }

    public void setReferralAndroidFirstRunTimestamp(long time) {
        HuhiPrefServiceBridgeJni.get().setReferralAndroidFirstRunTimestamp(time);
    }

    public void setReferralCheckedForPromoCodeFile(boolean value) {
        HuhiPrefServiceBridgeJni.get().setReferralCheckedForPromoCodeFile(value);
    }

    public void setReferralInitialization(boolean value) {
        HuhiPrefServiceBridgeJni.get().setReferralInitialization(value);
    }

    public void setReferralPromoCode(String promoCode) {
        HuhiPrefServiceBridgeJni.get().setReferralPromoCode(promoCode);
    }

    public void setReferralDownloadId(String downloadId) {
        HuhiPrefServiceBridgeJni.get().setReferralDownloadId(downloadId);
    }

    @NativeMethods
    interface Natives {
        void setHTTPSEEnabled(boolean enabled);
        void setAdBlockEnabled(boolean enabled);
        void setFingerprintingProtectionEnabled(boolean enabled);

        void setThirdPartyGoogleLoginEnabled(boolean enabled);
        void setThirdPartyFacebookEmbedEnabled(boolean enabled);
        void setThirdPartyTwitterEmbedEnabled(boolean enabled);
        void setThirdPartyLinkedinEmbedEnabled(boolean enabled);

        void setPlayYTVideoInBrowserEnabled(boolean enabled);
        boolean getPlayYTVideoInBrowserEnabled();

        void setDesktopModeEnabled(boolean enabled);
        boolean getDesktopModeEnabled();

        void setBackgroundVideoPlaybackEnabled(boolean enabled);
        boolean getBackgroundVideoPlaybackEnabled();

        long getTrackersBlockedCount(Profile profile);
        long getAdsBlockedCount(Profile profile);
        long getDataSaved(Profile profile);

        // Used to pass total stat from upgrading old tabs based browser
        // to a new core based
        void setOldTrackersBlockedCount(Profile profile, long count);
        void setOldAdsBlockedCount(Profile profile, long count);
        void setOldHttpsUpgradesCount(Profile profile, long count);

        void setSafetynetCheckFailed(boolean value);
        boolean getSafetynetCheckFailed();

        void setSafetynetStatus(String status);

        void setUseRewardsStagingServer(boolean enabled);
        void resetPromotionLastFetchStamp();
        boolean getUseRewardsStagingServer();
        boolean getBooleanForContentSetting(int content_type);

        void setReferralAndroidFirstRunTimestamp(long time);
        void setReferralCheckedForPromoCodeFile(boolean value);
        void setReferralInitialization(boolean value);
        void setReferralPromoCode(String promoCode);
        void setReferralDownloadId(String downloadId);
    }
}
