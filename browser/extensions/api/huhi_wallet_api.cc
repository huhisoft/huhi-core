/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/extensions/api/huhi_wallet_api.h"

#include <memory>
#include <string>

#include "base/json/json_writer.h"
#include "base/values.h"
#include "huhi/browser/infobars/crypto_wallets_infobar_delegate.h"
#include "huhi/browser/profiles/profile_util.h"
#include "huhi/common/huhi_wallet_constants.h"
#include "huhi/common/extensions/api/huhi_wallet.h"
#include "huhi/common/pref_names.h"
#include "huhi/grit/huhi_generated_resources.h"
#include "chrome/browser/extensions/api/tabs/tabs_constants.h"
#include "chrome/browser/extensions/extension_tab_util.h"
#include "chrome/browser/infobars/infobar_service.h"
#include "chrome/browser/profiles/profile.h"
#include "components/prefs/pref_service.h"
#include "content/public/browser/web_contents.h"
#include "extensions/browser/extension_registry.h"
#include "extensions/browser/extension_util.h"
#include "extensions/common/constants.h"
#include "huhi/browser/huhi_wallet/huhi_wallet_service_factory.h"
#include "huhi/components/huhi_wallet/browser/huhi_wallet_service.h"
#include "huhi/browser/extensions/huhi_wallet_util.h"
#include "ui/base/l10n/l10n_util.h"

namespace {

HuhiWalletService* GetHuhiWalletService(
    content::BrowserContext* context) {
  return HuhiWalletServiceFactory::GetInstance()
      ->GetForProfile(Profile::FromBrowserContext(context));
}

base::Value MakeSelectValue(const  base::string16& name,
                            HuhiWalletWeb3ProviderTypes value) {
  base::Value item(base::Value::Type::DICTIONARY);
  item.SetKey("value", base::Value(static_cast<int>(value)));
  item.SetKey("name", base::Value(name));
  return item;
}

}  // namespace

namespace extensions {
namespace api {

ExtensionFunction::ResponseAction
HuhiWalletPromptToEnableWalletFunction::Run() {
  std::unique_ptr<huhi_wallet::PromptToEnableWallet::Params> params(
      huhi_wallet::PromptToEnableWallet::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  Profile* profile = Profile::FromBrowserContext(browser_context());
  if (huhi::IsTorProfile(profile)) {
    return RespondNow(Error("Not available in Tor profile"));
  }

  // Get web contents for this tab
  content::WebContents* contents = nullptr;
  if (!ExtensionTabUtil::GetTabById(
        params->tab_id,
        Profile::FromBrowserContext(browser_context()),
        include_incognito_information(),
        nullptr,
        nullptr,
        &contents,
        nullptr)) {
    return RespondNow(Error(tabs_constants::kTabNotFoundError,
                            base::NumberToString(params->tab_id)));
  }

  InfoBarService* infobar_service =
      InfoBarService::FromWebContents(contents);
  if (infobar_service) {
    CryptoWalletsInfoBarDelegate::InfobarSubType subtype =
        CryptoWalletsInfoBarDelegate::InfobarSubType::GENERIC_SETUP;
    auto* service = GetHuhiWalletService(browser_context());
    auto* registry = extensions::ExtensionRegistry::Get(profile);
    if (service->ShouldShowLazyLoadInfobar()) {
      subtype = CryptoWalletsInfoBarDelegate::InfobarSubType::
          LOAD_CRYPTO_WALLETS;
    } else if (registry->ready_extensions().Contains(metamask_extension_id)) {
      subtype = CryptoWalletsInfoBarDelegate::InfobarSubType::
          CRYPTO_WALLETS_METAMASK;
    }
    CryptoWalletsInfoBarDelegate::Create(infobar_service, subtype);
  }

  return RespondNow(NoArguments());
}

ExtensionFunction::ResponseAction
HuhiWalletReadyFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());
  if (huhi::IsTorProfile(profile)) {
    return RespondNow(Error("Not available in Tor profile"));
  }

  auto* service = GetHuhiWalletService(browser_context());
  service->CryptoWalletsExtensionReady();
  return RespondNow(NoArguments());
}

ExtensionFunction::ResponseAction
HuhiWalletLoadUIFunction::Run() {
  auto* service = GetHuhiWalletService(browser_context());
  // If the extension is already ready, respond right away
  if (service->IsCryptoWalletsReady()) {
    return RespondNow(NoArguments());
  }

  // If the user has opt-ed in and MetaMask is not installed, then
  // set the Dapp provider to Crypto Wallets.
  Profile* profile = Profile::FromBrowserContext(browser_context());
  auto* registry = extensions::ExtensionRegistry::Get(profile);
  if (!registry->ready_extensions().Contains(metamask_extension_id)) {
    profile->GetPrefs()->SetInteger(kHuhiWalletWeb3Provider,
        static_cast<int>(HuhiWalletWeb3ProviderTypes::CRYPTO_WALLETS));
  }

  profile->GetPrefs()->SetBoolean(kOptedIntoCryptoWallets, true);
  service->LoadCryptoWalletsExtension(base::BindOnce(
      &HuhiWalletLoadUIFunction::OnLoaded, this));
  return RespondLater();
}

void HuhiWalletLoadUIFunction::OnLoaded() {
  Respond(NoArguments());
}

ExtensionFunction::ResponseAction
HuhiWalletShouldPromptForSetupFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());
  auto* service = HuhiWalletServiceFactory::GetForProfile(profile);
  bool should_prompt = !service->IsCryptoWalletsSetup() &&
      !profile->GetPrefs()->GetBoolean(kOptedIntoCryptoWallets);
  return RespondNow(OneArgument(std::make_unique<base::Value>(should_prompt)));
}

ExtensionFunction::ResponseAction
HuhiWalletShouldCheckForDappsFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());
  auto provider = static_cast<HuhiWalletWeb3ProviderTypes>(
      profile->GetPrefs()->GetInteger(kHuhiWalletWeb3Provider));
  bool dappDetection = !huhi::IsTorProfile(profile);
  if (provider != HuhiWalletWeb3ProviderTypes::ASK) {
    auto* service = GetHuhiWalletService(browser_context());
    dappDetection = provider == HuhiWalletWeb3ProviderTypes::ASK ||
        (provider == HuhiWalletWeb3ProviderTypes::CRYPTO_WALLETS &&
        !service->IsCryptoWalletsReady());
  }
  return RespondNow(OneArgument(
      std::make_unique<base::Value>(dappDetection)));
}

ExtensionFunction::ResponseAction
HuhiWalletGetWalletSeedFunction::Run() {
  // make sure the passed in enryption key is 32 bytes.
  std::unique_ptr<huhi_wallet::GetWalletSeed::Params> params(
    huhi_wallet::GetWalletSeed::Params::Create(*args_));
  if (params->key.size() != 32) {
    return RespondNow(Error("Invalid input key size"));
  }

  auto* service = GetHuhiWalletService(browser_context());

  base::Value::BlobStorage blob;
  std::string derived = service->GetWalletSeed(params->key);

  if (derived.empty()) {
    return RespondNow(Error("Error getting wallet seed"));
  }

  blob.assign(derived.begin(), derived.end());

  return RespondNow(OneArgument(
    std::make_unique<base::Value>(blob)));
}

ExtensionFunction::ResponseAction
HuhiWalletGetBitGoSeedFunction::Run() {
  // make sure the passed in enryption key is 32 bytes.
  std::unique_ptr<huhi_wallet::GetBitGoSeed::Params> params(
    huhi_wallet::GetBitGoSeed::Params::Create(*args_));
  if (params->key.size() != 32) {
    return RespondNow(Error("Invalid input key size"));
  }

  auto* service = GetHuhiWalletService(browser_context());

  base::Value::BlobStorage blob;
  std::string derived = service->GetBitGoSeed(params->key);

  if (derived.empty()) {
    return RespondNow(Error("Error getting wallet seed"));
  }

  blob.assign(derived.begin(), derived.end());

  return RespondNow(OneArgument(
    std::make_unique<base::Value>(blob)));
}

ExtensionFunction::ResponseAction
HuhiWalletGetProjectIDFunction::Run() {
  std::string project_id = extensions::GetInfuraProjectID();
  return RespondNow(OneArgument(
      std::make_unique<base::Value>(project_id)));
}

ExtensionFunction::ResponseAction
HuhiWalletGetHuhiKeyFunction::Run() {
  std::string huhi_key = extensions::GetHuhiKey();
  return RespondNow(OneArgument(
      std::make_unique<base::Value>(huhi_key)));
}

ExtensionFunction::ResponseAction
HuhiWalletResetWalletFunction::Run() {
  auto* service = GetHuhiWalletService(browser_context());
  service->ResetCryptoWallets();
  return RespondNow(NoArguments());
}

ExtensionFunction::ResponseAction
HuhiWalletGetWeb3ProviderFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());
  auto provider = static_cast<HuhiWalletWeb3ProviderTypes>(
      profile->GetPrefs()->GetInteger(kHuhiWalletWeb3Provider));
  std::string extension_id;
  if (provider == HuhiWalletWeb3ProviderTypes::CRYPTO_WALLETS) {
    extension_id = ethereum_remote_client_extension_id;
  } else if (provider == HuhiWalletWeb3ProviderTypes::METAMASK) {
    extension_id = metamask_extension_id;
  }
  return RespondNow(OneArgument(
      std::make_unique<base::Value>(extension_id)));
}

ExtensionFunction::ResponseAction
HuhiWalletGetWeb3ProviderListFunction::Run() {
  base::Value list(base::Value::Type::LIST);
  list.Append(MakeSelectValue(
      l10n_util::GetStringUTF16(IDS_HUHI_WALLET_WEB3_PROVIDER_ASK),
      HuhiWalletWeb3ProviderTypes::ASK));
  list.Append(MakeSelectValue(
      l10n_util::GetStringUTF16(IDS_HUHI_WALLET_WEB3_PROVIDER_NONE),
      HuhiWalletWeb3ProviderTypes::NONE));
  list.Append(MakeSelectValue(
      l10n_util::GetStringUTF16(IDS_HUHI_WALLET_WEB3_PROVIDER_CRYPTO_WALLETS),
      HuhiWalletWeb3ProviderTypes::CRYPTO_WALLETS));
  Profile* profile = Profile::FromBrowserContext(browser_context());
  auto* registry = extensions::ExtensionRegistry::Get(profile);
  if (registry->ready_extensions().Contains(metamask_extension_id)) {
    list.Append(MakeSelectValue(
        l10n_util::GetStringUTF16(IDS_HUHI_WALLET_WEB3_PROVIDER_METAMASK),
        HuhiWalletWeb3ProviderTypes::METAMASK));
  }
  std::string json_string;
  base::JSONWriter::Write(list, &json_string);
  return RespondNow(OneArgument(std::make_unique<base::Value>(json_string)));
}

}  // namespace api
}  // namespace extensions
