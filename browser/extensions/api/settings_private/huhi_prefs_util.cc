/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/extensions/api/settings_private/huhi_prefs_util.h"

#include "huhi/common/pref_names.h"
#include "huhi/components/huhi_wayback_machine/buildflags.h"
#include "huhi/components/huhi_rewards/common/pref_names.h"
#include "huhi/components/moonpay/browser/buildflags/buildflags.h"
#include "huhi/components/ntp_background_images/common/pref_names.h"
#include "chrome/browser/extensions/api/settings_private/prefs_util.h"
#include "chrome/common/extensions/api/settings_private.h"
#include "components/browsing_data/core/pref_names.h"
#include "components/gcm_driver/gcm_buildflags.h"
#include "components/omnibox/browser/omnibox_prefs.h"

#if BUILDFLAG(ENABLE_HUHI_WAYBACK_MACHINE)
#include "huhi/components/huhi_wayback_machine/pref_names.h"
#endif


#if BUILDFLAG(MOONPAY_ENABLED)
#include "huhi/components/moonpay/common/pref_names.h"
#endif

namespace extensions {

using ntp_background_images::prefs::kNewTabPageSuperReferralThemesOption;
using
    ntp_background_images::prefs::kNewTabPageShowSponsoredImagesBackgroundImage;
using ntp_background_images::prefs::kNewTabPageShowBackgroundImage;

namespace settings_api = api::settings_private;

const PrefsUtil::TypedPrefMap& HuhiPrefsUtil::GetWhitelistedKeys() {
  // Static cache, similar to parent class
  static PrefsUtil::TypedPrefMap* s_huhi_whitelist = nullptr;
  if (s_huhi_whitelist)
    return *s_huhi_whitelist;
  s_huhi_whitelist = new PrefsUtil::TypedPrefMap();
  // Start with parent class whitelist
  const auto chromium_prefs = PrefsUtil::GetWhitelistedKeys();
  s_huhi_whitelist->insert(chromium_prefs.begin(), chromium_prefs.end());
  // Add Huhi values to the whitelist
  // import data
  (*s_huhi_whitelist)[kImportDialogExtensions] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_huhi_whitelist)[kImportDialogPayments] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
  // Default Huhi shields
  (*s_huhi_whitelist)[kShieldsAdvancedViewEnabled] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_huhi_whitelist)[kShieldsStatsBadgeVisible] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_huhi_whitelist)[kAdControlType] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_huhi_whitelist)[kHTTPSEVerywhereControlType] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_huhi_whitelist)[kNoScriptControlType] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_huhi_whitelist)[kGoogleLoginControlType] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_huhi_whitelist)[kFBEmbedControlType] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_huhi_whitelist)[kTwitterEmbedControlType] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_huhi_whitelist)[kLinkedInEmbedControlType] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;

  // appearance prefs
  (*s_huhi_whitelist)[kLocationBarIsWide] =
    settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_huhi_whitelist)[kAutocompleteEnabled] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_huhi_whitelist)[kTopSiteSuggestionsEnabled] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_huhi_whitelist)[kHuhiSuggestedSiteSuggestionsEnabled] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_huhi_whitelist)[huhi_rewards::prefs::kHideButton] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_huhi_whitelist)[kAskWidevineInstall] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_huhi_whitelist)[kNewTabPageSuperReferralThemesOption] =
      settings_api::PrefType::PREF_TYPE_NUMBER;
  // new tab prefs
  (*s_huhi_whitelist)[kNewTabPageShowSponsoredImagesBackgroundImage] =
        settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_huhi_whitelist)[kNewTabPageShowBackgroundImage] =
        settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_huhi_whitelist)[kNewTabPageShowClock] =
        settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_huhi_whitelist)[kNewTabPageShowTopSites] =
        settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_huhi_whitelist)[kNewTabPageShowStats] =
        settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_huhi_whitelist)[kNewTabPageShowRewards] =
        settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_huhi_whitelist)[kNewTabPageShowBinance] =
        settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_huhi_whitelist)[kNewTabPageShowTogether] =
        settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_huhi_whitelist)[kNewTabPageShowAddCard] =
        settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_huhi_whitelist)[kNewTabPageShowGemini] =
        settings_api::PrefType::PREF_TYPE_BOOLEAN;
#if BUILDFLAG(MOONPAY_ENABLED)
  (*s_huhi_whitelist)[kMoonpayNewTabPageShowBitcoinDotCom] =
        settings_api::PrefType::PREF_TYPE_BOOLEAN;
#endif
  // Clear browsing data on exit prefs.
  (*s_huhi_whitelist)[browsing_data::prefs::kDeleteBrowsingHistoryOnExit] =
    settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_huhi_whitelist)[browsing_data::prefs::kDeleteDownloadHistoryOnExit] =
    settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_huhi_whitelist)[browsing_data::prefs::kDeleteCacheOnExit] =
    settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_huhi_whitelist)[browsing_data::prefs::kDeleteCookiesOnExit] =
    settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_huhi_whitelist)[browsing_data::prefs::kDeletePasswordsOnExit] =
    settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_huhi_whitelist)[browsing_data::prefs::kDeleteFormDataOnExit] =
    settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_huhi_whitelist)[browsing_data::prefs::kDeleteSiteSettingsOnExit] =
    settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_huhi_whitelist)[browsing_data::prefs::kDeleteHostedAppsDataOnExit] =
    settings_api::PrefType::PREF_TYPE_BOOLEAN;
  (*s_huhi_whitelist)[kAlwaysShowBookmarkBarOnNTP] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
  // WebTorrent pref
  (*s_huhi_whitelist)[kWebTorrentEnabled] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
#if BUILDFLAG(ENABLE_HUHI_WAYBACK_MACHINE)
  (*s_huhi_whitelist)[kHuhiWaybackMachineEnabled] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
#endif
  // Hangouts pref
  (*s_huhi_whitelist)[kHangoutsEnabled] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
  // IPFS Companion pref
  (*s_huhi_whitelist)[kIPFSCompanionEnabled] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
  // Huhi Wallet pref
  (*s_huhi_whitelist)[kHuhiWalletWeb3Provider] =
      settings_api::PrefType::PREF_TYPE_NUMBER;
  (*s_huhi_whitelist)[kLoadCryptoWalletsOnStartup] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
  // IPFS pref
  (*s_huhi_whitelist)[kIPFSResolveMethod] =
      settings_api::PrefType::PREF_TYPE_NUMBER;
  // Media Router Pref
  (*s_huhi_whitelist)[kHuhiEnabledMediaRouter] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;

#if !BUILDFLAG(USE_GCM_FROM_PLATFORM)
  // Push Messaging Pref
  (*s_huhi_whitelist)[kHuhiGCMChannelStatus] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;
#endif
  // Omnibox pref
  (*s_huhi_whitelist)[omnibox::kPreventUrlElisionsInOmnibox] =
      settings_api::PrefType::PREF_TYPE_BOOLEAN;

  return *s_huhi_whitelist;
}

}  // namespace extensions
