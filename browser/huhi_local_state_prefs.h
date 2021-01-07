/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_HUHI_LOCAL_STATE_PREFS_H_
#define HUHI_BROWSER_HUHI_LOCAL_STATE_PREFS_H_

class PrefRegistrySimple;

namespace huhi {

void RegisterLocalStatePrefs(PrefRegistrySimple* registry);

}  // namespace huhi

#endif  // HUHI_BROWSER_HUHI_LOCAL_STATE_PREFS_H_
