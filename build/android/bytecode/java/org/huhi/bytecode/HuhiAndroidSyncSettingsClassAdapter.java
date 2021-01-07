/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.huhi.bytecode;

import org.objectweb.asm.ClassVisitor;

public class HuhiAndroidSyncSettingsClassAdapter extends HuhiClassVisitor {
	static String sAndroidSyncSettingsClassName =
            "org/chromium/chrome/browser/sync/AndroidSyncSettings";
    static String sHuhiAndroidSyncSettingsClassName =
            "org/chromium/chrome/browser/sync/HuhiAndroidSyncSettings";

    public HuhiAndroidSyncSettingsClassAdapter(ClassVisitor visitor) {
        super(visitor);

        addMethodAnnotation(sHuhiAndroidSyncSettingsClassName,
            "isSyncEnabled", "Ljava/lang/Override;");
        addMethodAnnotation(sHuhiAndroidSyncSettingsClassName,
            "disableChromeSync", "Ljava/lang/Override;");

        deleteField(sHuhiAndroidSyncSettingsClassName, "mMasterSyncEnabled");
        makeProtectedField(sAndroidSyncSettingsClassName, "mMasterSyncEnabled");
    }
}
