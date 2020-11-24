/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.huhi.bytecode;

import org.objectweb.asm.ClassVisitor;

public class HuhiNewTabPageLayoutClassAdapter extends HuhiClassVisitor {
    static String sNewTabPageLayoutClassName = "org/chromium/chrome/browser/ntp/NewTabPageLayout";
    static String sHuhiNewTabPageLayoutClassName =
            "org/chromium/chrome/browser/ntp/HuhiNewTabPageLayout";
    static String sNewTabPageLayoutSuperClassName = "android/widget/FrameLayout";

    public HuhiNewTabPageLayoutClassAdapter(ClassVisitor visitor) {
        super(visitor);
        makePublicMethod(sNewTabPageLayoutClassName, "insertSiteSectionView");
        addMethodAnnotation(sHuhiNewTabPageLayoutClassName, "insertSiteSectionView",
                "Ljava/lang/Override;");

        makePublicMethod(sNewTabPageLayoutClassName, "getMaxRowsForMostVisitedTiles");
        addMethodAnnotation(sHuhiNewTabPageLayoutClassName, "getMaxRowsForMostVisitedTiles",
                "Ljava/lang/Override;");

        deleteField(sHuhiNewTabPageLayoutClassName, "mSiteSectionView");
        makeProtectedField(sNewTabPageLayoutClassName, "mSiteSectionView");

        changeSuperName(sNewTabPageLayoutClassName, sNewTabPageLayoutSuperClassName);
    }
}
