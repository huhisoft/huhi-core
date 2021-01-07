/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.huhi.bytecode;

import org.objectweb.asm.ClassVisitor;

public class HuhiFeedSurfaceCoordinatorClassAdapter extends HuhiClassVisitor {
    static String sFeedSurfaceCoordinatorClassName =
            "org/chromium/chrome/browser/feed/FeedSurfaceCoordinator";
    static String sHuhiFeedSurfaceCoordinatorClassName =
            "org/chromium/chrome/browser/feed/HuhiFeedSurfaceCoordinator";

    public HuhiFeedSurfaceCoordinatorClassAdapter(ClassVisitor visitor) {
        super(visitor);

        deleteField(sHuhiFeedSurfaceCoordinatorClassName, "mActivity");
        makeProtectedField(sFeedSurfaceCoordinatorClassName, "mActivity");

        deleteField(sHuhiFeedSurfaceCoordinatorClassName, "mScrollViewForPolicy");
        makeProtectedField(sFeedSurfaceCoordinatorClassName, "mScrollViewForPolicy");

        deleteField(sHuhiFeedSurfaceCoordinatorClassName, "mNtpHeader");
        makeProtectedField(sFeedSurfaceCoordinatorClassName, "mNtpHeader");

        deleteField(sHuhiFeedSurfaceCoordinatorClassName, "mRootView");
        makeProtectedField(sFeedSurfaceCoordinatorClassName, "mRootView");
    }
}
