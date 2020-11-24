/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser;

import org.chromium.base.annotations.JNINamespace;
import org.chromium.base.annotations.NativeMethods;

@JNINamespace("chrome::android")
public abstract class HuhiFeatureList {
    public static final String HUHI_REWARDS = "HuhiRewards";
    public static final String USE_DEV_UPDATER_URL = "UseDevUpdaterUrl";
    public static final String FORCE_WEB_CONTENTS_DARK_MODE = "WebContentsForceDark";
    public static final String ENABLE_FORCE_DARK = "enable-force-dark";

    public static void enableFeature(String featureName, boolean enabled) {
        HuhiFeatureListJni.get().enableFeature(featureName, enabled);
    }

    @NativeMethods
    interface Natives {
        void enableFeature(String featureName, boolean enabled);
    }
}
