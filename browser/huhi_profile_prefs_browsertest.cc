/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/common/pref_names.h"
#include "huhi/components/huhi_rewards/common/pref_names.h"
#include "huhi/components/huhi_wallet/buildflags/buildflags.h"
#include "huhi/components/huhi_wayback_machine/buildflags.h"
#include "huhi/components/ipfs/buildflags/buildflags.h"
#include "chrome/browser/net/prediction_options.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/common/pref_names.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "components/embedder_support/pref_names.h"
#include "components/prefs/pref_service.h"
#include "components/safe_browsing/core/common/safe_browsing_prefs.h"
#include "components/spellcheck/browser/pref_names.h"
#include "components/sync/base/pref_names.h"
#include "content/public/test/browser_test.h"

#if BUILDFLAG(IPFS_ENABLED)
#include "huhi/components/ipfs/ipfs_constants.h"
#include "huhi/components/ipfs/pref_names.h"
#endif

#if BUILDFLAG(HUHI_WALLET_ENABLED)
#include "huhi/components/huhi_wallet/huhi_wallet_constants.h"
#include "huhi/components/huhi_wallet/pref_names.h"
#endif

#if BUILDFLAG(ENABLE_HUHI_WAYBACK_MACHINE)
#include "huhi/components/huhi_wayback_machine/pref_names.h"
#endif

using HuhiProfilePrefsBrowserTest = InProcessBrowserTest;

// Check download prompt preference is set to true by default.
IN_PROC_BROWSER_TEST_F(HuhiProfilePrefsBrowserTest, DownloadPromptDefault) {
  EXPECT_TRUE(
      browser()->profile()->GetPrefs()->GetBoolean(prefs::kPromptForDownload));
}

IN_PROC_BROWSER_TEST_F(HuhiProfilePrefsBrowserTest, MiscHuhiPrefs) {
  EXPECT_TRUE(browser()->profile()->GetPrefs()->GetBoolean(
      kHTTPSEVerywhereControlType));
  EXPECT_FALSE(
      browser()->profile()->GetPrefs()->GetBoolean(kNoScriptControlType));
  EXPECT_FALSE(
      browser()->profile()->GetPrefs()->GetBoolean(
        kShieldsAdvancedViewEnabled));
  EXPECT_TRUE(
      browser()->profile()->GetPrefs()->GetBoolean(
        kShieldsStatsBadgeVisible));
  EXPECT_TRUE(
      browser()->profile()->GetPrefs()->GetBoolean(kAdControlType));
  EXPECT_TRUE(
      browser()->profile()->GetPrefs()->GetBoolean(kGoogleLoginControlType));
  EXPECT_TRUE(
      browser()->profile()->GetPrefs()->GetBoolean(kFBEmbedControlType));
  EXPECT_TRUE(
      browser()->profile()->GetPrefs()->GetBoolean(kTwitterEmbedControlType));
  EXPECT_FALSE(
      browser()->profile()->GetPrefs()->GetBoolean(kLinkedInEmbedControlType));
  EXPECT_TRUE(
      browser()->profile()->GetPrefs()->GetBoolean(kWebTorrentEnabled));
#if BUILDFLAG(ENABLE_HUHI_WAYBACK_MACHINE)
  EXPECT_TRUE(browser()->profile()->GetPrefs()->
      GetBoolean(kHuhiWaybackMachineEnabled));
#endif
  EXPECT_TRUE(
      browser()->profile()->GetPrefs()->GetBoolean(kHangoutsEnabled));
  EXPECT_FALSE(
      browser()->profile()->GetPrefs()->GetBoolean(
          huhi_rewards::prefs::kHideButton));
#if BUILDFLAG(IPFS_ENABLED)
  EXPECT_EQ(
      browser()->profile()->GetPrefs()->GetInteger(kIPFSResolveMethod),
      static_cast<int>((ipfs::IPFSResolveMethodTypes::IPFS_ASK)));
  EXPECT_FALSE(
      browser()->profile()->GetPrefs()->GetBoolean(kIPFSBinaryAvailable));
#endif
  EXPECT_FALSE(
      browser()->profile()->GetPrefs()->GetBoolean(kIPFSCompanionEnabled));
#if BUILDFLAG(HUHI_WALLET_ENABLED)
  EXPECT_EQ(
      browser()->profile()->GetPrefs()->GetInteger(kHuhiWalletWeb3Provider),
      static_cast<int>(HuhiWalletWeb3ProviderTypes::ASK));
  EXPECT_FALSE(
      browser()->profile()->GetPrefs()->GetBoolean(
          kLoadCryptoWalletsOnStartup));
  EXPECT_FALSE(
      browser()->profile()->GetPrefs()->GetBoolean(kOptedIntoCryptoWallets));
#endif
  EXPECT_FALSE(
      browser()->profile()->GetPrefs()->GetBoolean(kMRUCyclingEnabled));
#if !BUILDFLAG(USE_GCM_FROM_PLATFORM)
  EXPECT_FALSE(
      browser()->profile()->GetPrefs()->GetBoolean(kHuhiGCMChannelStatus));
#endif
}

IN_PROC_BROWSER_TEST_F(HuhiProfilePrefsBrowserTest,
                       DisableGoogleServicesByDefault) {
  EXPECT_FALSE(browser()->profile()->GetPrefs()->GetBoolean(
      embedder_support::kAlternateErrorPagesEnabled));
  EXPECT_FALSE(browser()->profile()->GetPrefs()->GetBoolean(
      spellcheck::prefs::kSpellCheckUseSpellingService));
  EXPECT_FALSE(browser()->profile()->GetPrefs()->GetBoolean(
      prefs::kSafeBrowsingExtendedReportingOptInAllowed));
  EXPECT_FALSE(browser()->profile()->GetPrefs()->GetBoolean(
      prefs::kSearchSuggestEnabled));
  EXPECT_EQ(browser()->profile()->GetPrefs()->GetInteger(
                prefs::kNetworkPredictionOptions),
            chrome_browser_net::NETWORK_PREDICTION_NEVER);
  EXPECT_FALSE(browser()->profile()->GetPrefs()->GetBoolean(
      prefs::kSigninAllowedOnNextStartup));
  // Verify cloud print is disabled.
  EXPECT_FALSE(browser()->profile()->GetPrefs()->GetBoolean(
      prefs::kCloudPrintProxyEnabled));
  EXPECT_FALSE(browser()->profile()->GetPrefs()->GetBoolean(
      prefs::kCloudPrintSubmitEnabled));
  EXPECT_TRUE(browser()->profile()->GetPrefs()->GetBoolean(
      prefs::kNtpUseMostVisitedTiles));
}
