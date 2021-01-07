/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.huhi.bytecode;

import org.objectweb.asm.ClassVisitor;

public class HuhiTopToolbarCoordinatorClassAdapter extends HuhiClassVisitor {
    static String sTopToolbarCoordinatorClassName =
            "org/chromium/chrome/browser/toolbar/top/TopToolbarCoordinator";
    static String sHuhiTopToolbarCoordinatorClassName =
            "org/chromium/chrome/browser/toolbar/top/HuhiTopToolbarCoordinator";

    public HuhiTopToolbarCoordinatorClassAdapter(ClassVisitor visitor) {
        super(visitor);

        deleteField(sHuhiTopToolbarCoordinatorClassName, "mTabSwitcherModeCoordinatorPhone");
        makeProtectedField(sTopToolbarCoordinatorClassName, "mTabSwitcherModeCoordinatorPhone");

        deleteField(sHuhiTopToolbarCoordinatorClassName, "mOptionalButtonController");
        makeProtectedField(sTopToolbarCoordinatorClassName, "mOptionalButtonController");
    }
}
