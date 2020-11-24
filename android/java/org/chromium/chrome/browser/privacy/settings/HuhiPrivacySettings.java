/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.privacy.settings;

import android.content.SharedPreferences;
import android.os.Bundle;

import androidx.preference.Preference;

import org.chromium.base.ContextUtils;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.preferences.HuhiPref;
import org.chromium.chrome.browser.preferences.HuhiPrefServiceBridge;
import org.chromium.chrome.browser.preferences.Pref;
import org.chromium.chrome.browser.privacy.settings.PrivacySettings;
import org.chromium.chrome.browser.profiles.Profile;
import org.chromium.chrome.browser.settings.ChromeManagedPreferenceDelegate;
import org.chromium.components.browser_ui.settings.ChromeBaseCheckBoxPreference;
import org.chromium.components.browser_ui.settings.ChromeSwitchPreference;
import org.chromium.components.browser_ui.settings.SettingsUtils;
import org.chromium.components.prefs.PrefService;
import org.chromium.components.user_prefs.UserPrefs;

public class HuhiPrivacySettings extends PrivacySettings {
    private static final String PREF_HTTPSE = "httpse";
    private static final String PREF_AD_BLOCK = "ad_block";
    private static final String PREF_FINGERPRINTING_PROTECTION = "fingerprinting_protection";
    private static final String PREF_CLOSE_TABS_ON_EXIT = "close_tabs_on_exit";
    private static final String PREF_SYNC_AND_SERVICES_LINK = "sync_and_services_link";
    private static final String PREF_SEARCH_SUGGESTIONS = "search_suggestions";
    private static final String PREF_AUTOCOMPLETE_TOP_SITES = "autocomplete_top_sites";
    private static final String PREF_AUTOCOMPLETE_HUHI_SUGGESTED_SITES = "autocomplete_huhi_suggested_sites";
    private static final String PREF_CLEAR_BROWSING_DATA = "clear_browsing_data";

    private final PrefService mPrefServiceBridge = UserPrefs.get(Profile.getLastUsedRegularProfile());
    private final ChromeManagedPreferenceDelegate mManagedPreferenceDelegate =
            createManagedPreferenceDelegate();
    private ChromeSwitchPreference mSearchSuggestions;
    private ChromeSwitchPreference mAutocompleteTopSites;
    private ChromeSwitchPreference mAutocompleteHuhiSuggestedSites;
    private ChromeBaseCheckBoxPreference mHttpsePref;
    private ChromeBaseCheckBoxPreference mAdBlockPref;
    private ChromeBaseCheckBoxPreference mFingerprintingProtectionPref;
    private ChromeBaseCheckBoxPreference mCloseTabsOnExitPref;

    @Override
    public void onCreatePreferences(Bundle savedInstanceState, String rootKey) {
        super.onCreatePreferences(savedInstanceState, rootKey);

        SettingsUtils.addPreferencesFromResource(this, R.xml.huhi_privacy_preferences);

        mHttpsePref = (ChromeBaseCheckBoxPreference) findPreference(PREF_HTTPSE);
        mHttpsePref.setOnPreferenceChangeListener(this);

        mAdBlockPref = (ChromeBaseCheckBoxPreference) findPreference(PREF_AD_BLOCK);
        mAdBlockPref.setOnPreferenceChangeListener(this);

        mFingerprintingProtectionPref =
                (ChromeBaseCheckBoxPreference) findPreference(PREF_FINGERPRINTING_PROTECTION);
        mFingerprintingProtectionPref.setOnPreferenceChangeListener(this);

        mCloseTabsOnExitPref =
                (ChromeBaseCheckBoxPreference) findPreference(PREF_CLOSE_TABS_ON_EXIT);
        mCloseTabsOnExitPref.setOnPreferenceChangeListener(this);

        mSearchSuggestions = (ChromeSwitchPreference) findPreference(PREF_SEARCH_SUGGESTIONS);
        mSearchSuggestions.setOnPreferenceChangeListener(this);
        mSearchSuggestions.setManagedPreferenceDelegate(mManagedPreferenceDelegate);

        mAutocompleteTopSites = (ChromeSwitchPreference) findPreference(PREF_AUTOCOMPLETE_TOP_SITES);
        mAutocompleteTopSites.setOnPreferenceChangeListener(this);

        mAutocompleteHuhiSuggestedSites = (ChromeSwitchPreference) findPreference(PREF_AUTOCOMPLETE_HUHI_SUGGESTED_SITES);
        mAutocompleteHuhiSuggestedSites.setOnPreferenceChangeListener(this);

        updatePreferences();
    }

    @Override
    public boolean onPreferenceChange(Preference preference, Object newValue) {
        super.onPreferenceChange(preference, newValue);

        String key = preference.getKey();
        if (PREF_HTTPSE.equals(key)) {
            HuhiPrefServiceBridge.getInstance().setHTTPSEEnabled((boolean) newValue);
        } else if (PREF_AD_BLOCK.equals(key)) {
            HuhiPrefServiceBridge.getInstance().setAdBlockEnabled((boolean) newValue);
        } else if (PREF_FINGERPRINTING_PROTECTION.equals(key)) {
            HuhiPrefServiceBridge.getInstance().setFingerprintingProtectionEnabled(
                    (boolean) newValue);
        } else if (PREF_CLOSE_TABS_ON_EXIT.equals(key)) {
            SharedPreferences.Editor sharedPreferencesEditor =
                    ContextUtils.getAppSharedPreferences().edit();
            sharedPreferencesEditor.putBoolean(PREF_CLOSE_TABS_ON_EXIT, (boolean) newValue);
            sharedPreferencesEditor.apply();
        } else if (PREF_SEARCH_SUGGESTIONS.equals(key)) {
            mPrefServiceBridge.setBoolean(Pref.SEARCH_SUGGEST_ENABLED, (boolean) newValue);
        } else if (PREF_AUTOCOMPLETE_TOP_SITES.equals(key)) {
            UserPrefs.get(Profile.getLastUsedRegularProfile()).setBoolean(HuhiPref.TOP_SITE_SUGGESTIONS_ENABLED, (boolean) newValue);
        } else if (PREF_AUTOCOMPLETE_HUHI_SUGGESTED_SITES.equals(key)) {
            UserPrefs.get(Profile.getLastUsedRegularProfile()).setBoolean(HuhiPref.HUHI_SUGGESTED_SITE_SUGGESTIONS_ENABLED,
                    (boolean) newValue);
        }

        return true;
    }

    @Override
    public void onResume() {
        super.onResume();
        updatePreferences();
    }

    private void updatePreferences() {
        removePreferenceIfPresent(PREF_SYNC_AND_SERVICES_LINK);
        mSearchSuggestions.setChecked(mPrefServiceBridge.getBoolean(Pref.SEARCH_SUGGEST_ENABLED));
        int order = findPreference(PREF_CLEAR_BROWSING_DATA).getOrder();
        mCloseTabsOnExitPref.setOrder(++order);
        mHttpsePref.setOrder(++order);
        mAdBlockPref.setOrder(++order);
        mFingerprintingProtectionPref.setOrder(++order);
        mSearchSuggestions.setOrder(++order);
        mAutocompleteTopSites
                .setChecked(UserPrefs.get(Profile.getLastUsedRegularProfile()).getBoolean(HuhiPref.TOP_SITE_SUGGESTIONS_ENABLED));
        mAutocompleteTopSites.setOrder(++order);
        mAutocompleteHuhiSuggestedSites.setChecked(
                UserPrefs.get(Profile.getLastUsedRegularProfile()).getBoolean(HuhiPref.HUHI_SUGGESTED_SITE_SUGGESTIONS_ENABLED));
        mAutocompleteHuhiSuggestedSites.setOrder(++order);
    }

    private void removePreferenceIfPresent(String key) {
        Preference preference = getPreferenceScreen().findPreference(key);
        if (preference != null) {
            getPreferenceScreen().removePreference(preference);
        }
    }

    private ChromeManagedPreferenceDelegate createManagedPreferenceDelegate() {
        return preference -> {
            String key = preference.getKey();
            if (PREF_SEARCH_SUGGESTIONS.equals(key)) {
                return mPrefServiceBridge.isManagedPreference(Pref.SEARCH_SUGGEST_ENABLED);
            }
            return false;
        };
    }
}
