/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.homepage;

import org.chromium.chrome.browser.partnercustomizations.CloseHuhiManager;

// see org.huhi.bytecode.HuhiHomepageManagerClassAdapter
public class HuhiHomepageManager {
    public static boolean shouldCloseAppWithZeroTabs() {
        return CloseHuhiManager.shouldCloseAppWithZeroTabs();
    }
}
