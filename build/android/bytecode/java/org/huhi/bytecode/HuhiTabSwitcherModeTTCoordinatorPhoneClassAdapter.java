/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.huhi.bytecode;

import org.objectweb.asm.ClassVisitor;

public class HuhiTabSwitcherModeTTCoordinatorPhoneClassAdapter extends HuhiClassVisitor {
    static String sTabSwitcherModeTTCoordinatorPhoneClassName =
            "org/chromium/chrome/browser/toolbar/top/TabSwitcherModeTTCoordinatorPhone";
    static String sHuhiTabSwitcherModeTTCoordinatorPhoneClassName =
            "org/chromium/chrome/browser/toolbar/top/HuhiTabSwitcherModeTTCoordinatorPhone";

    public HuhiTabSwitcherModeTTCoordinatorPhoneClassAdapter(ClassVisitor visitor) {
        super(visitor);

        deleteField(sHuhiTabSwitcherModeTTCoordinatorPhoneClassName, "mTabSwitcherModeToolbar");
        makeProtectedField(sTabSwitcherModeTTCoordinatorPhoneClassName, "mTabSwitcherModeToolbar");
    }
}
