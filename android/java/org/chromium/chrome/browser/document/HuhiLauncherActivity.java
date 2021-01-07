/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.document;

import android.app.Activity;
import android.os.Bundle;

import org.chromium.chrome.browser.HuhiHelper;
import org.chromium.chrome.browser.preferences.SharedPreferencesManager;
import org.chromium.chrome.browser.toolbar.bottom.BottomToolbarConfiguration;

/**
 * Base class for ChromeLauncherActivity
 */
public class HuhiLauncherActivity extends Activity {
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Disable key checker to avoid asserts on Huhi keys in debug
        SharedPreferencesManager.getInstance().disableKeyCheckerForTesting();

        BottomToolbarConfiguration.isBottomToolbarEnabled();
        HuhiHelper.DisableFREDRP();
    }
}
