/**
 * Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 */

package org.chromium.chrome.browser.onboarding;

import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.os.IBinder;
import android.util.Log;

import org.chromium.base.library_loader.LibraryLoader;
import org.chromium.chrome.browser.HuhiAdsNativeHelper;
import org.chromium.chrome.browser.HuhiRewardsNativeWorker;
import org.chromium.chrome.browser.HuhiRewardsObserver;
import org.chromium.chrome.browser.profiles.Profile;

public class HuhiRewardsService extends Service implements HuhiRewardsObserver {
    private static String TAG = "HuhiRewardsService";

    private Context context;

    private HuhiRewardsNativeWorker mHuhiRewardsNativeWorker;

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public void onCreate() {
        this.context = this;
    }

    @Override
    public void onDestroy() {
        if (mHuhiRewardsNativeWorker != null) {
            mHuhiRewardsNativeWorker.RemoveObserver(this);
        }
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        if (!LibraryLoader.getInstance().isInitialized()) {
            return START_STICKY;
        }
        try {
            mHuhiRewardsNativeWorker = HuhiRewardsNativeWorker.getInstance();
            if (mHuhiRewardsNativeWorker != null) {
                mHuhiRewardsNativeWorker.AddObserver(this);
                mHuhiRewardsNativeWorker.CreateWallet();
            }
        } catch (UnsatisfiedLinkError error) {
            Log.e(TAG, error.getMessage());
            assert false;
        }

        return START_STICKY;
    }

    // interface HuhiRewardsObserver
    @Override
    public void OnWalletInitialized(int error_code) {
        if (HuhiRewardsNativeWorker.WALLET_CREATED == error_code
                && OnboardingPrefManager.getInstance().isAdsAvailable()) {
            // Enable ads
            HuhiAdsNativeHelper.nativeSetAdsEnabled(Profile.getLastUsedRegularProfile());
        } else {
            // TODO: handle wallet creation problem
        }
        stopSelf();
    };

    @Override
    public void OnPublisherInfo(int tabId){};

    @Override
    public void OnGetCurrentBalanceReport(double[] report){};

    @Override
    public void OnNotificationAdded(String id, int type, long timestamp, String[] args){};

    @Override
    public void OnNotificationsCount(int count){};

    @Override
    public void OnGetLatestNotification(String id, int type, long timestamp, String[] args){};

    @Override
    public void OnNotificationDeleted(String id){};

    @Override
    public void OnIsWalletCreated(boolean created){};

    @Override
    public void OnGetPendingContributionsTotal(double amount){};

    @Override
    public void OnGetRewardsMainEnabled(boolean enabled){};

    @Override
    public void OnGetAutoContributeProperties(){};

    @Override
    public void OnGetReconcileStamp(long timestamp){};

    @Override
    public void OnRecurringDonationUpdated(){};

    @Override
    public void OnResetTheWholeState(boolean success){};

    @Override
    public void OnRewardsMainEnabled(boolean enabled){};
}
