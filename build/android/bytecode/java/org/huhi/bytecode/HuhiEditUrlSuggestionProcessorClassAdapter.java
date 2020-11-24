/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.huhi.bytecode;

import org.objectweb.asm.ClassVisitor;

public class HuhiEditUrlSuggestionProcessorClassAdapter extends HuhiClassVisitor {
    static String sEditUrlSuggestionProcessor =
            "org/chromium/chrome/browser/omnibox/suggestions/editurl/EditUrlSuggestionProcessor";
    static String sHuhiEditUrlSuggestionProcessor =
            "org/chromium/chrome/browser/omnibox/suggestions/editurl/HuhiEditUrlSuggestionProcessor";

    public HuhiEditUrlSuggestionProcessorClassAdapter(ClassVisitor visitor) {
        super(visitor);

        deleteField(sHuhiEditUrlSuggestionProcessor, "mHasClearedOmniboxForFocus");
        makeProtectedField(sEditUrlSuggestionProcessor, "mHasClearedOmniboxForFocus");
    }
}
