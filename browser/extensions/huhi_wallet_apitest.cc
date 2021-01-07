/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "base/path_service.h"
#include "huhi/common/huhi_paths.h"
#include "huhi/common/pref_names.h"
#include "huhi/components/huhi_wallet/huhi_wallet_constants.h"
#include "huhi/components/huhi_wallet/pref_names.h"
#include "chrome/browser/extensions/extension_apitest.h"
#include "components/prefs/pref_service.h"
#include "content/public/test/browser_test.h"
#include "extensions/common/constants.h"
#include "extensions/test/result_catcher.h"

namespace extensions {
namespace {

class HuhiWalletExtensionApiTest : public ExtensionApiTest {
 public:
  void SetUp() override {
    huhi::RegisterPathProvider();
    base::PathService::Get(huhi::DIR_TEST_DATA, &extension_dir_);
    extension_dir_ = extension_dir_.AppendASCII("extensions/api_test");
    ExtensionApiTest::SetUp();
  }
  void TearDown() override {
    ExtensionApiTest::TearDown();
  }
  PrefService* GetPrefs() { return browser()->profile()->GetPrefs(); }
  base::FilePath extension_dir_;
};

IN_PROC_BROWSER_TEST_F(HuhiWalletExtensionApiTest,
    HuhiExtensionWithWalletHasAccess) {
  ResultCatcher catcher;
  const Extension* extension =
    LoadExtension(extension_dir_.AppendASCII("huhiShieldsWithWallet"));
  ASSERT_TRUE(extension);
  ASSERT_TRUE(browsertest_util::ExecuteScriptInBackgroundPageNoWait(
      browser()->profile(), huhi_extension_id,
      "testBasics()"));
  ASSERT_TRUE(catcher.GetNextResult()) << message_;
}

IN_PROC_BROWSER_TEST_F(HuhiWalletExtensionApiTest,
    HuhiWalletAPIAvailable) {
  std::unique_ptr<base::Environment> env(base::Environment::Create());
  env->SetVar("HUHI_INFURA_PROJECT_ID", "test-project-id");
  env->SetVar("HUHI_SERVICES_KEY", "test-huhi-key");
  ResultCatcher catcher;
  const Extension* extension =
    LoadExtension(extension_dir_.AppendASCII("huhiWallet"));
  ASSERT_TRUE(extension);
  ASSERT_TRUE(browsertest_util::ExecuteScriptInBackgroundPageNoWait(
      browser()->profile(), ethereum_remote_client_extension_id,
      "testBasics()"));
  ASSERT_TRUE(catcher.GetNextResult()) << message_;
}

IN_PROC_BROWSER_TEST_F(HuhiWalletExtensionApiTest,
    HuhiWalletAPIKnownValuesTest) {
  GetPrefs()->SetString(kHuhiWalletAES256GCMSivNonce, "yJngKDr5nCGYz7EM");
  GetPrefs()->SetString(kHuhiWalletEncryptedSeed,
      "IQu5fUMbXG6E7v8ITwcIKL3TI3rst0LU1US7ZxCKpgAGgLNAN6DbCN7nMF2Eg7Kx");
  ResultCatcher catcher;
  const Extension* extension =
    LoadExtension(extension_dir_.AppendASCII("huhiWallet"));
  ASSERT_TRUE(extension);
  ASSERT_TRUE(browsertest_util::ExecuteScriptInBackgroundPageNoWait(
      browser()->profile(), ethereum_remote_client_extension_id,
      "testKnownSeedValuesEndToEnd()"));
  ASSERT_TRUE(catcher.GetNextResult()) << message_;
}

IN_PROC_BROWSER_TEST_F(HuhiWalletExtensionApiTest,
    HuhiWalletAPIBitGoKnownValuesTest) {
  GetPrefs()->SetString(kHuhiWalletAES256GCMSivNonce, "yJngKDr5nCGYz7EM");
  GetPrefs()->SetString(kHuhiWalletEncryptedSeed,
      "IQu5fUMbXG6E7v8ITwcIKL3TI3rst0LU1US7ZxCKpgAGgLNAN6DbCN7nMF2Eg7Kx");
  ResultCatcher catcher;
  const Extension* extension =
    LoadExtension(extension_dir_.AppendASCII("huhiWallet"));
  ASSERT_TRUE(extension);
  ASSERT_TRUE(browsertest_util::ExecuteScriptInBackgroundPageNoWait(
      browser()->profile(), ethereum_remote_client_extension_id,
      "testKnownBitGoSeedValuesEndToEnd()"));
  ASSERT_TRUE(catcher.GetNextResult()) << message_;
}

IN_PROC_BROWSER_TEST_F(HuhiWalletExtensionApiTest,
    HuhiWalletWeb3ProviderCryptoWallets) {
  GetPrefs()->SetInteger(kHuhiWalletWeb3Provider,
      static_cast<int>(HuhiWalletWeb3ProviderTypes::CRYPTO_WALLETS));
  ResultCatcher catcher;
  const Extension* extension =
    LoadExtension(extension_dir_.AppendASCII("huhiWallet"));
  ASSERT_TRUE(extension);
  ASSERT_TRUE(browsertest_util::ExecuteScriptInBackgroundPageNoWait(
      browser()->profile(), ethereum_remote_client_extension_id,
      "testProviderIsCryptoWallets()"));
  ASSERT_TRUE(catcher.GetNextResult()) << message_;
}

IN_PROC_BROWSER_TEST_F(HuhiWalletExtensionApiTest,
    HuhiWalletWeb3ProviderMetaMask) {
  GetPrefs()->SetInteger(kHuhiWalletWeb3Provider,
      static_cast<int>(HuhiWalletWeb3ProviderTypes::METAMASK));
  ResultCatcher catcher;
  const Extension* extension =
    LoadExtension(extension_dir_.AppendASCII("huhiWallet"));
  ASSERT_TRUE(extension);
  ASSERT_TRUE(browsertest_util::ExecuteScriptInBackgroundPageNoWait(
      browser()->profile(), ethereum_remote_client_extension_id,
      "testProviderIsMetaMask()"));
  ASSERT_TRUE(catcher.GetNextResult()) << message_;
}

IN_PROC_BROWSER_TEST_F(HuhiWalletExtensionApiTest,
    HuhiWalletWeb3ProviderAsk) {
  GetPrefs()->SetInteger(kHuhiWalletWeb3Provider,
      static_cast<int>(HuhiWalletWeb3ProviderTypes::ASK));
  ResultCatcher catcher;
  const Extension* extension =
    LoadExtension(extension_dir_.AppendASCII("huhiWallet"));
  ASSERT_TRUE(extension);
  ASSERT_TRUE(browsertest_util::ExecuteScriptInBackgroundPageNoWait(
      browser()->profile(), ethereum_remote_client_extension_id,
      "testProviderIsAsk()"));
  ASSERT_TRUE(catcher.GetNextResult()) << message_;
}

IN_PROC_BROWSER_TEST_F(HuhiWalletExtensionApiTest,
    HuhiWalletWeb3ProviderNone) {
  GetPrefs()->SetInteger(kHuhiWalletWeb3Provider,
      static_cast<int>(HuhiWalletWeb3ProviderTypes::NONE));
  ResultCatcher catcher;
  const Extension* extension =
    LoadExtension(extension_dir_.AppendASCII("huhiWallet"));
  ASSERT_TRUE(extension);
  ASSERT_TRUE(browsertest_util::ExecuteScriptInBackgroundPageNoWait(
      browser()->profile(), ethereum_remote_client_extension_id,
      "testProviderIsNone()"));
  ASSERT_TRUE(catcher.GetNextResult()) << message_;
}

IN_PROC_BROWSER_TEST_F(HuhiWalletExtensionApiTest,
    HuhiWalletAPINotAvailable) {
  ResultCatcher catcher;
  const Extension* extension =
    LoadExtension(extension_dir_.AppendASCII("notHuhiWallet"));
  ASSERT_TRUE(extension);
  ASSERT_TRUE(catcher.GetNextResult()) << message_;
}

IN_PROC_BROWSER_TEST_F(HuhiWalletExtensionApiTest,
    HuhiShieldsDappDetectionWhenDefault) {
  ResultCatcher catcher;
  const Extension* extension =
    LoadExtension(extension_dir_.AppendASCII("huhiShieldsWithWallet"));
  ASSERT_TRUE(browsertest_util::ExecuteScriptInBackgroundPageNoWait(
      browser()->profile(), huhi_extension_id, "testDappCheck()"));
  ASSERT_TRUE(extension);
  ASSERT_TRUE(catcher.GetNextResult()) << message_;
}

IN_PROC_BROWSER_TEST_F(HuhiWalletExtensionApiTest,
    HuhiShieldsDappDetectionWhenAsk) {
  GetPrefs()->SetInteger(kHuhiWalletWeb3Provider,
      static_cast<int>(HuhiWalletWeb3ProviderTypes::ASK));
  ResultCatcher catcher;
  const Extension* extension =
    LoadExtension(extension_dir_.AppendASCII("huhiShieldsWithWallet"));
  ASSERT_TRUE(browsertest_util::ExecuteScriptInBackgroundPageNoWait(
      browser()->profile(), huhi_extension_id, "testDappCheck()"));
  ASSERT_TRUE(extension);
  ASSERT_TRUE(catcher.GetNextResult()) << message_;
}

IN_PROC_BROWSER_TEST_F(HuhiWalletExtensionApiTest,
    HuhiShieldsNoDappDetectionWhenNone) {
  GetPrefs()->SetInteger(kHuhiWalletWeb3Provider,
      static_cast<int>(HuhiWalletWeb3ProviderTypes::NONE));
  ResultCatcher catcher;
  const Extension* extension =
    LoadExtension(extension_dir_.AppendASCII("huhiShieldsWithWallet"));
  ASSERT_TRUE(browsertest_util::ExecuteScriptInBackgroundPageNoWait(
      browser()->profile(), huhi_extension_id, "testNoDappCheck()"));
  ASSERT_TRUE(extension);
  ASSERT_TRUE(catcher.GetNextResult()) << message_;
}

IN_PROC_BROWSER_TEST_F(HuhiWalletExtensionApiTest,
    HuhiShieldsNoDappDetectionWhenMetaMask) {
  GetPrefs()->SetInteger(kHuhiWalletWeb3Provider,
      static_cast<int>(HuhiWalletWeb3ProviderTypes::METAMASK));
  ResultCatcher catcher;
  const Extension* extension =
    LoadExtension(extension_dir_.AppendASCII("huhiShieldsWithWallet"));
  ASSERT_TRUE(browsertest_util::ExecuteScriptInBackgroundPageNoWait(
      browser()->profile(), huhi_extension_id, "testNoDappCheck()"));
  ASSERT_TRUE(extension);
  ASSERT_TRUE(catcher.GetNextResult()) << message_;
}

IN_PROC_BROWSER_TEST_F(HuhiWalletExtensionApiTest,
    HuhiShieldsNoDappDetectionWhenCryptoWallets) {
  GetPrefs()->SetInteger(kHuhiWalletWeb3Provider,
      static_cast<int>(HuhiWalletWeb3ProviderTypes::CRYPTO_WALLETS));
  ResultCatcher catcher;
  const Extension* extension =
    LoadExtension(extension_dir_.AppendASCII("huhiShieldsWithWallet"));
  LoadExtension(extension_dir_.AppendASCII("huhiWallet"));
  ASSERT_TRUE(browsertest_util::ExecuteScriptInBackgroundPageNoWait(
      browser()->profile(), huhi_extension_id, "testNoDappCheck()"));
  ASSERT_TRUE(extension);
  ASSERT_TRUE(catcher.GetNextResult()) << message_;
}

IN_PROC_BROWSER_TEST_F(HuhiWalletExtensionApiTest,
    HuhiShieldsDappDetectionWhenCryptoWalletsNotReady) {
  GetPrefs()->SetInteger(kHuhiWalletWeb3Provider,
      static_cast<int>(HuhiWalletWeb3ProviderTypes::CRYPTO_WALLETS));
  ResultCatcher catcher;
  const Extension* extension =
    LoadExtension(extension_dir_.AppendASCII("huhiShieldsWithWallet"));
  ASSERT_TRUE(browsertest_util::ExecuteScriptInBackgroundPageNoWait(
      browser()->profile(), huhi_extension_id, "testDappCheck()"));
  ASSERT_TRUE(extension);
  ASSERT_TRUE(catcher.GetNextResult()) << message_;
}

}  // namespace
}  // namespace extensions
