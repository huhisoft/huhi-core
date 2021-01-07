/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.settings;

import android.os.Bundle;
import androidx.preference.Preference;

import org.chromium.chrome.R;
import org.chromium.components.browser_ui.settings.ChromeSwitchPreference;
import org.chromium.components.browser_ui.settings.SettingsUtils;
import org.chromium.chrome.browser.settings.HuhiPreferenceFragment;
import org.chromium.chrome.browser.partnercustomizations.CloseHuhiManager;

public class ClosingAllTabsClosesHuhiPreference
        extends HuhiPreferenceFragment implements Preference.OnPreferenceChangeListener {
    private static final String CLOSING_ALL_TABS_CLOSES_HUHI_KEY = "closing_all_tabs_closes_huhi";

    public static int getPreferenceSummary() {
        return CloseHuhiManager.getClosingAllTabsClosesHuhiEnabled() ? R.string.text_on : R.string.text_off;
    }

    @Override
    public void onCreatePreferences(Bundle savedInstanceState, String rootKey) {
        getActivity().setTitle(R.string.prefs_closing_all_tabs_closes_huhi);
        SettingsUtils.addPreferencesFromResource(this, R.xml.closing_all_tabs_closes_huhi_preference);

        ChromeSwitchPreference pref =
                (ChromeSwitchPreference) findPreference(CLOSING_ALL_TABS_CLOSES_HUHI_KEY);
        pref.setChecked(CloseHuhiManager.getClosingAllTabsClosesHuhiEnabled());
        pref.setOnPreferenceChangeListener(this);
    }

    @Override
    public boolean onPreferenceChange(Preference preference, Object newValue) {
        CloseHuhiManager.setClosingAllTabsClosesHuhiEnabled((boolean) newValue);
        return true;
    }
}
