/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/huhi_wallet/huhi_wallet_utils.h"

#include "huhi/common/huhi_wallet_constants.h"
#include "huhi/common/pref_names.h"
#include "chrome/browser/profiles/profile.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/pref_registry/pref_registry_syncable.h"
#include "extensions/browser/extension_prefs.h"
#include "extensions/common/constants.h"

namespace {

void MigrateHuhiWalletPrefs_V0_V1(Profile* profile) {
  PrefService* prefs = profile->GetPrefs();
  bool wallet_was_enabled = true;  // true was the default
  if (prefs->HasPrefPath(kHuhiWalletEnabledDeprecated)) {
    wallet_was_enabled = prefs->GetBoolean(kHuhiWalletEnabledDeprecated);
  }

  bool has_crypto_wallets = extensions::ExtensionPrefs::Get(profile)->
      HasPrefForExtension(ethereum_remote_client_extension_id);
  bool has_metamask = extensions::ExtensionPrefs::Get(profile)->
      HasPrefForExtension(metamask_extension_id);

  HuhiWalletWeb3ProviderTypes provider =
      HuhiWalletWeb3ProviderTypes::ASK;
  if (!wallet_was_enabled&& has_metamask) {
    // If Crypto Wallets was disabled and MetaMask is installed, set to MetaMask
    provider = HuhiWalletWeb3ProviderTypes::METAMASK;
  } else if (!wallet_was_enabled && !has_metamask) {
    // If Crypto Wallets is diabled, and MetaMask not installed, set None
    provider = HuhiWalletWeb3ProviderTypes::NONE;
  } else if (wallet_was_enabled && has_metamask) {
    // If Crypto Wallets is enabled, and MetaMask is installed, set
    // to Crypto Wallets
    provider = HuhiWalletWeb3ProviderTypes::CRYPTO_WALLETS;
  } else if (has_crypto_wallets && wallet_was_enabled) {
    // If CryptoWallets is enabled and installed, but MetaMask is not
    // installed, set Crypto Wallets.
    provider = HuhiWalletWeb3ProviderTypes::CRYPTO_WALLETS;
  } else if (!has_crypto_wallets && wallet_was_enabled) {
    // If CryptoWallets is enabled and not installed yet, and MetaMask is not
    // installed, set Ask
    provider = HuhiWalletWeb3ProviderTypes::ASK;
  }
  prefs->SetInteger(kHuhiWalletWeb3Provider, static_cast<int>(provider));
  prefs->ClearPref(kHuhiWalletEnabledDeprecated);
  prefs->SetInteger(kHuhiWalletPrefVersion, 1);
}

}  // namespace

namespace huhi_wallet {

void RegisterHuhiWalletProfilePrefsForMigration(
    user_prefs::PrefRegistrySyncable* registry) {
  registry->RegisterBooleanPref(kHuhiWalletEnabledDeprecated, true);
}

void MigrateHuhiWalletPrefs(Profile* profile) {
  PrefService* prefs = profile->GetPrefs();
  if (prefs->GetInteger(kHuhiWalletPrefVersion) == 0) {
    MigrateHuhiWalletPrefs_V0_V1(profile);
  }
}

}  // namespace huhi_wallet
