/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.preferences.website;

import org.chromium.base.annotations.CalledByNative;
import org.chromium.base.annotations.JNINamespace;
import org.chromium.base.annotations.NativeMethods;
import org.chromium.chrome.browser.preferences.website.HuhiShieldsContentSettingsObserver;
import org.chromium.chrome.browser.profiles.Profile;

import java.util.ArrayList;
import java.util.List;

@JNINamespace("chrome::android")
public class HuhiShieldsContentSettings {
    static public final String RESOURCE_IDENTIFIER_ADS = "ads";
    static public final String RESOURCE_IDENTIFIER_TRACKERS = "trackers";
    static public final String RESOURCE_IDENTIFIER_ADS_TRACKERS = "ads_trackers";
    static public final String RESOURCE_IDENTIFIER_DATA_SAVED = "data_saved";
    static public final String RESOURCE_IDENTIFIER_HTTP_UPGRADABLE_RESOURCES = "httpUpgradableResources";
    static public final String RESOURCE_IDENTIFIER_HUHI_SHIELDS = "huhiShields";
    static public final String RESOURCE_IDENTIFIER_FINGERPRINTING = "fingerprinting";
    static public final String RESOURCE_IDENTIFIER_COOKIES = "cookies";
    static public final String RESOURCE_IDENTIFIER_REFERRERS = "referrers";
    static public final String RESOURCE_IDENTIFIER_JAVASCRIPTS = "javascript";

    static public final String BLOCK_RESOURCE = "block";
    static public final String BLOCK_THIRDPARTY_RESOURCE = "block_third_party";
    static public final String DEFAULT = "default";
    static public final String ALLOW_RESOURCE = "allow";

    private long mNativeHuhiShieldsContentSettings;
    private List<HuhiShieldsContentSettingsObserver> mHuhiShieldsContentSettingsObservers;
    private static HuhiShieldsContentSettings sInstance;

    public static HuhiShieldsContentSettings getInstance() {
        if (sInstance == null) sInstance = new HuhiShieldsContentSettings();
        return sInstance;
    }

    private HuhiShieldsContentSettings() {
        mNativeHuhiShieldsContentSettings = 0;
        mHuhiShieldsContentSettingsObservers =
            new ArrayList<HuhiShieldsContentSettingsObserver>();
        init();
    }

    public void addObserver(HuhiShieldsContentSettingsObserver observer) {
        mHuhiShieldsContentSettingsObservers.add(observer);
    }

    public void removeObserver(HuhiShieldsContentSettingsObserver observer) {
        mHuhiShieldsContentSettingsObservers.remove(observer);
    }

    private void init() {
        if (mNativeHuhiShieldsContentSettings == 0) {
            HuhiShieldsContentSettingsJni.get().init(this);
        }
    }

    @Override
    protected void finalize() {
        destroy();
    }

    private void destroy() {
        if (mNativeHuhiShieldsContentSettings == 0) {
            return;
        }
        HuhiShieldsContentSettingsJni.get().destroy(mNativeHuhiShieldsContentSettings);
    }

    static public void setShields(Profile profile, String host, String resourceIndentifier, boolean value,
                                  boolean fromTopShields) {
        String setting_string = (value ? BLOCK_RESOURCE : ALLOW_RESOURCE);
        if (resourceIndentifier.equals(RESOURCE_IDENTIFIER_HUHI_SHIELDS)) {
            HuhiShieldsContentSettingsJni.get().setHuhiShieldsEnabled(value, host, profile);
        } else if (resourceIndentifier.equals(RESOURCE_IDENTIFIER_ADS_TRACKERS)) {
            HuhiShieldsContentSettingsJni.get().setAdControlType(setting_string, host, profile);
        } else if (resourceIndentifier.equals(RESOURCE_IDENTIFIER_HTTP_UPGRADABLE_RESOURCES)) {
            HuhiShieldsContentSettingsJni.get().setHTTPSEverywhereEnabled(value, host, profile);
        } else if (resourceIndentifier.equals(RESOURCE_IDENTIFIER_JAVASCRIPTS)) {
            HuhiShieldsContentSettingsJni.get().setNoScriptControlType(setting_string, host, profile);
        }
    }

    public static void setShieldsValue(Profile profile, String host, String resourceIndentifier,
                                       String settingOption, boolean fromTopShields) {
        if (resourceIndentifier.equals(RESOURCE_IDENTIFIER_FINGERPRINTING)) {
            HuhiShieldsContentSettingsJni.get().setFingerprintingControlType(settingOption, host, profile);
        } else if (resourceIndentifier.equals(RESOURCE_IDENTIFIER_COOKIES)) {
            HuhiShieldsContentSettingsJni.get().setCookieControlType(settingOption, host, profile);
        }
    }

    public static boolean getShields(Profile profile, String host, String resourceIndentifier) {
        String settings = BLOCK_RESOURCE;
        if (resourceIndentifier.equals(RESOURCE_IDENTIFIER_HUHI_SHIELDS)) {
            return HuhiShieldsContentSettingsJni.get().getHuhiShieldsEnabled(host, profile);
        } else if (resourceIndentifier.equals(RESOURCE_IDENTIFIER_ADS_TRACKERS)) {
            settings = HuhiShieldsContentSettingsJni.get().getAdControlType(host, profile);
        } else if (resourceIndentifier.equals(RESOURCE_IDENTIFIER_HTTP_UPGRADABLE_RESOURCES)) {
            return HuhiShieldsContentSettingsJni.get().getHTTPSEverywhereEnabled(host, profile);
        } else if (resourceIndentifier.equals(RESOURCE_IDENTIFIER_JAVASCRIPTS)) {
            settings = HuhiShieldsContentSettingsJni.get().getNoScriptControlType(host, profile);
        }

        return !settings.equals(ALLOW_RESOURCE);
    }

    public static String getShieldsValue(Profile profile, String host, String resourceIndentifier) {
        String settings = BLOCK_RESOURCE;
        if (resourceIndentifier.equals(RESOURCE_IDENTIFIER_FINGERPRINTING)) {
            settings = HuhiShieldsContentSettingsJni.get().getFingerprintingControlType(host, profile);
        } else if (resourceIndentifier.equals(RESOURCE_IDENTIFIER_COOKIES)) {
            settings = HuhiShieldsContentSettingsJni.get().getCookieControlType(host, profile);
        }
        return settings;
    }

    @CalledByNative
    private void setNativePtr(long nativePtr) {
        assert mNativeHuhiShieldsContentSettings == 0;
        mNativeHuhiShieldsContentSettings = nativePtr;
    }

    @CalledByNative
    private void blockedEvent(int tabId, String block_type, String subresource) {
        for (HuhiShieldsContentSettingsObserver observer : mHuhiShieldsContentSettingsObservers) {
            observer.blockEvent(tabId, block_type, subresource);
        }
    }

    @CalledByNative
    private void savedBandwidth(long savings) {
        for (HuhiShieldsContentSettingsObserver observer : mHuhiShieldsContentSettingsObservers) {
            observer.savedBandwidth(savings);
        }
    }

    @NativeMethods
    interface Natives {
        void init(HuhiShieldsContentSettings self);
        void destroy(long nativeHuhiShieldsContentSettings);

        void setHuhiShieldsEnabled(boolean enabled, String url, Profile profile);
        boolean getHuhiShieldsEnabled(String url, Profile profile);
        void setAdControlType(String type, String url, Profile profile);
        String getAdControlType(String url, Profile profile);
        void setCookieControlType(String type, String url, Profile profile);
        String getCookieControlType(String url, Profile profile);
        void setFingerprintingControlType(String type, String url, Profile profile);
        String getFingerprintingControlType(String url, Profile profile);
        void setHTTPSEverywhereEnabled(boolean enabled, String url, Profile profile);
        boolean getHTTPSEverywhereEnabled(String url, Profile profile);
        void setNoScriptControlType(String type, String url, Profile profile);
        String getNoScriptControlType(String url, Profile profile);
    }
}
