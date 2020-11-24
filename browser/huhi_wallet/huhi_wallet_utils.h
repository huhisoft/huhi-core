/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_HUHI_WALLET_HUHI_WALLET_UTILS_H_
#define HUHI_BROWSER_HUHI_WALLET_HUHI_WALLET_UTILS_H_

class Profile;

namespace user_prefs {
class PrefRegistrySyncable;
}

namespace huhi_wallet {

void MigrateHuhiWalletPrefs(Profile* profile);
void RegisterHuhiWalletProfilePrefsForMigration(
    user_prefs::PrefRegistrySyncable* registry);

}  // namespace huhi_wallet

#endif  // HUHI_BROWSER_HUHI_WALLET_HUHI_WALLET_UTILS_H_
