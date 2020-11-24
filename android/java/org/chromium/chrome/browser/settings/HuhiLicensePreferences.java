/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.settings;

import android.os.Bundle;

import org.chromium.base.Log;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.HuhiRewardsHelper;
import org.chromium.chrome.browser.settings.HuhiPreferenceFragment;
import org.chromium.components.browser_ui.settings.SettingsUtils;

import java.io.IOException;
import java.io.InputStream;
import java.util.Scanner;

/**
 * Fragment to display Huhi license information.
 */
public class HuhiLicensePreferences extends HuhiPreferenceFragment {
    private static final String TAG = "HuhiLicense";

    private static final String PREF_HUHI_LICENSE_TEXT = "huhi_license_text";
    private static final String ASSET_HUHI_LICENSE = "LICENSE.html";

    @Override
    public void onCreatePreferences(Bundle savedInstanceState, String s) {
        SettingsUtils.addPreferencesFromResource(this, R.xml.huhi_license_preferences);
        getActivity().setTitle(R.string.huhi_license_text);
        HuhiLicensePreference licenseText =
                (HuhiLicensePreference) findPreference(PREF_HUHI_LICENSE_TEXT);
        try {
            InputStream in = getActivity().getAssets().open(ASSET_HUHI_LICENSE);
            Scanner scanner = new Scanner(in).useDelimiter("\\A");
            String summary = scanner.hasNext() ? scanner.next() : "";
            in.close();
            licenseText.setSummary(HuhiRewardsHelper.spannedFromHtmlString(summary));
        } catch (IOException e) {
            Log.e(TAG, "Could not load license text: " + e);
        }
    }
}
