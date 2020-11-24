/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.sync;

import org.chromium.chrome.browser.sync.ProfileSyncService;
import org.chromium.components.sync.SyncContentResolverDelegate;

// see org.huhi.bytecode.HuhiAndroidSyncSettingsAdapter
public class HuhiAndroidSyncSettings extends AndroidSyncSettings {
    private boolean mMasterSyncEnabled;

    public HuhiAndroidSyncSettings(SyncContentResolverDelegate syncContentResolverDelegate) {
        super(syncContentResolverDelegate);
    }

    // Chromium's AndroidSyncSettings.mChromeSyncEnabled is never set to true
    // after app restart when Huhi sync v2 is enabled, and by this reason on
    // next SyncController.updateSyncStateFromAndroid sync gets disabled, so
    // we act here as mChromeSyncEnabled would be true.
    // Following up issue https://github.com/huhisoft/huhi-browser/issues/10454
    @Override
    public boolean isSyncEnabled() {
        return mMasterSyncEnabled;
    }

    @Override
    public void disableChromeSync() { }

    // We need to override this to make able
    // DevicePickerBottomSheetContent.createContentView send the link
    // For Huhi we don't have an account in Android system account,
    // so pretend sync for Huhi "account" is always on when sync is configured
    @Override
    public boolean isChromeSyncEnabled() {
        ProfileSyncService profileSyncService = ProfileSyncService.get();
        return profileSyncService != null && profileSyncService.isFirstSetupComplete();
    }
}
