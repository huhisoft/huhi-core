/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.settings;

import android.os.Bundle;
import androidx.preference.PreferenceDialogFragmentCompat;
import android.view.View;

import org.chromium.chrome.browser.HuhiRewardsNativeWorker;

/**
 * The dialog used to reset Huhi Rewards.
 */
public class HuhiRewardsResetPreferenceDialog extends PreferenceDialogFragmentCompat {
    public static final String TAG = "HuhiRewardsResetPreferenceDialog";

    public static HuhiRewardsResetPreferenceDialog newInstance(
            HuhiRewardsResetPreference preference) {
        HuhiRewardsResetPreferenceDialog fragment = new HuhiRewardsResetPreferenceDialog();
        Bundle bundle = new Bundle(1);
        bundle.putString(PreferenceDialogFragmentCompat.ARG_KEY, preference.getKey());
        fragment.setArguments(bundle);
        return fragment;
    }

    @Override
    protected void onBindDialogView(View view) {
        super.onBindDialogView(view);
    }

    @Override
    public void onDialogClosed(boolean positive) {
        if (positive) {
            HuhiRewardsNativeWorker.getInstance().SetRewardsMainEnabled(false);
        }
    }
}
