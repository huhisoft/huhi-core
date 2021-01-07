/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser;

import android.content.Context;
import android.content.SharedPreferences;

import org.chromium.base.Log;
import org.chromium.base.ContextUtils;
import org.chromium.base.ThreadUtils;
import org.chromium.base.annotations.CalledByNative;
import org.chromium.base.annotations.JNINamespace;
import org.chromium.base.task.PostTask;
import org.chromium.base.task.TaskTraits;

import java.lang.Runnable;

@JNINamespace("chrome::android")
public class HuhiSyncWorker {
    public static final String TAG = "SYNC";

    private Context mContext;
    private String mDebug = "true";

    private long mNativeHuhiSyncWorker;

    @CalledByNative
    private void setNativePtr(long nativePtr) {
        assert mNativeHuhiSyncWorker == 0;
        mNativeHuhiSyncWorker = nativePtr;
    }

    private void Init() {
        if (mNativeHuhiSyncWorker == 0) {
            nativeInit();
        }
    }

    @Override
    protected void finalize() {
        Destroy();
    }

    private void Destroy() {
        if (mNativeHuhiSyncWorker != 0) {
            nativeDestroy(mNativeHuhiSyncWorker);
            mNativeHuhiSyncWorker = 0;
        }
    }

    public HuhiSyncWorker() {
        mContext = ContextUtils.getApplicationContext();
        Init();
        (new MigrationFromV1()).MigrateFromSyncV1();
    }

    private class MigrationFromV1 {
        // Deprecated
        public static final String PREF_NAME = "SyncPreferences";
        private static final String PREF_LAST_FETCH_NAME = "TimeLastFetch";
        private static final String PREF_LATEST_DEVICE_RECORD_TIMESTAMPT_NAME =
                "LatestDeviceRecordTime";
        private static final String PREF_LAST_TIME_SEND_NOT_SYNCED_NAME = "TimeLastSendNotSynced";
        public static final String PREF_DEVICE_ID = "DeviceId";
        public static final String PREF_BASE_ORDER = "BaseOrder";
        public static final String PREF_LAST_ORDER = "LastOrder";
        public static final String PREF_SEED = "Seed";
        public static final String PREF_SYNC_DEVICE_NAME = "SyncDeviceName";
        private static final String PREF_SYNC_SWITCH = "sync_switch";
        private static final String PREF_SYNC_BOOKMARKS = "huhi_sync_bookmarks";
        public static final String PREF_SYNC_TABS = "huhi_sync_tabs"; // never used
        public static final String PREF_SYNC_HISTORY = "huhi_sync_history"; // never used
        public static final String PREF_SYNC_AUTOFILL_PASSWORDS =
                "huhi_sync_autofill_passwords"; // never used
        public static final String PREF_SYNC_PAYMENT_SETTINGS =
                "huhi_sync_payment_settings"; // never used

        private boolean HaveSyncV1Prefs() {
            SharedPreferences sharedPref = mContext.getSharedPreferences(PREF_NAME, 0);

            String deviceId = sharedPref.getString(PREF_DEVICE_ID, null);
            if (null == deviceId) {
                return false;
            }
            return true;
        }

        private void DeleteSyncV1Prefs() {
            SharedPreferences sharedPref = mContext.getSharedPreferences(PREF_NAME, 0);
            SharedPreferences.Editor editor = sharedPref.edit();
            editor.clear().apply();
        }

        private void DeleteSyncV1LevelDb() {
            nativeDestroyV1LevelDb();
        }

        public void MigrateFromSyncV1() {
            // Do all migration work in file IO thread because we may need to
            // read shared preferences and delete level db
            PostTask.postTask(TaskTraits.BEST_EFFORT_MAY_BLOCK, () -> {
                if (HaveSyncV1Prefs()) {
                    Log.i(TAG, "Found sync v1 data, doing migration");
                    DeleteSyncV1Prefs();
                    DeleteSyncV1LevelDb();
                    // Mark sync v1 was enabled to trigger informers
                    ThreadUtils.runOnUiThreadBlocking(new Runnable() {
                        @Override
                        public void run() {
                            nativeMarkSyncV1WasEnabledAndMigrated();
                            HuhiSyncInformers.show();
                        }
                    });
                }
            });
        }
    };

    public String GetCodephrase() {
        return nativeGetSyncCodeWords(mNativeHuhiSyncWorker);
    }

    public void SaveCodephrase(String codephrase) {
        nativeSaveCodeWords(mNativeHuhiSyncWorker, codephrase);
    }

    public String GetSeedHexFromWords(String codephrase) {
        return nativeGetSeedHexFromWords(codephrase);
    }

    public String GetWordsFromSeedHex(String seedHex) {
        return nativeGetWordsFromSeedHex(seedHex);
    }

    public void RequestSync() {
        nativeRequestSync(mNativeHuhiSyncWorker);
    }

    public boolean IsFirstSetupComplete() {
        return nativeIsFirstSetupComplete(mNativeHuhiSyncWorker);
    }

    public void FinalizeSyncSetup() {
        nativeFinalizeSyncSetup(mNativeHuhiSyncWorker);
    }

    public void ResetSync() {
        nativeResetSync(mNativeHuhiSyncWorker);
    }

    public boolean getSyncV1WasEnabled() {
        return nativeGetSyncV1WasEnabled(mNativeHuhiSyncWorker);
    }

    public boolean getSyncV2MigrateNoticeDismissed() {
        return nativeGetSyncV2MigrateNoticeDismissed(mNativeHuhiSyncWorker);
    }

    public void setSyncV2MigrateNoticeDismissed(boolean isDismissed) {
        nativeSetSyncV2MigrateNoticeDismissed(mNativeHuhiSyncWorker, isDismissed);
    }

    private native void nativeInit();
    private native void nativeDestroy(long nativeHuhiSyncWorker);

    private native void nativeDestroyV1LevelDb();
    private native void nativeMarkSyncV1WasEnabledAndMigrated();

    private native String nativeGetSyncCodeWords(long nativeHuhiSyncWorker);
    private native void nativeRequestSync(long nativeHuhiSyncWorker);

    private native String nativeGetSeedHexFromWords(String passphrase);
    private native String nativeGetWordsFromSeedHex(String seedHex);
    private native void nativeSaveCodeWords(long nativeHuhiSyncWorker, String passphrase);

    private native void nativeFinalizeSyncSetup(long nativeHuhiSyncWorker);

    private native boolean nativeIsFirstSetupComplete(long nativeHuhiSyncWorker);

    private native void nativeResetSync(long nativeHuhiSyncWorker);

    private native boolean nativeGetSyncV1WasEnabled(long nativeHuhiSyncWorker);
    private native boolean nativeGetSyncV2MigrateNoticeDismissed(long nativeHuhiSyncWorker);
    private native void nativeSetSyncV2MigrateNoticeDismissed(long nativeHuhiSyncWorker, boolean isDismissed);
}
