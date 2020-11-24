/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.huhi.bytecode;

import org.objectweb.asm.ClassVisitor;

public class HuhiClassAdapter {
    public static ClassVisitor createAdapter(ClassVisitor chain) {
        chain = new HuhiMainPreferenceBaseClassAdapter(chain);
        chain = new HuhiAndroidSyncSettingsClassAdapter(chain);
        chain = new HuhiLaunchIntentDispatcherClassAdapter(chain);
        chain = new HuhiHomepageManagerClassAdapter(chain);
        chain = new HuhiManageSyncSettingsClassAdapter(chain);
        chain = new HuhiNewTabPageLayoutClassAdapter(chain);
        chain = new HuhiFeedSurfaceCoordinatorClassAdapter(chain);
        chain = new HuhiNewTabPageClassAdapter(chain);
        chain = new HuhiEditUrlSuggestionProcessorClassAdapter(chain);
        chain = new HuhiSearchEngineAdapterClassAdapter(chain);
        chain = new HuhiCommandLineInitUtilClassAdapter(chain);
        return chain;
    }
}
