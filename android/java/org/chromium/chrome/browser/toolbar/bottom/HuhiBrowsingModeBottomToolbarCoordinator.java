/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.toolbar.bottom;

import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnLongClickListener;

import org.chromium.base.supplier.ObservableSupplier;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.ActivityTabProvider;
import org.chromium.chrome.browser.ThemeColorProvider;
import org.chromium.chrome.browser.app.HuhiActivity;
import org.chromium.chrome.browser.compositor.layouts.OverviewModeBehavior;
import org.chromium.chrome.browser.tab.TabImpl;
import org.chromium.chrome.browser.toolbar.IncognitoStateProvider;
import org.chromium.chrome.browser.toolbar.TabCountProvider;
import org.chromium.chrome.browser.toolbar.menu_button.MenuButton;
import org.chromium.chrome.browser.ui.appmenu.AppMenuButtonHelper;

/**
 * Huhi's extension to BrowsingModeBottomToolbarCoordinator.
 */
public class HuhiBrowsingModeBottomToolbarCoordinator
    extends BrowsingModeBottomToolbarCoordinator {
    private final BrowsingModeBottomToolbarLinearLayout mHuhiToolbarRoot;
    private final ActivityTabProvider mHuhiTabProvider;
    private final BookmarksButton mBookmarkButton;
    private final MenuButton mMenuButton;
    private final BottomToolbarNewTabButton mHuhiNewTabButton;

    HuhiBrowsingModeBottomToolbarCoordinator(View root, ActivityTabProvider tabProvider,
            OnClickListener homeButtonListener, OnClickListener searchAcceleratorListener,
            ObservableSupplier<OnClickListener> shareButtonListenerSupplier,
            OnLongClickListener tabSwitcherLongClickListener,
            ObservableSupplier<OverviewModeBehavior> overviewModeBehaviorSupplier) {
        super(root, tabProvider, homeButtonListener, searchAcceleratorListener,
                shareButtonListenerSupplier, tabSwitcherLongClickListener,
                overviewModeBehaviorSupplier);
        mHuhiTabProvider = tabProvider;
        mHuhiToolbarRoot = root.findViewById(R.id.bottom_toolbar_browsing);
        mHuhiNewTabButton = mHuhiToolbarRoot.findViewById(R.id.bottom_new_tab_button);
        mBookmarkButton = mHuhiToolbarRoot.findViewById(R.id.bottom_bookmark_button);
        if (HuhiBottomToolbarVariationManager.isHuhiVariation()) {
            mBookmarkButton.setVisibility(View.VISIBLE);
            getNewTabButtonParent().setVisibility(View.GONE);
            OnClickListener bookmarkClickHandler = v -> {
                TabImpl tab = (TabImpl) mHuhiTabProvider.get();
                HuhiActivity activity = HuhiActivity.getHuhiActivity();
                if (tab == null || activity == null) {
                    assert false;
                    return;
                }
                activity.addOrEditBookmark(tab);
            };
            mBookmarkButton.setOnClickListener(bookmarkClickHandler);
        }
        mMenuButton = mHuhiToolbarRoot.findViewById(R.id.menu_button_wrapper);
        if (!BottomToolbarVariationManager.isMenuButtonOnBottom()) {
            mMenuButton.setVisibility(View.GONE);
        }
    }

    @Override
    public void initializeWithNative(OnClickListener newTabListener,
            OnClickListener tabSwitcherListener, AppMenuButtonHelper menuButtonHelper,
            TabCountProvider tabCountProvider, ThemeColorProvider themeColorProvider,
            IncognitoStateProvider incognitoStateProvider) {
        super.initializeWithNative(newTabListener, tabSwitcherListener, menuButtonHelper,
                tabCountProvider, themeColorProvider, incognitoStateProvider);
        mBookmarkButton.setThemeColorProvider(themeColorProvider);

        mMenuButton.setAppMenuButtonHelper(menuButtonHelper);
        mMenuButton.setThemeColorProvider(themeColorProvider);
    }

    public void updateBookmarkButton(boolean isBookmarked, boolean editingAllowed) {
        if (mBookmarkButton != null) {
            mBookmarkButton.updateBookmarkButton(isBookmarked, editingAllowed);
        }
    }

    @Override
    public void destroy() {
        super.destroy();
        mBookmarkButton.destroy();
        mMenuButton.destroy();
    }

    View getNewTabButtonParent() {
        return (View)mHuhiNewTabButton.getParent();
    }

    BookmarksButton getBookmarkButton() {
        return mBookmarkButton;
    }
}
