/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_WALLET_PREF_NAMES_H_
#define HUHI_COMPONENTS_HUHI_WALLET_PREF_NAMES_H_

extern const char kHuhiWalletAES256GCMSivNonce[];
extern const char kHuhiWalletEncryptedSeed[];
// Deprecated in favor of kHuhiWalletWeb3Provider
extern const char kHuhiWalletEnabledDeprecated[];
extern const char kHuhiWalletPrefVersion[];
extern const char kHuhiWalletWeb3Provider[];
extern const char kLoadCryptoWalletsOnStartup[];
extern const char kOptedIntoCryptoWallets[];

#endif  // HUHI_COMPONENTS_HUHI_WALLET_PREF_NAMES_H_
