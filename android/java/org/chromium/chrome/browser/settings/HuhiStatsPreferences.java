/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.settings;

import android.content.SharedPreferences;
import android.os.Bundle;
import android.widget.Toast;

import androidx.preference.Preference;
import androidx.preference.Preference.OnPreferenceChangeListener;

import org.chromium.base.ContextUtils;
import org.chromium.base.task.AsyncTask;
import org.chromium.base.ThreadUtils;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.HuhiRelaunchUtils;
import org.chromium.chrome.browser.ntp_background_images.NTPBackgroundImagesBridge;
import org.chromium.chrome.browser.preferences.HuhiPrefServiceBridge;
import org.chromium.chrome.browser.settings.HuhiPreferenceFragment;
import org.chromium.components.browser_ui.settings.ChromeSwitchPreference;
import org.chromium.components.browser_ui.settings.SettingsUtils;
import org.chromium.chrome.browser.onboarding.OnboardingPrefManager;
import org.chromium.chrome.browser.local_database.DatabaseHelper;

/**
 * Fragment to keep track of all the display related preferences.
 */
public class HuhiStatsPreferences extends HuhiPreferenceFragment
    implements OnPreferenceChangeListener {

    // deprecated preferences from browser-android-tabs
    public static final String PREF_HUHI_STATS = "huhi_stats";
    public static final String PREF_HUHI_STATS_NOTIFICATION = "huhi_stats_notification";
    public static final String PREF_CLEAR_HUHI_STATS = "clear_huhi_stats";

    private ChromeSwitchPreference huhiStatsPref;
    private ChromeSwitchPreference huhiStatsNotificationPref;

    private DatabaseHelper mDatabaseHelper = DatabaseHelper.getInstance();

    private SharedPreferences sharedPreferences = ContextUtils.getAppSharedPreferences();
    private SharedPreferences.Editor sharedPreferencesEditor = sharedPreferences.edit();

    public static int getPreferenceSummary() {
        return OnboardingPrefManager.getInstance().isHuhiStatsEnabled() ? R.string.text_on : R.string.text_off;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getActivity().setTitle(R.string.huhi_stats);
        SettingsUtils.addPreferencesFromResource(this, R.xml.huhi_stats_preferences);
        findPreference(PREF_CLEAR_HUHI_STATS).setOnPreferenceClickListener(new Preference.OnPreferenceClickListener() {
            @Override
            public boolean onPreferenceClick(Preference preference) {
                new AsyncTask<Void>() {
                    @Override
                    protected Void doInBackground() {
                        try {
                            mDatabaseHelper.clearStatsTable();
                            mDatabaseHelper.clearSavedBandwidthTable();
                        } catch (Exception e) {
                            // Do nothing if url is invalid.
                            // Just return w/o showing shields popup.
                            return null;
                        }
                        return null;
                    }
                    @Override
                    protected void onPostExecute(Void result) {
                        assert ThreadUtils.runningOnUiThread();
                        if (isCancelled()) return;
                        Toast.makeText(ContextUtils.getApplicationContext(), ContextUtils.getApplicationContext().getResources().getString(R.string.data_has_been_cleared), Toast.LENGTH_SHORT).show();
                    }
                } .executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);
                return true;
            }
        });
    }

    private void removePreferenceIfPresent(String key) {
        Preference preference = getPreferenceScreen().findPreference(key);
        if (preference != null) getPreferenceScreen().removePreference(preference);
    }

    @Override
    public void onActivityCreated(Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        huhiStatsPref = (ChromeSwitchPreference) findPreference(PREF_HUHI_STATS);
        if (huhiStatsPref != null) {
            huhiStatsPref.setEnabled(true);
            huhiStatsPref.setChecked(OnboardingPrefManager.getInstance().isHuhiStatsEnabled());
            huhiStatsPref.setOnPreferenceChangeListener(this);
        }
        huhiStatsNotificationPref = (ChromeSwitchPreference) findPreference(PREF_HUHI_STATS_NOTIFICATION);
        if (huhiStatsNotificationPref != null) {
            huhiStatsNotificationPref.setEnabled(true);
            huhiStatsNotificationPref.setChecked(OnboardingPrefManager.getInstance().isHuhiStatsNotificationEnabled());
            huhiStatsNotificationPref.setOnPreferenceChangeListener(this);
        }
    }

    @Override
    public boolean onPreferenceChange(Preference preference, Object newValue) {
        setOnPreferenceValue(preference.getKey(), (boolean)newValue);
        return true;
    }

    public static void setOnPreferenceValue(String preferenceName, boolean newValue) {
        if (PREF_HUHI_STATS.equals(preferenceName)) {
            OnboardingPrefManager.getInstance().setHuhiStatsEnabled((boolean)newValue);
        } else if (PREF_HUHI_STATS_NOTIFICATION.equals(preferenceName)) {
            OnboardingPrefManager.getInstance().setHuhiStatsNotificationEnabled((boolean)newValue);
        } else {
            SharedPreferences sharedPreferences = ContextUtils.getAppSharedPreferences();
            SharedPreferences.Editor sharedPreferencesEditor = sharedPreferences.edit();
            sharedPreferencesEditor.putBoolean(preferenceName, newValue);
            sharedPreferencesEditor.apply();
        }
    }

    public static void setOnPreferenceValue(String preferenceName, int newValue) {
        SharedPreferences sharedPreferences = ContextUtils.getAppSharedPreferences();
        SharedPreferences.Editor sharedPreferencesEditor = sharedPreferences.edit();
        sharedPreferencesEditor.putInt(preferenceName, newValue);
        sharedPreferencesEditor.apply();
    }
}
