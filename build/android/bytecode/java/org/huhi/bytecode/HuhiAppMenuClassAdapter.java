/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.huhi.bytecode;

import org.objectweb.asm.ClassVisitor;

public class HuhiAppMenuClassAdapter extends HuhiClassVisitor {
    static String sAppMenuClassName = "org/chromium/chrome/browser/ui/appmenu/AppMenu";

    static String sHuhiAppMenuClassName = "org/chromium/chrome/browser/ui/appmenu/HuhiAppMenu";

    public HuhiAppMenuClassAdapter(ClassVisitor visitor) {
        super(visitor);
        changeMethodOwner(sAppMenuClassName, "getPopupPosition", sHuhiAppMenuClassName);
    }
}
