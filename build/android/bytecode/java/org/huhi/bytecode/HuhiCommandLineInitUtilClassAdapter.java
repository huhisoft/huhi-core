/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.huhi.bytecode;

import org.objectweb.asm.ClassVisitor;

public class HuhiCommandLineInitUtilClassAdapter extends HuhiClassVisitor {
    static String sCommandLineClassName =
        "org/chromium/base/CommandLineInitUtil";

    static String sHuhiCommandLineClassName =
        "org/chromium/base/HuhiCommandLineInitUtil";

    static String sMethodReadFileAsUtf8 = "initCommandLine";

    public HuhiCommandLineInitUtilClassAdapter(ClassVisitor visitor) {
        super(visitor);
        changeMethodOwner(sCommandLineClassName, sMethodReadFileAsUtf8,
                          sHuhiCommandLineClassName);
    }
}
