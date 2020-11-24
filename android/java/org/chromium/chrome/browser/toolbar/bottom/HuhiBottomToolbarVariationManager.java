/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.toolbar.bottom;

import org.chromium.chrome.browser.toolbar.bottom.BottomToolbarConfiguration;

/**
  * Huhi's extension for BottomToolbarVariationManager
  */
public class HuhiBottomToolbarVariationManager
        extends BottomToolbarVariationManager {
    private static String sHuhiVariation;

    private static @Variations String getHuhiVariation() {
        if (sHuhiVariation != null) return sHuhiVariation;
        sHuhiVariation = BOTTOM_TOOLBAR_VARIATION.getValue();
        return sHuhiVariation;
    }

    public static boolean isHuhiVariation() {
        return BottomToolbarConfiguration.isBottomToolbarEnabled()
                && getHuhiVariation().equals(Variations.NONE);
    }
}
