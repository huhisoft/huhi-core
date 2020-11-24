/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_HUHI_PAGES_H_
#define HUHI_BROWSER_UI_HUHI_PAGES_H_

class Browser;

namespace huhi {

void ShowHuhiAdblock(Browser* browser);
void ShowWebcompatReporter(Browser* browser);
void ShowHuhiRewards(Browser* browser);
void ShowHuhiWallet(Browser* browser);
void ShowExtensionSettings(Browser* browser);
void ShowSync(Browser* browser);

}  // namespace huhi

#endif  // HUHI_BROWSER_UI_HUHI_PAGES_H_
