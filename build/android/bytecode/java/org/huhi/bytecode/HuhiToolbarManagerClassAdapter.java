/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.huhi.bytecode;

import org.objectweb.asm.ClassVisitor;

public class HuhiToolbarManagerClassAdapter extends HuhiClassVisitor {
    static String sToolbarManagerClassName = "org/chromium/chrome/browser/toolbar/ToolbarManager";
    static String sHuhiToolbarManagerClassName =
            "org/chromium/chrome/browser/toolbar/HuhiToolbarManager";

    public HuhiToolbarManagerClassAdapter(ClassVisitor visitor) {
        super(visitor);

        deleteField(sHuhiToolbarManagerClassName, "mBottomControlsCoordinator");
        makeProtectedField(sToolbarManagerClassName, "mBottomControlsCoordinator");

        deleteField(sHuhiToolbarManagerClassName, "mBrowserControlsSizer");
        makeProtectedField(sToolbarManagerClassName, "mBrowserControlsSizer");

        deleteField(sHuhiToolbarManagerClassName, "mFullscreenManager");
        makeProtectedField(sToolbarManagerClassName, "mFullscreenManager");

        deleteField(sHuhiToolbarManagerClassName, "mActivityTabProvider");
        makeProtectedField(sToolbarManagerClassName, "mActivityTabProvider");

        deleteField(sHuhiToolbarManagerClassName, "mAppThemeColorProvider");
        makeProtectedField(sToolbarManagerClassName, "mAppThemeColorProvider");

        deleteField(sHuhiToolbarManagerClassName, "mShareDelegateSupplier");
        makeProtectedField(sToolbarManagerClassName, "mShareDelegateSupplier");

        deleteField(sHuhiToolbarManagerClassName, "mScrimCoordinator");
        makeProtectedField(sToolbarManagerClassName, "mScrimCoordinator");

        deleteField(sHuhiToolbarManagerClassName, "mActivity");
        makeProtectedField(sToolbarManagerClassName, "mActivity");

        deleteField(sHuhiToolbarManagerClassName, "mShowStartSurfaceSupplier");
        makeProtectedField(sToolbarManagerClassName, "mShowStartSurfaceSupplier");

        deleteField(sHuhiToolbarManagerClassName, "mOverviewModeBehaviorSupplier");
        makeProtectedField(sToolbarManagerClassName, "mOverviewModeBehaviorSupplier");

        deleteField(sHuhiToolbarManagerClassName, "mMenuButtonCoordinator");
        makeProtectedField(sToolbarManagerClassName, "mMenuButtonCoordinator");

        deleteField(sHuhiToolbarManagerClassName, "mToolbarTabController");
        makeProtectedField(sToolbarManagerClassName, "mToolbarTabController");

        deleteField(sHuhiToolbarManagerClassName, "mLocationBar");
        makeProtectedField(sToolbarManagerClassName, "mLocationBar");

        deleteField(sHuhiToolbarManagerClassName, "mActionModeController");
        makeProtectedField(sToolbarManagerClassName, "mActionModeController");

        deleteField(sHuhiToolbarManagerClassName, "mLocationBarModel");
        makeProtectedField(sToolbarManagerClassName, "mLocationBarModel");

        deleteField(sHuhiToolbarManagerClassName, "mToolbar");
        makeProtectedField(sToolbarManagerClassName, "mToolbar");

        deleteField(sHuhiToolbarManagerClassName, "mBookmarkBridgeSupplier");
        makeProtectedField(sToolbarManagerClassName, "mBookmarkBridgeSupplier");

        makePublicMethod(sToolbarManagerClassName, "onOrientationChange");
        addMethodAnnotation(
                sHuhiToolbarManagerClassName, "onOrientationChange", "Ljava/lang/Override;");

        makePublicMethod(sToolbarManagerClassName, "updateButtonStatus");
        addMethodAnnotation(
                sHuhiToolbarManagerClassName, "updateButtonStatus", "Ljava/lang/Override;");

        makePublicMethod(sToolbarManagerClassName, "updateBookmarkButtonStatus");
        addMethodAnnotation(sHuhiToolbarManagerClassName, "updateBookmarkButtonStatus",
                "Ljava/lang/Override;");

        makePublicMethod(sToolbarManagerClassName, "updateReloadState");
        deleteMethod(sHuhiToolbarManagerClassName, "updateReloadState");
    }
}
