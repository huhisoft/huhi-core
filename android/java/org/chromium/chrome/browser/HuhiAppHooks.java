/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser;

import org.chromium.chrome.browser.help.HuhiHelpAndFeedback;
import org.chromium.chrome.browser.help.HelpAndFeedback;
import org.chromium.chrome.browser.partnerbookmarks.PartnerBookmark;
import org.chromium.chrome.browser.partnercustomizations.HuhiPartnerBrowserCustomizations;
import org.chromium.chrome.browser.partnercustomizations.PartnerBrowserCustomizations;

public class HuhiAppHooks extends AppHooksImpl {
    @Override
    public HelpAndFeedback createHelpAndFeedback() {
        return new HuhiHelpAndFeedback();
    }

    @Override
    public PartnerBookmark.BookmarkIterator getPartnerBookmarkIterator() {
        return null;
    }

    @Override
    public PartnerBrowserCustomizations.Provider getCustomizationProvider() {
        return new HuhiPartnerBrowserCustomizations.ProviderPackage();
    }
}
