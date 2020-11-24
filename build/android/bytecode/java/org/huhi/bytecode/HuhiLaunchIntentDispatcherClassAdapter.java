/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.huhi.bytecode;

import org.objectweb.asm.ClassVisitor;

public class HuhiLaunchIntentDispatcherClassAdapter extends HuhiClassVisitor {
    static String sLaunchIntentDispatcherClassName = "org/chromium/chrome/browser/LaunchIntentDispatcher";
    static String sHuhiLaunchIntentDispatcherClassName = "org/chromium/chrome/browser/HuhiLaunchIntentDispatcher";

    public HuhiLaunchIntentDispatcherClassAdapter(ClassVisitor visitor) {
        super(visitor);
        changeMethodOwner(sLaunchIntentDispatcherClassName, "isCustomTabIntent", sHuhiLaunchIntentDispatcherClassName);
    }
}
