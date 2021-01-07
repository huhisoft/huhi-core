/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.huhi.bytecode;

import org.objectweb.asm.ClassVisitor;

public class HuhiSearchEngineAdapterClassAdapter extends HuhiClassVisitor {
    static String sSearchEngineAdapterClassName =
        "org/chromium/chrome/browser/search_engines/settings/SearchEngineAdapter";

    static String sHuhiSearchEngineAdapterBaseClassName =
        "org/chromium/chrome/browser/search_engines/settings/HuhiBaseSearchEngineAdapter";

    static String sMethodGetPermissionsLinkMessage =
        "getPermissionsLinkMessage";

    static String sMethodGetSearchEngineSourceType =
        "getSearchEngineSourceType";

    static String sMethodSortAndFilterUnnecessaryTemplateUrl = "sortAndFilterUnnecessaryTemplateUrl";

    public HuhiSearchEngineAdapterClassAdapter(ClassVisitor visitor) {
        super(visitor);
        changeSuperName(sSearchEngineAdapterClassName,
                        sHuhiSearchEngineAdapterBaseClassName);
        changeMethodOwner(sSearchEngineAdapterClassName, sMethodGetSearchEngineSourceType,
                          sHuhiSearchEngineAdapterBaseClassName);
        changeMethodOwner(sSearchEngineAdapterClassName, sMethodGetPermissionsLinkMessage,
                          sHuhiSearchEngineAdapterBaseClassName);
        changeMethodOwner(sSearchEngineAdapterClassName, sMethodSortAndFilterUnnecessaryTemplateUrl,
                          sHuhiSearchEngineAdapterBaseClassName);
    }
}
