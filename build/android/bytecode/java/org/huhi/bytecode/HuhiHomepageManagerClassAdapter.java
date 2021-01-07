/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.huhi.bytecode;

import org.objectweb.asm.ClassVisitor;

public class HuhiHomepageManagerClassAdapter extends HuhiClassVisitor {
    static String sHomepageManagerClassName = "org/chromium/chrome/browser/homepage/HomepageManager";
    static String sHuhiHomepageManagerClassName = "org/chromium/chrome/browser/homepage/HuhiHomepageManager";

    public HuhiHomepageManagerClassAdapter(ClassVisitor visitor) {
        super(visitor);
        changeMethodOwner(sHomepageManagerClassName, "shouldCloseAppWithZeroTabs", sHuhiHomepageManagerClassName);
    }
}
