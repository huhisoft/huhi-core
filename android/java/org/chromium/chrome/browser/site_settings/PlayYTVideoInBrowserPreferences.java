/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.site_settings;

import android.os.Bundle;
import androidx.preference.Preference;

import org.chromium.chrome.R;
import org.chromium.chrome.browser.preferences.HuhiPrefServiceBridge;
import org.chromium.components.browser_ui.settings.ChromeSwitchPreference;
import org.chromium.components.browser_ui.settings.SettingsUtils;
import org.chromium.chrome.browser.settings.HuhiPreferenceFragment;

public class PlayYTVideoInBrowserPreferences
        extends HuhiPreferenceFragment implements Preference.OnPreferenceChangeListener {
    public static final String PLAY_YT_VIDEO_IN_BROWSER_KEY = "play_yt_video_in_browser";

    @Override
    public void onCreatePreferences(Bundle savedInstanceState, String rootKey) {
        getActivity().setTitle(R.string.settings_play_yt_video_in_browser_title);
        SettingsUtils.addPreferencesFromResource(this, R.xml.play_yt_video_in_browser_preferences);

        ChromeSwitchPreference pref =
                (ChromeSwitchPreference) findPreference(PLAY_YT_VIDEO_IN_BROWSER_KEY);
        // Initially enabled.
        pref.setChecked(
            HuhiPrefServiceBridge.getInstance().getPlayYTVideoInBrowserEnabled());
        pref.setOnPreferenceChangeListener(this);
    }

    @Override
    public boolean onPreferenceChange(Preference preference, Object newValue) {
        HuhiPrefServiceBridge.getInstance().setPlayYTVideoInBrowserEnabled((boolean) newValue);
        return true;
    }
}
