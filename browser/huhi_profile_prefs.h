/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_HUHI_HUHI_PROFILE_PREFS_H_
#define HUHI_BROWSER_HUHI_HUHI_PROFILE_PREFS_H_

namespace user_prefs {
class PrefRegistrySyncable;
}

namespace huhi {

void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

}  // namespace huhi

#endif  // HUHI_BROWSER_HUHI_HUHI_PROFILE_PREFS_H_
