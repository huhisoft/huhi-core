/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/ui/webui/huhi_web_ui_controller_factory.h"

#include <memory>

#include "base/feature_list.h"
#include "base/memory/ptr_util.h"
#include "huhi/browser/ui/webui/huhi_adblock_ui.h"
#include "huhi/browser/ui/webui/webcompat_reporter_ui.h"
#include "huhi/common/huhi_features.h"
#include "huhi/common/pref_names.h"
#include "huhi/common/webui_url_constants.h"
#include "huhi/components/huhi_rewards/browser/buildflags/buildflags.h"
#include "huhi/components/huhi_wallet/browser/buildflags/buildflags.h"
#include "huhi/components/ipfs/browser/buildflags/buildflags.h"
#include "huhi/components/ipfs/browser/features.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/common/url_constants.h"
#include "components/prefs/pref_service.h"
#include "url/gurl.h"

#if !defined(OS_ANDROID)
#include "huhi/browser/ui/webui/huhi_new_tab_ui.h"
#include "huhi/browser/ui/webui/huhi_settings_ui.h"
#include "huhi/browser/ui/webui/huhi_welcome_ui.h"
#endif

#if BUILDFLAG(HUHI_REWARDS_ENABLED)
#include "huhi/browser/ui/webui/huhi_tip_ui.h"
#include "huhi/browser/ui/webui/huhi_rewards_internals_ui.h"
#include "huhi/browser/ui/webui/huhi_rewards_page_ui.h"
#endif

#if BUILDFLAG(HUHI_WALLET_ENABLED)
#include "huhi/browser/ui/webui/huhi_wallet_ui.h"
#endif

#if BUILDFLAG(IPFS_ENABLED)
#include "huhi/browser/ui/webui/ipfs_ui.h"
#endif

using content::WebUI;
using content::WebUIController;

namespace {

// A function for creating a new WebUI. The caller owns the return value, which
// may be NULL (for example, if the URL refers to an non-existent extension).
typedef WebUIController* (*WebUIFactoryFunction)(WebUI* web_ui,
                                                 const GURL& url);

// Template for defining WebUIFactoryFunction.
template<class T>
WebUIController* NewWebUI(WebUI* web_ui, const GURL& url) {
  return new T(web_ui);
}

template<>
WebUIController* NewWebUI<BasicUI>(WebUI* web_ui, const GURL& url) {
  auto host = url.host_piece();
  if (host == kAdblockHost) {
    return new HuhiAdblockUI(web_ui, url.host());
  } else if (host == kWebcompatReporterHost) {
    return new WebcompatReporterUI(web_ui, url.host());
#if BUILDFLAG(IPFS_ENABLED)
  } else if (host == kIPFSHost &&
      base::FeatureList::IsEnabled(ipfs::features::kIpfsFeature)) {
    return new IPFSUI(web_ui, url.host());
#endif  // BUILDFLAG(IPFS_ENABLED)
#if BUILDFLAG(HUHI_WALLET_ENABLED)
  } else if (host == kWalletHost) {
    return new HuhiWalletUI(web_ui, url.host());
#endif  // BUILDFLAG(HUHI_WALLET_ENABLED)
#if BUILDFLAG(HUHI_REWARDS_ENABLED)
  } else if (host == kRewardsPageHost) {
    return new HuhiRewardsPageUI(web_ui, url.host());
  } else if (host == kRewardsInternalsHost) {
    return new HuhiRewardsInternalsUI(web_ui, url.host());
#if !defined(OS_ANDROID)
  } else if (host == kTipHost) {
    return new HuhiTipUI(web_ui, url.host());
#endif  // !defined(OS_ANDROID)
#endif  // BUILDFLAG(HUHI_REWARDS_ENABLED)
#if !defined(OS_ANDROID)
  } else if (host == kWelcomeHost) {
    return new HuhiWelcomeUI(web_ui, url.host());
  } else if (host == chrome::kChromeUISettingsHost) {
    return new HuhiSettingsUI(web_ui, url.host());
  } else if (host == chrome::kChromeUINewTabHost) {
    return new HuhiNewTabUI(web_ui, url.host());
#endif  // !defined(OS_ANDROID)
  }
  return nullptr;
}

// Returns a function that can be used to create the right type of WebUI for a
// tab, based on its URL. Returns NULL if the URL doesn't have WebUI associated
// with it.
WebUIFactoryFunction GetWebUIFactoryFunction(WebUI* web_ui,
                                             const GURL& url) {
  if (url.host_piece() == kAdblockHost ||
      url.host_piece() == kWebcompatReporterHost ||
#if BUILDFLAG(IPFS_ENABLED)
      (url.host_piece() == kIPFSHost &&
          base::FeatureList::IsEnabled(ipfs::features::kIpfsFeature)) ||
#endif  // BUILDFLAG(IPFS_ENABLED)
#if BUILDFLAG(HUHI_WALLET_ENABLED)
      url.host_piece() == kWalletHost ||
#endif
#if BUILDFLAG(HUHI_REWARDS_ENABLED)
      url.host_piece() == kRewardsPageHost ||
      url.host_piece() == kRewardsInternalsHost ||
      url.host_piece() == kTipHost ||
#endif
      url.host_piece() == kWelcomeHost ||
      url.host_piece() == chrome::kChromeUIWelcomeURL ||
      url.host_piece() == chrome::kChromeUINewTabHost ||
      url.host_piece() == chrome::kChromeUISettingsHost) {
    return &NewWebUI<BasicUI>;
  }

  return nullptr;
}

#if defined(OS_ANDROID)
bool ShouldBlockRewardsWebUI(
      content::BrowserContext* browser_context, const GURL& url) {
  if (url.host_piece() != kRewardsPageHost &&
      url.host_piece() != kRewardsInternalsHost) {
    return false;
  }
  if (!base::FeatureList::IsEnabled(features::kHuhiRewards)) {
    return true;
  }
  Profile* profile = Profile::FromBrowserContext(browser_context);
  if (profile &&
      profile->GetPrefs() &&
      profile->GetPrefs()->GetBoolean(kSafetynetCheckFailed)) {
    return true;
  }
  return false;
}
#endif  // defined(OS_ANDROID)

}  // namespace

WebUI::TypeID HuhiWebUIControllerFactory::GetWebUIType(
      content::BrowserContext* browser_context, const GURL& url) {
#if defined(OS_ANDROID)
  if (ShouldBlockRewardsWebUI(browser_context, url)) {
    return WebUI::kNoWebUI;
  }
#endif  // defined(OS_ANDROID)
  WebUIFactoryFunction function = GetWebUIFactoryFunction(NULL, url);
  if (function) {
    return reinterpret_cast<WebUI::TypeID>(function);
  }
  return ChromeWebUIControllerFactory::GetWebUIType(browser_context, url);
}

std::unique_ptr<WebUIController>
HuhiWebUIControllerFactory::CreateWebUIControllerForURL(WebUI* web_ui,
                                                         const GURL& url) {
  WebUIFactoryFunction function = GetWebUIFactoryFunction(web_ui, url);
  if (!function) {
    return ChromeWebUIControllerFactory::CreateWebUIControllerForURL(
        web_ui, url);
  }

  return base::WrapUnique((*function)(web_ui, url));
}


// static
HuhiWebUIControllerFactory* HuhiWebUIControllerFactory::GetInstance() {
  return base::Singleton<HuhiWebUIControllerFactory>::get();
}

HuhiWebUIControllerFactory::HuhiWebUIControllerFactory() {
}

HuhiWebUIControllerFactory::~HuhiWebUIControllerFactory() {
}
