/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.settings;

import android.content.Context;
import androidx.preference.DialogPreference;
import android.util.AttributeSet;

import org.chromium.chrome.R;

/**
 * The preference used to reset Huhi Rewards.
 */
public class HuhiRewardsResetPreference extends DialogPreference {
    /**
     * Constructor for HuhiRewardsResetPreference.
     */
    public HuhiRewardsResetPreference(Context context, AttributeSet attrs) {
        super(context, attrs);
        setDialogLayoutResource(R.layout.huhi_rewards_reset_tab_content);
    }
}
