/**
 * Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

package org.chromium.chrome.browser.util;

import android.app.Activity;
import android.content.Context;
import android.view.ContextThemeWrapper;
import android.view.MenuItem;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.PopupMenu;

import org.chromium.base.ApplicationStatus;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.app.HuhiActivity;
import org.chromium.chrome.browser.app.ChromeActivity;
import org.chromium.chrome.browser.night_mode.GlobalNightModeStateProviderHolder;
import org.chromium.chrome.browser.tab.TabLaunchType;
import org.chromium.content_public.browser.LoadUrlParams;

public class TabUtils {
    public static void showTabPopupMenu(Context context, View view) {
        HuhiActivity huhiActivity = HuhiActivity.getHuhiActivity();
        Context wrapper = new ContextThemeWrapper(context,
                GlobalNightModeStateProviderHolder.getInstance().isInNightMode()
                        ? R.style.NewTabPopupMenuDark
                        : R.style.NewTabPopupMenuLight);
        // Creating the instance of PopupMenu
        PopupMenu popup = new PopupMenu(wrapper, view);
        // Inflating the Popup using xml file
        popup.getMenuInflater().inflate(R.menu.new_tab_menu, popup.getMenu());

        if (huhiActivity != null && huhiActivity.getCurrentTabModel().isIncognito()) {
            popup.getMenu().findItem(R.id.new_tab_menu_id).setVisible(false);
        }
        // registering popup with OnMenuItemClickListener
        popup.setOnMenuItemClickListener(new PopupMenu.OnMenuItemClickListener() {
            @Override
            public boolean onMenuItemClick(MenuItem item) {
                int id = item.getItemId();
                if (id == R.id.new_tab_menu_id) {
                    openNewTab(huhiActivity, false);
                } else if (id == R.id.new_incognito_tab_menu_id) {
                    openNewTab(huhiActivity, true);
                }
                return true;
            }
        });
        popup.show(); // showing popup menu
    }

    public static void openNewTab() {
        HuhiActivity huhiActivity = HuhiActivity.getHuhiActivity();
        boolean isIncognito =
                huhiActivity != null ? huhiActivity.getCurrentTabModel().isIncognito() : false;
        openNewTab(huhiActivity, isIncognito);
    }

    private static void openNewTab(HuhiActivity huhiActivity, boolean isIncognito) {
        if (huhiActivity == null) return;
        huhiActivity.getTabModelSelector().getModel(isIncognito).commitAllTabClosures();
        huhiActivity.getTabCreator(isIncognito).launchNTP();
    }

    public static void openUrlInNewTab(boolean isIncognito, String url) {
        HuhiActivity huhiActivity = HuhiActivity.getHuhiActivity();
        if (huhiActivity != null) {
            huhiActivity.getTabCreator(isIncognito).launchUrl(url, TabLaunchType.FROM_CHROME_UI);
        }
    }

    public static void openUrlInSameTab(String url) {
        HuhiActivity huhiActivity = HuhiActivity.getHuhiActivity();
        if (huhiActivity != null) {
            LoadUrlParams loadUrlParams = new LoadUrlParams(url);
            huhiActivity.getActivityTab().loadUrl(loadUrlParams);
        }
    }

    public static void enableRewardsButton() {
        HuhiActivity huhiActivity = HuhiActivity.getHuhiActivity();
        if (huhiActivity == null || huhiActivity.getToolbarManager() == null) {
            return;
        }
        View toolbarView = huhiActivity.findViewById(R.id.toolbar);
        if (toolbarView == null) {
            return;
        }
        FrameLayout rewardsLayout = toolbarView.findViewById(R.id.huhi_rewards_button_layout);
        if (rewardsLayout == null) {
            return;
        }
        rewardsLayout.setVisibility(View.VISIBLE);
    }
}
