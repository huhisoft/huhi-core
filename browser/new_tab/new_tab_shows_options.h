/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_NEW_TAB_NEW_TAB_SHOWS_OPTIONS_H_
#define HUHI_BROWSER_NEW_TAB_NEW_TAB_SHOWS_OPTIONS_H_

#include "url/gurl.h"

class Profile;

namespace base {
class Value;
}  // namespace base

namespace huhi {

enum class NewTabPageShowsOptions {
  kDashboard,
  kHomepage,
  kBlankpage
};

GURL GetNewTabPageURL(Profile* profile);
base::Value GetNewTabShowsOptionsList(Profile* profile);
bool ShouldUseNewTabURLForNewTab(Profile* profile);
bool ShouldNewTabShowDashboard(Profile* profile);
bool ShouldNewTabShowBlankpage(Profile* profile);

}  // namespace huhi

#endif  // HUHI_BROWSER_NEW_TAB_NEW_TAB_SHOWS_OPTIONS_H_
