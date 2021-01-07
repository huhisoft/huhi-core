/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.settings;

import static org.chromium.chrome.browser.settings.MainSettings.PREF_UI_THEME;

import android.content.SharedPreferences;
import android.os.Bundle;

import androidx.preference.Preference;

import org.chromium.base.ContextUtils;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.HuhiFeatureList;
import org.chromium.chrome.browser.HuhiRelaunchUtils;
import org.chromium.chrome.browser.HuhiRewardsNativeWorker;
import org.chromium.chrome.browser.HuhiRewardsObserver;
import org.chromium.chrome.browser.flags.ChromeFeatureList;
import org.chromium.chrome.browser.night_mode.NightModeUtils;
import org.chromium.chrome.browser.preferences.HuhiPreferenceKeys;
import org.chromium.chrome.browser.settings.HuhiPreferenceFragment;
import org.chromium.chrome.browser.toolbar.bottom.BottomToolbarConfiguration;
import org.chromium.components.browser_ui.settings.ChromeSwitchPreference;
import org.chromium.components.browser_ui.settings.SettingsUtils;
import org.chromium.ui.base.DeviceFormFactor;

public class AppearancePreferences extends HuhiPreferenceFragment
        implements Preference.OnPreferenceChangeListener, HuhiRewardsObserver {
    public static final String PREF_HIDE_HUHI_REWARDS_ICON = "hide_huhi_rewards_icon";
    public static final String PREF_HUHI_NIGHT_MODE_ENABLED = "huhi_night_mode_enabled_key";
    private HuhiRewardsNativeWorker mHuhiRewardsNativeWorker;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getActivity().setTitle(R.string.prefs_appearance);
        SettingsUtils.addPreferencesFromResource(this, R.xml.appearance_preferences);
        boolean isTablet = DeviceFormFactor.isNonMultiDisplayContextOnTablet(
                ContextUtils.getApplicationContext());
        if (isTablet) {
            removePreferenceIfPresent(HuhiPreferenceKeys.HUHI_BOTTOM_TOOLBAR_ENABLED_KEY);
        }

        if (!NightModeUtils.isNightModeSupported()) {
            removePreferenceIfPresent(PREF_UI_THEME);
        }

        if (!ChromeFeatureList.isEnabled(HuhiFeatureList.HUHI_REWARDS)) {
            removePreferenceIfPresent(PREF_HIDE_HUHI_REWARDS_ICON);
        }
    }

    @Override
    public void onCreatePreferences(Bundle savedInstanceState, String rootKey) {}

    private void removePreferenceIfPresent(String key) {
        Preference preference = getPreferenceScreen().findPreference(key);
        if (preference != null) getPreferenceScreen().removePreference(preference);
    }

    @Override
    public void onActivityCreated(Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);

        ChromeSwitchPreference hideHuhiRewardsIconPref = (ChromeSwitchPreference) findPreference(PREF_HIDE_HUHI_REWARDS_ICON);
        if (hideHuhiRewardsIconPref != null) {
            SharedPreferences sharedPreferences = ContextUtils.getAppSharedPreferences();
            hideHuhiRewardsIconPref.setChecked(sharedPreferences.getBoolean(PREF_HIDE_HUHI_REWARDS_ICON, false));
            hideHuhiRewardsIconPref.setOnPreferenceChangeListener(this);
        }

        Preference nightModeEnabled =
                findPreference(PREF_HUHI_NIGHT_MODE_ENABLED);
        nightModeEnabled.setOnPreferenceChangeListener(this);
        if (nightModeEnabled instanceof ChromeSwitchPreference) {
            ((ChromeSwitchPreference) nightModeEnabled)
                    .setChecked(ChromeFeatureList.isEnabled(
                        HuhiFeatureList.FORCE_WEB_CONTENTS_DARK_MODE));
        }

        Preference enableBottomToolbar =
                findPreference(HuhiPreferenceKeys.HUHI_BOTTOM_TOOLBAR_ENABLED_KEY);
        if (enableBottomToolbar == null) return;

        enableBottomToolbar.setOnPreferenceChangeListener(this);
        if (enableBottomToolbar instanceof ChromeSwitchPreference) {
            boolean isTablet = DeviceFormFactor.isNonMultiDisplayContextOnTablet(
                    ContextUtils.getApplicationContext());
            ((ChromeSwitchPreference) enableBottomToolbar)
                    .setChecked(!isTablet
                            && BottomToolbarConfiguration.isBottomToolbarEnabled());
        }
    }

    @Override
    public void onStart() {
        mHuhiRewardsNativeWorker = HuhiRewardsNativeWorker.getInstance();
        if (mHuhiRewardsNativeWorker != null) {
            mHuhiRewardsNativeWorker.AddObserver(this);
        }
        super.onStart();
    }

    @Override
    public void onStop() {
        if (mHuhiRewardsNativeWorker != null) {
            mHuhiRewardsNativeWorker.RemoveObserver(this);
        }
        super.onStop();
    }

    @Override
    public boolean onPreferenceChange(Preference preference, Object newValue) {
        String key = preference.getKey();
        if (HuhiPreferenceKeys.HUHI_BOTTOM_TOOLBAR_ENABLED_KEY.equals(key)) {
            SharedPreferences prefs = ContextUtils.getAppSharedPreferences();
            Boolean originalStatus = BottomToolbarConfiguration.isBottomToolbarEnabled();
            prefs.edit()
                    .putBoolean(HuhiPreferenceKeys.HUHI_BOTTOM_TOOLBAR_ENABLED_KEY,
                            !originalStatus)
                    .apply();
            HuhiRelaunchUtils.askForRelaunch(getActivity());
        } else if (PREF_HIDE_HUHI_REWARDS_ICON.equals(key)) {
            SharedPreferences sharedPreferences = ContextUtils.getAppSharedPreferences();
            SharedPreferences.Editor sharedPreferencesEditor = sharedPreferences.edit();
            sharedPreferencesEditor.putBoolean(PREF_HIDE_HUHI_REWARDS_ICON, !(boolean) newValue);
            sharedPreferencesEditor.apply();
            HuhiRelaunchUtils.askForRelaunch(getActivity());
        } else if (PREF_HUHI_NIGHT_MODE_ENABLED.equals(key)) {
            HuhiFeatureList.enableFeature(
                HuhiFeatureList.ENABLE_FORCE_DARK, (boolean) newValue);
            HuhiRelaunchUtils.askForRelaunch(getActivity());
        }

        return true;
    }
}
