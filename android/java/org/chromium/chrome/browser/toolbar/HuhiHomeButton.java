/**
 * Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

package org.chromium.chrome.browser.toolbar;

import android.content.Context;
import android.util.AttributeSet;

import androidx.core.content.ContextCompat;

import org.chromium.chrome.R;
import org.chromium.chrome.browser.homepage.HomepageManager;
import org.chromium.chrome.browser.tab.Tab;

/**
 * Huhi's extension of HomeButton.
 */
public class HuhiHomeButton extends HomeButton {
    private Context mContext;

    public HuhiHomeButton(Context context, AttributeSet attrs) {
        super(context, attrs);
        mContext = context;
    }

    /**
     * Override to swap icon to new_tab_icon and enable the button when
     * homepage is disabled.
     */
    @Override
    public void updateButtonEnabledState(Tab tab) {
        super.updateButtonEnabledState(tab);

        final boolean isHomepageEnabled = HomepageManager.isHomepageEnabled();
        if (!isHomepageEnabled) {
            setImageDrawable(ContextCompat.getDrawable(mContext, R.drawable.new_tab_icon));
            setEnabled(true);
        } else { // swap back to home button icon
            setImageDrawable(ContextCompat.getDrawable(mContext, R.drawable.btn_toolbar_home));
        }
    }
}
