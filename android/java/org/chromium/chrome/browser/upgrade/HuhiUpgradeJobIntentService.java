/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.upgrade;

import android.content.Context;
import android.content.Intent;

import androidx.annotation.NonNull;
import androidx.core.app.JobIntentService;

import org.chromium.base.Callback;
import org.chromium.base.Log;
import org.chromium.base.task.PostTask;
import org.chromium.chrome.browser.HuhiFeatureList;
import org.chromium.chrome.browser.flags.ChromeFeatureList;
import org.chromium.chrome.browser.preferences.HuhiPrefServiceBridge;
import org.chromium.chrome.browser.util.SafetyNetCheck;
import org.chromium.chrome.browser.util.TabUtils;
import org.chromium.content_public.browser.BrowserStartupController;
import org.chromium.content_public.browser.UiThreadTaskTraits;

public class HuhiUpgradeJobIntentService extends JobIntentService {
    private static final String TAG = "HuhiUpgradeJobIntentService";

    private static final int JOB_ID = 1;

    public static void maybePerformUpgradeTasks(Context context) {
        HuhiUpgradeJobIntentService.enqueueWork(context, new Intent());
    }

    private static void enqueueWork(Context context, Intent work) {
        enqueueWork(context, HuhiUpgradeJobIntentService.class, JOB_ID, work);
    }

    @Override
    protected void onHandleWork(@NonNull Intent intent) {
        PostTask.runOrPostTask(UiThreadTaskTraits.DEFAULT, () -> {
            BrowserStartupController.getInstance().addStartupCompletedObserver(
                    new BrowserStartupController.StartupCallback() {
                        @Override
                        public void onSuccess() {
                            if (ChromeFeatureList.isEnabled(HuhiFeatureList.HUHI_REWARDS)
                                    && HuhiPrefServiceBridge.getInstance()
                                               .getSafetynetCheckFailed()) {
                                Callback<Boolean> callback = value -> {
                                    if (value == null || !value.booleanValue()) {
                                        return;
                                    }
                                    // Reset flag and update UI
                                    HuhiPrefServiceBridge.getInstance().setSafetynetCheckFailed(
                                            false);
                                    TabUtils.enableRewardsButton();
                                };
                                // Re-perform safetynet check
                                SafetyNetCheck.updateSafetynetStatus(callback);
                            }
                        }

                        @Override
                        public void onFailure() {
                            Log.e(TAG,
                                    "Failed to perform upgrade tasks: BrowserStartupController.StartupCallback failed");
                        }
                    });
        });
    }
}