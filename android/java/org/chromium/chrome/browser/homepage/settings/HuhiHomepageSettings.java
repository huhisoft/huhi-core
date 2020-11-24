/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.homepage.settings;

import android.os.Bundle;

import org.chromium.chrome.browser.homepage.HomepageManager;
import org.chromium.components.browser_ui.settings.ChromeSwitchPreference;
import org.chromium.chrome.browser.homepage.settings.HomepageSettings;

public class HuhiHomepageSettings extends HomepageSettings {
    private HomepageManager mHomepageManager;

    @Override
    public void onCreatePreferences(Bundle savedInstanceState, String rootKey) {
        super.onCreatePreferences(savedInstanceState, rootKey);

        mHomepageManager = HomepageManager.getInstance();
        ChromeSwitchPreference homepageSwitch =
                (ChromeSwitchPreference) findPreference(PREF_HOMEPAGE_SWITCH);

        if (homepageSwitch.isVisible()) return;
        // Show homepage switch if it is hidden.
        homepageSwitch.setVisible(true);
        boolean isHomepageEnabled = HomepageManager.isHomepageEnabled();
        homepageSwitch.setChecked(isHomepageEnabled);
        homepageSwitch.setOnPreferenceChangeListener((preference, newValue) -> {
            mHomepageManager.setPrefHomepageEnabled((boolean) newValue);
            return true;
        });
    }
}
