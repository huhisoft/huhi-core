/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser;

import android.support.test.filters.SmallTest;
import android.view.View;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.runner.RunWith;

import org.chromium.chrome.R;
import org.chromium.chrome.browser.app.ChromeActivity;
import org.chromium.chrome.browser.ntp.HuhiDuckDuckGoOfferView;
import org.chromium.chrome.browser.ntp.IncognitoNewTabPage;
import org.chromium.chrome.browser.onboarding.OnboardingPrefManager;
import org.chromium.chrome.browser.preferences.SharedPreferencesManager;
import org.chromium.chrome.browser.settings.HuhiSearchEngineUtils;
import org.chromium.chrome.test.ChromeActivityTestRule;
import org.chromium.chrome.test.ChromeJUnit4ClassRunner;
import org.chromium.components.search_engines.TemplateUrl;
import org.chromium.content_public.browser.test.util.TestThreadUtils;

/**
 * Huhi specific tests for private tab
 */
@RunWith(ChromeJUnit4ClassRunner.class)
public class HuhiPrivateTabTest {
    @Rule
    public ChromeActivityTestRule<ChromeActivity> mActivityTestRule = new ChromeActivityTestRule<>(
            ChromeActivity.class);

    @Before
    public void setUp() throws Exception {
        // Disable key checker to avoid asserts on Huhi keys in debug
        SharedPreferencesManager.getInstance().disableKeyCheckerForTesting();
        OnboardingPrefManager.getInstance().setOnboardingShown(false);
        mActivityTestRule.startMainActivityOnBlankPage();
    }

    @Test
    @SmallTest
    public void testHuhiPrivateTabDdgVisible() throws Exception {
        mActivityTestRule.newIncognitoTabFromMenu();
        final IncognitoNewTabPage ntp = (IncognitoNewTabPage) mActivityTestRule.getActivity().getActivityTab()
                .getNativePage();

        TestThreadUtils.runOnUiThreadBlocking(() -> {
            Assert.assertEquals(ntp.getView().findViewById(R.id.ddg_offer_link).getVisibility(), View.VISIBLE);
        });
    }

    @Test
    @SmallTest
    public void testHuhiPrivateTabDdgGone() throws Exception {
        TestThreadUtils.runOnUiThreadBlocking(() -> {
            TemplateUrl templateUrl = HuhiSearchEngineUtils
                    .getTemplateUrlByShortName(HuhiDuckDuckGoOfferView.DDG_SEARCH_ENGINE_SHORT_NAME);
            if (templateUrl != null) {
                HuhiSearchEngineUtils.setDSEPrefs(templateUrl, true);
                HuhiSearchEngineUtils.updateActiveDSE(true);
            }
        });

        mActivityTestRule.newIncognitoTabFromMenu();
        final IncognitoNewTabPage ntp = (IncognitoNewTabPage) mActivityTestRule.getActivity().getActivityTab()
                .getNativePage();

        TestThreadUtils.runOnUiThreadBlocking(() -> {
            Assert.assertEquals(ntp.getView().findViewById(R.id.ddg_offer_link).getVisibility(), View.GONE);
        });
    }
}
