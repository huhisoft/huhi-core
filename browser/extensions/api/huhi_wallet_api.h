/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_EXTENSIONS_API_HUHI_WALLET_API_H_
#define HUHI_BROWSER_EXTENSIONS_API_HUHI_WALLET_API_H_

#include <string>

#include "extensions/browser/extension_function.h"

class Profile;

namespace extensions {
namespace api {

class HuhiWalletPromptToEnableWalletFunction :
    public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiWallet.promptToEnableWallet", UNKNOWN)

 protected:
  ~HuhiWalletPromptToEnableWalletFunction() override {}
  ResponseAction Run() override;
};

class HuhiWalletReadyFunction :
    public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiWallet.ready", UNKNOWN)

 protected:
  ~HuhiWalletReadyFunction() override {}
  ResponseAction Run() override;
};

class HuhiWalletShouldCheckForDappsFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiWallet.shouldCheckForDapps", UNKNOWN)

 protected:
  ~HuhiWalletShouldCheckForDappsFunction() override {}
  ResponseAction Run() override;
};

class HuhiWalletLoadUIFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiWallet.loadUI", UNKNOWN)
  void OnLoaded();

 protected:
  ~HuhiWalletLoadUIFunction() override {}
  ResponseAction Run() override;
};

class HuhiWalletShouldPromptForSetupFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiWallet.shouldPromptForSetup", UNKNOWN)

 protected:
  ~HuhiWalletShouldPromptForSetupFunction() override {}
  ResponseAction Run() override;
};

class HuhiWalletGetWalletSeedFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiWallet.getWalletSeed", UNKNOWN)

 protected:
  ~HuhiWalletGetWalletSeedFunction() override {}
  ResponseAction Run() override;
};

class HuhiWalletGetBitGoSeedFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiWallet.getBitGoSeed", UNKNOWN)

 protected:
  ~HuhiWalletGetBitGoSeedFunction() override {}
  ResponseAction Run() override;
};

class HuhiWalletGetProjectIDFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiWallet.getProjectID", UNKNOWN)

 protected:
  ~HuhiWalletGetProjectIDFunction() override {}
  ResponseAction Run() override;
};

class HuhiWalletGetHuhiKeyFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiWallet.getHuhiKey", UNKNOWN)

 protected:
  ~HuhiWalletGetHuhiKeyFunction() override {}
  ResponseAction Run() override;
};

class HuhiWalletResetWalletFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiWallet.resetWallet", UNKNOWN)

 protected:
  ~HuhiWalletResetWalletFunction() override {}
  ResponseAction Run() override;
};

class HuhiWalletGetWeb3ProviderFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiWallet.getWeb3Provider", UNKNOWN)

 protected:
  ~HuhiWalletGetWeb3ProviderFunction() override {}
  ResponseAction Run() override;
};

class HuhiWalletGetWeb3ProviderListFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiWallet.getWeb3ProviderList", UNKNOWN)

 protected:
  ~HuhiWalletGetWeb3ProviderListFunction() override {}
  ResponseAction Run() override;
};

}  // namespace api
}  // namespace extensions

#endif  // HUHI_BROWSER_EXTENSIONS_API_HUHI_WALLET_API_H_
