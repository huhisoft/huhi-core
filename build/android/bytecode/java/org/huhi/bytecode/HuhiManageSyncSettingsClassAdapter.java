/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.huhi.bytecode;

import org.objectweb.asm.ClassVisitor;

public class HuhiManageSyncSettingsClassAdapter extends HuhiClassVisitor {
    static String sManageSyncSettingsClassName =
            "org/chromium/chrome/browser/sync/settings/ManageSyncSettings";
    static String sHuhiManageSyncSettingsClassName =
            "org/chromium/chrome/browser/sync/settings/HuhiManageSyncSettings";

    HuhiManageSyncSettingsClassAdapter(ClassVisitor visitor) {
        super(visitor);

        deleteField(sHuhiManageSyncSettingsClassName, "mGoogleActivityControls");
        makeProtectedField(sManageSyncSettingsClassName, "mGoogleActivityControls");

        deleteField(sHuhiManageSyncSettingsClassName, "mSyncEncryption");
        makeProtectedField(sManageSyncSettingsClassName, "mSyncEncryption");

        deleteField(sHuhiManageSyncSettingsClassName, "mManageSyncData");
        makeProtectedField(sManageSyncSettingsClassName, "mManageSyncData");

        deleteField(sHuhiManageSyncSettingsClassName, "mSyncPaymentsIntegration");
        makeProtectedField(sManageSyncSettingsClassName, "mSyncPaymentsIntegration");
    }
}
