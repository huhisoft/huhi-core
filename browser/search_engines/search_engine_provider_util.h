/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_SEARCH_ENGINES_SEARCH_ENGINE_PROVIDER_UTIL_H_
#define HUHI_BROWSER_SEARCH_ENGINES_SEARCH_ENGINE_PROVIDER_UTIL_H_

class Profile;

namespace user_prefs {
class PrefRegistrySyncable;
}

namespace huhi {

bool UseAlternativeSearchEngineProviderEnabled(Profile* profile);

void ToggleUseAlternativeSearchEngineProvider(Profile* profile);

bool IsRegionForQwant(Profile* profile);

}  // namespace huhi

#endif  // HUHI_BROWSER_SEARCH_ENGINES_SEARCH_ENGINE_PROVIDER_UTIL_H_
