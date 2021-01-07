/** Copyright (c) 2020 The Huhi Authors. All rights reserved.
  * This Source Code Form is subject to the terms of the Mozilla Public
  * License, v. 2.0. If a copy of the MPL was not distributed with this file,
  * You can obtain one at http://mozilla.org/MPL/2.0/.
  */

package org.chromium.chrome.browser;

import android.os.Handler;
import androidx.annotation.Nullable;

import org.chromium.base.Log;
import org.chromium.base.annotations.CalledByNative;
import org.chromium.base.annotations.JNINamespace;
import org.chromium.chrome.browser.HuhiRewardsBalance;
import org.chromium.chrome.browser.HuhiRewardsHelper;
import org.chromium.chrome.browser.HuhiRewardsObserver;
import org.chromium.chrome.browser.HuhiRewardsPublisher.PublisherStatus;
import org.chromium.chrome.browser.tab.Tab;
import org.chromium.components.embedder_support.util.UrlConstants;
import org.json.JSONException;

import java.util.ArrayList;
import java.util.List;

@JNINamespace("chrome::android")
public class HuhiRewardsNativeWorker {
    /**
     * Allows to monitor a front tab publisher changes.
     */
    public interface PublisherObserver { void onFrontTabPublisherChanged(boolean verified); }

    // Rewards notifications
    // Taken from components/huhi_rewards/browser/rewards_notification_service.h
    public static final int REWARDS_NOTIFICATION_INVALID = 0;
    public static final int REWARDS_NOTIFICATION_AUTO_CONTRIBUTE = 1;
    public static final int REWARDS_NOTIFICATION_GRANT = 2;
    public static final int REWARDS_NOTIFICATION_GRANT_ADS = 3;
    public static final int REWARDS_NOTIFICATION_FAILED_CONTRIBUTION = 4;
    public static final int REWARDS_NOTIFICATION_IMPENDING_CONTRIBUTION = 5;
    public static final int REWARDS_NOTIFICATION_INSUFFICIENT_FUNDS = 6;
    public static final int REWARDS_NOTIFICATION_BACKUP_WALLET = 7;
    public static final int REWARDS_NOTIFICATION_TIPS_PROCESSED = 8;
    public static final int REWARDS_NOTIFICATION_ADS_ONBOARDING = 9;
    public static final int REWARDS_NOTIFICATION_VERIFIED_PUBLISHER = 10;

    public static final int LEDGER_OK = 0;
    public static final int LEDGER_ERROR = 1;
    public static final int WALLET_CREATED = 12;
    public static final int BAT_NOT_ALLOWED = 25;
    public static final int SAFETYNET_ATTESTATION_FAILED = 27;

    private static final int REWARDS_UNKNOWN = 0;
    private static final int REWARDS_DISABLED = 1;
    private static final int REWARDS_ENABLED = 2;
    private static int rewardsStatus = REWARDS_UNKNOWN;
    private String frontTabUrl;
    private static final Handler mHandler = new Handler();

    private List<HuhiRewardsObserver> mObservers;
    private List<PublisherObserver> mFrontTabPublisherObservers;
    private long mNativeHuhiRewardsNativeWorker;

    private static HuhiRewardsNativeWorker instance;
    private static final Object lock = new Object();
    private boolean grantClaimInProcess;  // flag: wallet is being created

    public static  HuhiRewardsNativeWorker getInstance() {
        synchronized(lock) {
          if(instance == null) {
              instance = new HuhiRewardsNativeWorker();
              instance.Init();
          }
        }
        return instance;
    }

    private HuhiRewardsNativeWorker() {
        mObservers = new ArrayList<HuhiRewardsObserver>();
        mFrontTabPublisherObservers = new ArrayList<PublisherObserver>();
    }

    private void Init() {
      if (mNativeHuhiRewardsNativeWorker == 0) {
          nativeInit();
      }
    }

    @Override
    protected void finalize() {
        Destroy();
    }

    private void Destroy() {
        if (mNativeHuhiRewardsNativeWorker != 0) {
            nativeDestroy(mNativeHuhiRewardsNativeWorker);
            mNativeHuhiRewardsNativeWorker = 0;
        }
    }

    public void AddObserver(HuhiRewardsObserver observer) {
        synchronized(lock) {
            mObservers.add(observer);
        }
    }

    public void RemoveObserver(HuhiRewardsObserver observer) {
        synchronized(lock) {
            mObservers.remove(observer);
        }
    }

    public void AddPublisherObserver(PublisherObserver observer) {
        synchronized (lock) {
            mFrontTabPublisherObservers.add(observer);
        }
    }

    public void RemovePublisherObserver(PublisherObserver observer) {
        synchronized (lock) {
            mFrontTabPublisherObservers.remove(observer);
        }
    }

    public void OnNotifyFrontTabUrlChanged(int tabId, String url) {
        boolean chromeUrl = url.startsWith(UrlConstants.CHROME_SCHEME);
        boolean newUrl = (frontTabUrl == null || !frontTabUrl.equals(url));
        if (chromeUrl) {
            // Don't query 'GetPublisherInfo' and post response now.
            mHandler.post(new Runnable() {
                @Override
                public void run() {
                    NotifyPublisherObservers(false);
                }
            });
        } else if (newUrl) {
            GetPublisherInfo(tabId, url);
        }

        frontTabUrl = url;
    }

    private void NotifyPublisherObservers(boolean verified) {
        for (PublisherObserver observer : mFrontTabPublisherObservers) {
            observer.onFrontTabPublisherChanged(verified);
        }
    }

    public void TriggerOnNotifyFrontTabUrlChanged() {
        // Clear frontTabUrl so that all observers are updated.
        frontTabUrl = "";
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                Tab tab = HuhiRewardsHelper.currentActiveChromeTabbedActivityTab();
                if (tab != null && !tab.isIncognito()) {
                    OnNotifyFrontTabUrlChanged(tab.getId(), tab.getUrlString());
                }
            }
        });
    }

    public boolean IsGrantClaimInProcess() {
        synchronized(lock) {
          return grantClaimInProcess;
        }
    }

    public void GetRewardsParameters() {
        synchronized(lock) {
            nativeGetRewardsParameters(mNativeHuhiRewardsNativeWorker);
        }
    }

    @Nullable
    public HuhiRewardsBalance GetWalletBalance() {
        synchronized(lock) {
            String  json = nativeGetWalletBalance(mNativeHuhiRewardsNativeWorker);
            HuhiRewardsBalance balance = null;
            try{
                balance = new HuhiRewardsBalance (json);
            }
            catch (JSONException e) {
                balance = null;
            }
            return balance;
        }
    }

    public double GetWalletRate() {
        synchronized(lock) {
            return nativeGetWalletRate(mNativeHuhiRewardsNativeWorker);
        }
    }

    public void GetPublisherInfo(int tabId, String host) {
        synchronized(lock) {
            nativeGetPublisherInfo(mNativeHuhiRewardsNativeWorker, tabId, host);
        }
    }

    public String GetPublisherURL(int tabId) {
        synchronized(lock) {
            return nativeGetPublisherURL(mNativeHuhiRewardsNativeWorker, tabId);
        }
    }

    public String GetPublisherFavIconURL(int tabId) {
        synchronized(lock) {
            return nativeGetPublisherFavIconURL(mNativeHuhiRewardsNativeWorker, tabId);
        }
    }

    public String GetPublisherName(int tabId) {
        synchronized(lock) {
            return nativeGetPublisherName(mNativeHuhiRewardsNativeWorker, tabId);
        }
    }

    public String GetPublisherId(int tabId) {
        synchronized(lock) {
            return nativeGetPublisherId(mNativeHuhiRewardsNativeWorker, tabId);
        }
    }

    public int GetPublisherPercent(int tabId) {
        synchronized(lock) {
            return nativeGetPublisherPercent(mNativeHuhiRewardsNativeWorker, tabId);
        }
    }

    public boolean GetPublisherExcluded(int tabId) {
        synchronized(lock) {
            return nativeGetPublisherExcluded(mNativeHuhiRewardsNativeWorker, tabId);
        }
    }

    public @PublisherStatus int GetPublisherStatus(int tabId) {
        synchronized(lock) {
            return nativeGetPublisherStatus(mNativeHuhiRewardsNativeWorker, tabId);
        }
    }

    public void IncludeInAutoContribution(int tabId, boolean exclude) {
        synchronized(lock) {
            nativeIncludeInAutoContribution(mNativeHuhiRewardsNativeWorker, tabId, exclude);
        }
    }

    public void RemovePublisherFromMap(int tabId) {
        synchronized(lock) {
            nativeRemovePublisherFromMap(mNativeHuhiRewardsNativeWorker, tabId);
        }
    }

    public void GetCurrentBalanceReport() {
        synchronized(lock) {
            nativeGetCurrentBalanceReport(mNativeHuhiRewardsNativeWorker);
        }
    }

    public void Donate(String publisher_key, int amount, boolean recurring) {
        synchronized(lock) {
            nativeDonate(mNativeHuhiRewardsNativeWorker, publisher_key, amount, recurring);
        }
    }

    public void GetAllNotifications() {
        synchronized(lock) {
            nativeGetAllNotifications(mNativeHuhiRewardsNativeWorker);
        }
    }

    public void DeleteNotification(String notification_id) {
        synchronized(lock) {
            nativeDeleteNotification(mNativeHuhiRewardsNativeWorker, notification_id);
        }
    }

    public void GetGrant(String promotionId) {
        synchronized(lock) {
            if (grantClaimInProcess) {
                return;
            }
            grantClaimInProcess = true;
            nativeGetGrant(mNativeHuhiRewardsNativeWorker, promotionId);
        }
    }

    public String[] GetCurrentGrant(int position) {
        synchronized(lock) {
            return nativeGetCurrentGrant(mNativeHuhiRewardsNativeWorker, position);
        }
    }

    public void GetPendingContributionsTotal() {
        synchronized(lock) {
            nativeGetPendingContributionsTotal(mNativeHuhiRewardsNativeWorker);
        }
    }

    public void GetRecurringDonations() {
        synchronized(lock) {
            nativeGetRecurringDonations(mNativeHuhiRewardsNativeWorker);
        }
    }

    public boolean IsCurrentPublisherInRecurrentDonations(String publisher) {
        synchronized(lock) {
            return nativeIsCurrentPublisherInRecurrentDonations(mNativeHuhiRewardsNativeWorker, publisher);
        }
    }

    public double GetPublisherRecurrentDonationAmount(String publisher) {
        synchronized(lock) {
            return nativeGetPublisherRecurrentDonationAmount(mNativeHuhiRewardsNativeWorker, publisher);
        }
    }

    public void GetAutoContributeProperties() {
        synchronized(lock) {
            nativeGetAutoContributeProperties(mNativeHuhiRewardsNativeWorker);
        }
    }

    public boolean IsAutoContributeEnabled() {
        synchronized(lock) {
            return nativeIsAutoContributeEnabled(mNativeHuhiRewardsNativeWorker);
        }
    }

    public void GetReconcileStamp() {
        synchronized(lock) {
            nativeGetReconcileStamp(mNativeHuhiRewardsNativeWorker);
        }
    }

    public void RemoveRecurring(String publisher) {
        synchronized(lock) {
            nativeRemoveRecurring(mNativeHuhiRewardsNativeWorker,publisher);
        }
    }

    public void ResetTheWholeState() {
        synchronized(lock) {
            nativeResetTheWholeState(mNativeHuhiRewardsNativeWorker);
        }
    }

    public void FetchGrants() {
        synchronized(lock) {
            nativeFetchGrants(mNativeHuhiRewardsNativeWorker);
        }
    }

    public int GetAdsPerHour() {
        synchronized (lock) {
            return nativeGetAdsPerHour(mNativeHuhiRewardsNativeWorker);
        }
    }

    public void SetAdsPerHour(int value) {
        synchronized (lock) {
            nativeSetAdsPerHour(mNativeHuhiRewardsNativeWorker, value);
        }
    }

    public boolean IsAnonWallet() {
        synchronized(lock) {
            return nativeIsAnonWallet(mNativeHuhiRewardsNativeWorker);
        }
    }

    public void GetExternalWallet() {
        synchronized (lock) {
            nativeGetExternalWallet(mNativeHuhiRewardsNativeWorker);
        }
    }

    public void DisconnectWallet(String wallet_type) {
        synchronized (lock) {
            nativeDisconnectWallet(mNativeHuhiRewardsNativeWorker, wallet_type);
        }
    }

    public void ProcessRewardsPageUrl(String path, String query) {
        synchronized (lock) {
            nativeProcessRewardsPageUrl(mNativeHuhiRewardsNativeWorker,
                    path, query);
        }
    }

    public void RecoverWallet(String passPhrase) {
        synchronized (lock) {
            nativeRecoverWallet(mNativeHuhiRewardsNativeWorker, passPhrase);
        }
    }

    @CalledByNative
    public void OnRecoverWallet(int errorCode) {
        for (HuhiRewardsObserver observer : mObservers) {
            observer.OnRecoverWallet(errorCode);
        }
    }

    public void RefreshPublisher(String publisherKey) {
        synchronized (lock) {
            nativeRefreshPublisher(mNativeHuhiRewardsNativeWorker, publisherKey);
        }
    }

    public void SetAutoContributeEnabled(boolean isSetAutoContributeEnabled) {
        synchronized(lock) {
            nativeSetAutoContributeEnabled(mNativeHuhiRewardsNativeWorker, isSetAutoContributeEnabled);
        }
    }

    public void SetAutoContributionAmount(double amount) {
        synchronized(lock) {
            nativeSetAutoContributionAmount(mNativeHuhiRewardsNativeWorker, amount);
        }
    }

    public void StartProcess() {
        synchronized (lock) {
            nativeStartProcess(mNativeHuhiRewardsNativeWorker);
        }
    }

    @CalledByNative
    public void OnStartProcess() {
        for (HuhiRewardsObserver observer : mObservers) {
            observer.OnStartProcess();
        }
    }

    @CalledByNative
    public void OnRefreshPublisher(int status, String publisherKey) {
        for (HuhiRewardsObserver observer : mObservers) {
            observer.OnRefreshPublisher(status, publisherKey);
        }
    }

    @CalledByNative
    public void OnRewardsParameters(int errorCode) {
        for (HuhiRewardsObserver observer : mObservers) {
            observer.OnRewardsParameters(errorCode);
        }
    }

    @CalledByNative
    public void OnGetCurrentBalanceReport(double[] report) {
        for (HuhiRewardsObserver observer : mObservers) {
            observer.OnGetCurrentBalanceReport(report);
        }
    }

    @CalledByNative
    private void setNativePtr(long nativePtr) {
        assert mNativeHuhiRewardsNativeWorker == 0;
        mNativeHuhiRewardsNativeWorker = nativePtr;
    }

    @CalledByNative
    public void OnPublisherInfo(int tabId) {
        @PublisherStatus int pubStatus = GetPublisherStatus(tabId);
        boolean verified = (pubStatus == HuhiRewardsPublisher.CONNECTED ||
                pubStatus == HuhiRewardsPublisher.VERIFIED) ? true : false;
        NotifyPublisherObservers(verified);

        // Notify HuhiRewardsObserver (panel).
        for (HuhiRewardsObserver observer : mObservers) {
            observer.OnPublisherInfo(tabId);
        }
    }

    @CalledByNative
    public void OnNotificationAdded(String id, int type, long timestamp,
            String[] args) {
        for (HuhiRewardsObserver observer : mObservers) {
            observer.OnNotificationAdded(id, type, timestamp, args);
        }
    }

    @CalledByNative
    public void OnNotificationsCount(int count) {
        for (HuhiRewardsObserver observer : mObservers) {
            observer.OnNotificationsCount(count);
        }
    }

    @CalledByNative
    public void OnGetLatestNotification(String id, int type, long timestamp,
            String[] args) {
        for (HuhiRewardsObserver observer : mObservers) {
            observer.OnGetLatestNotification(id, type, timestamp, args);
        }
    }

    @CalledByNative
    public void OnNotificationDeleted(String id) {
        for (HuhiRewardsObserver observer : mObservers) {
            observer.OnNotificationDeleted(id);
        }
    }

    @CalledByNative
    public void OnGetPendingContributionsTotal(double amount) {
        for (HuhiRewardsObserver observer : mObservers) {
            observer.OnGetPendingContributionsTotal(amount);
        }
    }

    @CalledByNative
    public void OnGetAutoContributeProperties() {
        for (HuhiRewardsObserver observer : mObservers) {
            observer.OnGetAutoContributeProperties();
        }
    }

    @CalledByNative
    public void OnGetReconcileStamp(long timestamp) {
        for (HuhiRewardsObserver observer : mObservers) {
            observer.OnGetReconcileStamp(timestamp);
        }
    }

    @CalledByNative
    public void OnRecurringDonationUpdated() {
        for (HuhiRewardsObserver observer : mObservers) {
            observer.OnRecurringDonationUpdated();
        }
    }

    @CalledByNative
    public void OnGrantFinish(int result) {
        grantClaimInProcess = false;
        for(HuhiRewardsObserver observer : mObservers) {
            observer.OnGrantFinish(result);
        }
    }

    @CalledByNative
    public void OnResetTheWholeState(boolean success) {
        for (HuhiRewardsObserver observer : mObservers) {
            observer.OnResetTheWholeState(success);
        }
    }

    @CalledByNative
    public void OnGetExternalWallet(int error_code, String external_wallet) {
        for (HuhiRewardsObserver observer : mObservers) {
            observer.OnGetExternalWallet(error_code, external_wallet);
        }
    }

    @CalledByNative
    public void OnDisconnectWallet(int error_code, String external_wallet) {
        for (HuhiRewardsObserver observer : mObservers) {
            observer.OnDisconnectWallet(error_code, external_wallet);
        }
    }

    @CalledByNative
    public void OnProcessRewardsPageUrl(int error_code, String wallet_type,
            String action, String json_args) {
        for (HuhiRewardsObserver observer : mObservers) {
            observer.OnProcessRewardsPageUrl(error_code, wallet_type,
                    action, json_args);
        }
    }

    @CalledByNative
    public void OnClaimPromotion(int error_code) {
        grantClaimInProcess = false;
        for (HuhiRewardsObserver observer : mObservers) {
            observer.OnClaimPromotion(error_code);
        }
    }

    @CalledByNative
    public void OnOneTimeTip() {
        for (HuhiRewardsObserver observer : mObservers) {
            observer.OnOneTimeTip();
        }
    }

    private native void nativeInit();
    private native void nativeDestroy(long nativeHuhiRewardsNativeWorker);
    private native String nativeGetWalletBalance(long nativeHuhiRewardsNativeWorker);
    private native double nativeGetWalletRate(long nativeHuhiRewardsNativeWorker);
    private native void nativeGetPublisherInfo(long nativeHuhiRewardsNativeWorker, int tabId, String host);
    private native String nativeGetPublisherURL(long nativeHuhiRewardsNativeWorker, int tabId);
    private native String nativeGetPublisherFavIconURL(long nativeHuhiRewardsNativeWorker, int tabId);
    private native String nativeGetPublisherName(long nativeHuhiRewardsNativeWorker, int tabId);
    private native String nativeGetPublisherId(long nativeHuhiRewardsNativeWorker, int tabId);
    private native int nativeGetPublisherPercent(long nativeHuhiRewardsNativeWorker, int tabId);
    private native boolean nativeGetPublisherExcluded(long nativeHuhiRewardsNativeWorker, int tabId);
    private native int nativeGetPublisherStatus(long nativeHuhiRewardsNativeWorker, int tabId);
    private native void nativeIncludeInAutoContribution(long nativeHuhiRewardsNativeWorker, int tabId,
      boolean exclude);
    private native void nativeRemovePublisherFromMap(long nativeHuhiRewardsNativeWorker, int tabId);
    private native void nativeGetCurrentBalanceReport(long nativeHuhiRewardsNativeWorker);
    private native void nativeDonate(long nativeHuhiRewardsNativeWorker, String publisher_key,
            int amount, boolean recurring);
    private native void nativeGetAllNotifications(long nativeHuhiRewardsNativeWorker);
    private native void nativeDeleteNotification(
            long nativeHuhiRewardsNativeWorker, String notification_id);
    private native void nativeGetGrant(long nativeHuhiRewardsNativeWorker, String promotionId);
    private native String[] nativeGetCurrentGrant(long nativeHuhiRewardsNativeWorker, int position);
    private native void nativeGetPendingContributionsTotal(long nativeHuhiRewardsNativeWorker);
    private native void nativeGetRecurringDonations(long nativeHuhiRewardsNativeWorker);
    private native boolean nativeIsCurrentPublisherInRecurrentDonations(long nativeHuhiRewardsNativeWorker,
        String publisher);
    private native void nativeGetAutoContributeProperties(long nativeHuhiRewardsNativeWorker);
    private native boolean nativeIsAutoContributeEnabled(long nativeHuhiRewardsNativeWorker);
    private native void nativeGetReconcileStamp(long nativeHuhiRewardsNativeWorker);
    private native double nativeGetPublisherRecurrentDonationAmount(long nativeHuhiRewardsNativeWorker, String publisher);
    private native void nativeRemoveRecurring(long nativeHuhiRewardsNativeWorker, String publisher);
    private native void nativeResetTheWholeState(long nativeHuhiRewardsNativeWorker);
    private native void nativeFetchGrants(long nativeHuhiRewardsNativeWorker);
    private native int nativeGetAdsPerHour(long nativeHuhiRewardsNativeWorker);
    private native void nativeSetAdsPerHour(long nativeHuhiRewardsNativeWorker, int value);
    private native boolean nativeIsAnonWallet(long nativeHuhiRewardsNativeWorker);
    private native void nativeGetExternalWallet(long nativeHuhiRewardsNativeWorker);
    private native void nativeDisconnectWallet(long nativeHuhiRewardsNativeWorker, String wallet_type);
    private native void nativeProcessRewardsPageUrl(long nativeHuhiRewardsNativeWorker, String path, String query);
    private native void nativeRecoverWallet(long nativeHuhiRewardsNativeWorker, String passPhrase);
    private native void nativeRefreshPublisher(long nativeHuhiRewardsNativeWorker, String publisherKey);
    private native void nativeGetRewardsParameters(long nativeHuhiRewardsNativeWorker);
    private native void nativeSetAutoContributeEnabled(long nativeHuhiRewardsNativeWorker, boolean isSetAutoContributeEnabled);
    private native void nativeSetAutoContributionAmount(long nativeHuhiRewardsNativeWorker, double amount);
    private native void nativeStartProcess(long nativeHuhiRewardsNativeWorker);
}
