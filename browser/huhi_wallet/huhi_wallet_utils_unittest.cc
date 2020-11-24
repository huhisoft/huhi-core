/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/huhi_wallet/huhi_wallet_utils.h"

#include <memory>
#include <string>
#include <utility>

#include "huhi/common/huhi_wallet_constants.h"
#include "huhi/common/pref_names.h"
#include "chrome/browser/prefs/browser_prefs.h"
#include "chrome/test/base/testing_profile.h"
#include "components/sync_preferences/testing_pref_service_syncable.h"
#include "content/public/test/browser_task_environment.h"
#include "extensions/browser/extension_prefs.h"
#include "extensions/browser/extension_registry.h"
#include "extensions/common/constants.h"
#include "extensions/common/extension_builder.h"
#include "testing/gtest/include/gtest/gtest.h"

class HuhiWalletUtilsUnitTest : public testing::Test {
 public:
  void SetUp() override {
    profile_ = CreateProfile();
  }

  Profile* profile() {
    return profile_.get();
  }

  void AddCryptoWallets() {
    AddExtension(ethereum_remote_client_extension_id,
        &crypto_wallets_extension);
  }

  void AddMetaMask() {
    AddExtension(metamask_extension_id, &metamask_extension);
  }

 private:
  void AddExtension(const std::string& extension_id,
       scoped_refptr<const extensions::Extension> *extension) {
    extensions::DictionaryBuilder manifest;
    manifest.Set("name", "ext")
        .Set("version", "0.1")
        .Set("manifest_version", 2);
    *extension = extensions::ExtensionBuilder()
        .SetManifest(manifest.Build())
        .SetID(extension_id)
        .Build();
    ASSERT_TRUE(extension->get());
    extensions::ExtensionPrefs::Get(profile())->UpdateExtensionPref(
        extension_id, "test", std::make_unique<base::Value>(""));
    extensions::ExtensionRegistry::Get(profile())->AddEnabled(extension->get());
  }

  std::unique_ptr<TestingProfile> CreateProfile() {
    TestingProfile::Builder builder;
    auto prefs =
        std::make_unique<sync_preferences::TestingPrefServiceSyncable>();
    RegisterUserProfilePrefs(prefs->registry());
    builder.SetPrefService(std::move(prefs));
    return builder.Build();
  }

  content::BrowserTaskEnvironment task_environment_;
  std::unique_ptr<TestingProfile> profile_;
  scoped_refptr<const extensions::Extension> metamask_extension;
  scoped_refptr<const extensions::Extension> crypto_wallets_extension;
};

// If Crypto Wallets was disabled and MetaMask is installed, set to MetaMask
TEST_F(HuhiWalletUtilsUnitTest, TestPrefMigrationMMCryptoWalletsDisabled) {
  AddMetaMask();
  profile()->GetPrefs()->SetBoolean(kHuhiWalletEnabledDeprecated, false);

  huhi_wallet::MigrateHuhiWalletPrefs(profile());

  auto provider = static_cast<HuhiWalletWeb3ProviderTypes>(
      profile()->GetPrefs()->GetInteger(kHuhiWalletWeb3Provider));
  ASSERT_EQ(provider, HuhiWalletWeb3ProviderTypes::METAMASK);
}

// If Crypto Wallets is diabled, and MetaMask not installed, set None
TEST_F(HuhiWalletUtilsUnitTest, TestPrefMigrationCryptoWalletsDisabled) {
  AddCryptoWallets();
  profile()->GetPrefs()->SetBoolean(kHuhiWalletEnabledDeprecated, false);

  huhi_wallet::MigrateHuhiWalletPrefs(profile());

  auto provider = static_cast<HuhiWalletWeb3ProviderTypes>(
      profile()->GetPrefs()->GetInteger(kHuhiWalletWeb3Provider));
  ASSERT_EQ(provider, HuhiWalletWeb3ProviderTypes::NONE);
}

// If Crypto Wallets is enabled, and MetaMask is installed, set
// to Crypto Wallets
TEST_F(HuhiWalletUtilsUnitTest, TestPrefMigrationCryptoWalletsAndMMInstalled) {
  profile()->GetPrefs()->SetBoolean(kHuhiWalletEnabledDeprecated, true);
  AddCryptoWallets();
  AddMetaMask();

  huhi_wallet::MigrateHuhiWalletPrefs(profile());

  auto provider = static_cast<HuhiWalletWeb3ProviderTypes>(
      profile()->GetPrefs()->GetInteger(kHuhiWalletWeb3Provider));
  ASSERT_EQ(provider, HuhiWalletWeb3ProviderTypes::CRYPTO_WALLETS);
}

// If CryptoWallets is enabled and installed, but MetaMask is not
// installed, set Crypto Wallets.
TEST_F(HuhiWalletUtilsUnitTest, TestPrefMigrationCryptoWalletsInstalled) {
  profile()->GetPrefs()->SetBoolean(kHuhiWalletEnabledDeprecated, true);
  AddCryptoWallets();

  huhi_wallet::MigrateHuhiWalletPrefs(profile());

  auto provider = static_cast<HuhiWalletWeb3ProviderTypes>(
      profile()->GetPrefs()->GetInteger(kHuhiWalletWeb3Provider));
  ASSERT_EQ(provider, HuhiWalletWeb3ProviderTypes::CRYPTO_WALLETS);
}

// If CryptoWallets is enabled and not installed yet, and MetaMask is not
// installed, set Ask
TEST_F(HuhiWalletUtilsUnitTest, TestPrefMigrationNothingInstalled) {
  profile()->GetPrefs()->SetBoolean(kHuhiWalletEnabledDeprecated, true);

  huhi_wallet::MigrateHuhiWalletPrefs(profile());

  auto provider = static_cast<HuhiWalletWeb3ProviderTypes>(
      profile()->GetPrefs()->GetInteger(kHuhiWalletWeb3Provider));
  ASSERT_EQ(provider, HuhiWalletWeb3ProviderTypes::ASK);
}
