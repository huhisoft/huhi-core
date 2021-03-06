/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.settings;

import android.content.Context;
import android.view.View;

import org.chromium.chrome.browser.search_engines.settings.SearchEngineAdapter;
import org.chromium.components.search_engines.TemplateUrl;

public class HuhiSearchEngineAdapter extends SearchEngineAdapter {
    private boolean mIsPrivate;

    public HuhiSearchEngineAdapter(Context context, boolean isPrivate) {
        super(context);
        mIsPrivate = isPrivate;
    }

    @Override
    public void onClick(View view) {
        super.onClick(view);

        if (view.getTag() == null) {
            return;
        }

        TemplateUrl templateUrl = (TemplateUrl) getItem((int) view.getTag());
        HuhiSearchEngineUtils.setDSEPrefs(templateUrl, mIsPrivate);
    }

    @Override
    public void start() {
        HuhiSearchEngineUtils.updateActiveDSE(mIsPrivate);
        super.start();
    }
}
