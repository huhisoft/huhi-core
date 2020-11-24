/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.sync.settings;

import android.os.Bundle;

import androidx.annotation.Nullable;
import androidx.preference.Preference;

import org.chromium.chrome.browser.sync.settings.ManageSyncSettings;
import org.chromium.chrome.browser.ui.huhi_tricks.checkbox_to_switch.CheckBoxPreference;

// See org.huhi.bytecode.HuhiManageSyncSettingsClassAdapter
public class HuhiManageSyncSettings extends ManageSyncSettings {
    private Preference mGoogleActivityControls;

    private Preference mSyncEncryption;

    private Preference mManageSyncData;

    private CheckBoxPreference mSyncPaymentsIntegration;

    @Override
    public void onCreatePreferences(@Nullable Bundle savedInstanceState, String rootKey) {
        super.onCreatePreferences(savedInstanceState, rootKey);

        getPreferenceScreen().removePreference(mGoogleActivityControls);
        getPreferenceScreen().removePreference(mSyncEncryption);
        getPreferenceScreen().removePreference(mManageSyncData);

        mSyncPaymentsIntegration.setVisible(false);
    }
}
