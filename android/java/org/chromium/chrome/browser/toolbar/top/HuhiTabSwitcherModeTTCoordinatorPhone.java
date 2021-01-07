/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.toolbar.top;

import android.view.ViewStub;

import org.chromium.chrome.browser.toolbar.menu_button.MenuButtonCoordinator;

class HuhiTabSwitcherModeTTCoordinatorPhone extends TabSwitcherModeTTCoordinatorPhone {
    private TabSwitcherModeTTPhone mTabSwitcherModeToolbar;

    private boolean mIsBottomToolbarVisible;
    private MenuButtonCoordinator mHuhiMenuButtonCoordinator;

    HuhiTabSwitcherModeTTCoordinatorPhone(
            ViewStub tabSwitcherToolbarStub, MenuButtonCoordinator menuButtonCoordinator) {
        super(tabSwitcherToolbarStub, menuButtonCoordinator);
        mHuhiMenuButtonCoordinator = menuButtonCoordinator;
    }

    @Override
    public void setTabSwitcherMode(boolean inTabSwitcherMode) {
        super.setTabSwitcherMode(inTabSwitcherMode);
        if (inTabSwitcherMode && (mTabSwitcherModeToolbar instanceof HuhiTabSwitcherModeTTPhone)) {
            ((HuhiTabSwitcherModeTTPhone) mTabSwitcherModeToolbar)
                    .onBottomToolbarVisibilityChanged(mIsBottomToolbarVisible);
        }
        if (mHuhiMenuButtonCoordinator != null && mIsBottomToolbarVisible) {
            mHuhiMenuButtonCoordinator.setVisibility(!inTabSwitcherMode);
        }
    }

    void onBottomToolbarVisibilityChanged(boolean isVisible) {
        if (mIsBottomToolbarVisible == isVisible) {
            return;
        }
        mIsBottomToolbarVisible = isVisible;
        if (mTabSwitcherModeToolbar instanceof HuhiTabSwitcherModeTTPhone) {
            ((HuhiTabSwitcherModeTTPhone) mTabSwitcherModeToolbar)
                    .onBottomToolbarVisibilityChanged(isVisible);
        }
    }
}
