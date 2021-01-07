/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.partnercustomizations;

import android.content.SharedPreferences;

import org.chromium.base.ContextUtils;

public class CloseHuhiManager {
    private static final String CLOSING_ALL_TABS_CLOSES_HUHI = "closing_all_tabs_closes_huhi";

    public static boolean shouldCloseAppWithZeroTabs() {
        return getClosingAllTabsClosesHuhiEnabled();
    }

    public static boolean getClosingAllTabsClosesHuhiEnabled() {
        return ContextUtils.getAppSharedPreferences().getBoolean(CLOSING_ALL_TABS_CLOSES_HUHI, false);
    }

    public static void setClosingAllTabsClosesHuhiEnabled(boolean enable) {
        SharedPreferences.Editor sharedPreferencesEditor =
            ContextUtils.getAppSharedPreferences().edit();
        sharedPreferencesEditor.putBoolean(CLOSING_ALL_TABS_CLOSES_HUHI, enable);
        sharedPreferencesEditor.apply();
    }
}
