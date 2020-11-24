/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.toolbar.bottom;

import android.app.Activity;
import android.content.SharedPreferences;
import android.graphics.Point;
import android.view.Display;

import org.chromium.base.ApplicationStatus;
import org.chromium.base.ContextUtils;
import org.chromium.chrome.browser.app.ChromeActivity;
import org.chromium.chrome.browser.preferences.HuhiPreferenceKeys;
import org.chromium.chrome.browser.preferences.SharedPreferencesManager;

public class HuhiBottomToolbarConfiguration {
    private static final int SMALL_SCREEN_WIDTH = 360;
    private static final int SMALL_SCREEN_HEIGHT = 640;

    public static boolean isBottomToolbarEnabled() {
        SharedPreferences sharedPreferences = ContextUtils.getAppSharedPreferences();
        if (sharedPreferences.getBoolean(
                    HuhiPreferenceKeys.HUHI_BOTTOM_TOOLBAR_SET_KEY, false)) {
            return sharedPreferences.getBoolean(
                    HuhiPreferenceKeys.HUHI_BOTTOM_TOOLBAR_ENABLED_KEY, true);
        } else {
            SharedPreferencesManager.getInstance().writeBoolean(
                    HuhiPreferenceKeys.HUHI_BOTTOM_TOOLBAR_SET_KEY, true);
            boolean enable = true;
            if (isSmallScreen()) {
                enable = false;
            }
            SharedPreferencesManager.getInstance().writeBoolean(
                    HuhiPreferenceKeys.HUHI_BOTTOM_TOOLBAR_ENABLED_KEY, enable);

            return enable;
        }
    }

    private static boolean isSmallScreen() {
        Activity currentActivity = null;
        for (Activity ref : ApplicationStatus.getRunningActivities()) {
            currentActivity = ref;
            if (!(ref instanceof ChromeActivity)) continue;

            break;
        }
        Display screensize = currentActivity.getWindowManager().getDefaultDisplay();
        Point size = new Point();
        screensize.getSize(size);
        int width = size.x;
        int height = size.y;

        return (width <= SMALL_SCREEN_WIDTH) && (height <= SMALL_SCREEN_HEIGHT);
    }
}

