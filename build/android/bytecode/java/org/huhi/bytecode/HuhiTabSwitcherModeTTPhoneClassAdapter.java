/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.huhi.bytecode;

import org.objectweb.asm.ClassVisitor;

public class HuhiTabSwitcherModeTTPhoneClassAdapter extends HuhiClassVisitor {
    static String sTabSwitcherModeTTPhoneClassName =
            "org/chromium/chrome/browser/toolbar/top/TabSwitcherModeTTPhone";
    static String sHuhiTabSwitcherModeTTPhoneClassName =
            "org/chromium/chrome/browser/toolbar/top/HuhiTabSwitcherModeTTPhone";

    public HuhiTabSwitcherModeTTPhoneClassAdapter(ClassVisitor visitor) {
        super(visitor);

        deleteField(sHuhiTabSwitcherModeTTPhoneClassName, "mNewTabViewButton");
        makeProtectedField(sTabSwitcherModeTTPhoneClassName, "mNewTabViewButton");

        deleteField(sHuhiTabSwitcherModeTTPhoneClassName, "mNewTabImageButton");
        makeProtectedField(sTabSwitcherModeTTPhoneClassName, "mNewTabImageButton");

        deleteField(sHuhiTabSwitcherModeTTPhoneClassName, "mToggleTabStackButton");
        makeProtectedField(sTabSwitcherModeTTPhoneClassName, "mToggleTabStackButton");

        deleteField(sHuhiTabSwitcherModeTTPhoneClassName, "mShouldShowNewTabVariation");
        makeProtectedField(sTabSwitcherModeTTPhoneClassName, "mShouldShowNewTabVariation");

        makePublicMethod(sTabSwitcherModeTTPhoneClassName, "updateNewTabButtonVisibility");
        addMethodAnnotation(sHuhiTabSwitcherModeTTPhoneClassName, "updateNewTabButtonVisibility",
                "Ljava/lang/Override;");

        makePublicMethod(sTabSwitcherModeTTPhoneClassName, "shouldShowIncognitoToggle");
        deleteMethod(sHuhiTabSwitcherModeTTPhoneClassName, "shouldShowIncognitoToggle");
    }
}
