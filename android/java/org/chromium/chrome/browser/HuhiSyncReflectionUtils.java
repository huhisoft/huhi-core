/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser;

import java.lang.reflect.Method;

import org.chromium.base.Log;
import org.chromium.base.ThreadUtils;
import org.chromium.chrome.browser.HuhiConfig;

// The purpose of this class is to hide HuhiSyncWorker object under `enable_huhi_sync`
// and create it without explict import
public class HuhiSyncReflectionUtils {

    private static Object sHuhiSyncWorker = null;
    private static boolean sInitialized = false;
    private static String TAG = "SYNC";

    public static Object getSyncWorker() {
        // May be invoked in non-UI thread when we do validation for camera QR in callback
        if (!sInitialized) {
            if (HuhiConfig.SYNC_ENABLED) {
                try {
                    sHuhiSyncWorker =
                        Class.forName("org.chromium.chrome.browser.HuhiSyncWorker")
                             .getConstructor()
                             .newInstance();
                } catch (Exception e) {
                    Log.e(TAG, "Cannot create HuhiSyncWorker ", e);
                }
            }
            sInitialized = true;
        }
        return sHuhiSyncWorker;
    }

    public static void showInformers() {
        if (!HuhiConfig.SYNC_ENABLED) {
            return;
        }

        try {
            Method method = Class.forName("org.chromium.chrome.browser.HuhiSyncInformers").getDeclaredMethod("show");
            method.invoke(null);
        } catch (Exception e) {
            Log.e(TAG, "Cannot show sync informers with reflection ", e);
        }
    }
}
