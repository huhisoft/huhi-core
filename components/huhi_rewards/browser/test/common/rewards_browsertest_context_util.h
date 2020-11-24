/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_TEST_COMMON_REWARDS_BROWSERTEST_CONTEXT_UTIL_H_
#define HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_TEST_COMMON_REWARDS_BROWSERTEST_CONTEXT_UTIL_H_

#include <string>
#include <vector>

#include "build/build_config.h"

namespace content {
class WebContents;
}  // namespace content

namespace rewards_browsertest_util {

void WaitForElementToAppear(
    content::WebContents* context,
    const std::string& selector,
    bool should_appear = true);

void WaitForElementToEqual(
    content::WebContents*,
    const std::string& selector,
    const std::string& expectedValue);

void WaitForElementToContain(
    content::WebContents* context,
    const std::string& selector,
    const std::string& substring);

void WaitForElementToContainHTML(
    content::WebContents* context,
    const std::string& selector,
    const std::string& html);

void WaitForElementThenClick(
    content::WebContents* context,
    const std::string& selector);

std::string WaitForElementThenGetAttribute(
    content::WebContents* context,
    const std::string& selector,
    const std::string& attribute_name);

std::string WaitForElementThenGetContent(
    content::WebContents* context,
    const std::string& selector);

void DragAndDrop(
    content::WebContents* context,
    const std::string& drag_selector,
    const std::string& drop_selector);

void IsMediaTipsInjected(content::WebContents* contents, bool should_appear);

std::vector<double> GetSiteBannerTipOptions(content::WebContents* site_banner);

std::vector<double> GetRewardsPopupTipOptions(content::WebContents* popup);

}  // namespace rewards_browsertest_util

#endif  // HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_TEST_COMMON_REWARDS_BROWSERTEST_CONTEXT_UTIL_H_
