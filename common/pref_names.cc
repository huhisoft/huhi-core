/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/common/pref_names.h"

const char kAdsBlocked[] = "huhi.stats.ads_blocked";
// We no longer update this pref, but we keep it around for now because it's
// added to kAdsBlocked when being displayed.
const char kTrackersBlocked[] = "huhi.stats.trackers_blocked";
const char kJavascriptBlocked[] = "huhi.stats.javascript_blocked";
const char kHttpsUpgrades[] = "huhi.stats.https_upgrades";
const char kFingerprintingBlocked[] = "huhi.stats.fingerprinting_blocked";
const char kLastCheckYMD[] = "huhi.stats.last_check_ymd";
const char kLastCheckWOY[] = "huhi.stats.last_check_woy";
const char kLastCheckMonth[] = "huhi.stats.last_check_month";
const char kFirstCheckMade[] = "huhi.stats.first_check_made";
const char kWeekOfInstallation[] = "huhi.stats.week_of_installation";
const char kAdBlockCheckedDefaultRegion[] =
    "huhi.ad_block.checked_default_region";
const char kAdBlockCustomFilters[] = "huhi.ad_block.custom_filters";
const char kAdBlockRegionalFilters[] = "huhi.ad_block.regional_filters";
const char kWidevineOptedIn[] = "huhi.widevine_opted_in";
const char kWidevineInstalledVersion[] = "huhi.widevine_installed_version";
const char kAskWidevineInstall[] = "huhi.ask_widevine_install";
const char kUseAlternativeSearchEngineProvider[] =
    "huhi.use_alternate_private_search_engine";
const char kAlternativeSearchEngineProviderInTor[] =
    "huhi.alternate_private_search_engine_in_tor";
const char kHuhiThemeType[] = "huhi.theme.type";  // deprecated
const char kUseOverriddenHuhiThemeType[] =
    "huhi.theme.use_overridden_huhi_theme_type";  // deprecated
const char kLocationBarIsWide[] = "huhi.location_bar_is_wide";
const char kReferralDownloadID[] = "huhi.referral.download_id";
const char kReferralTimestamp[] = "huhi.referral.timestamp";
const char kReferralAttemptTimestamp[] =
    "huhi.referral.referral_attempt_timestamp";
const char kReferralAttemptCount[] = "huhi.referral.referral_attempt_count";
const char kReferralHeaders[] = "huhi.referral.headers";
const char kReferralAndroidFirstRunTimestamp[] =
    "huhi.referral_android_first_run_timestamp";
const char kHTTPSEVerywhereControlType[] = "huhi.https_everywhere_default";
const char kNoScriptControlType[] = "huhi.no_script_default";
const char kShieldsAdvancedViewEnabled[] =
    "huhi.shields.advanced_view_enabled";
const char kShieldsStatsBadgeVisible[] =
    "huhi.shields.stats_badge_visible";
const char kAdControlType[] = "huhi.ad_default";
const char kGoogleLoginControlType[] = "huhi.google_login_default";
const char kFBEmbedControlType[] = "huhi.fb_embed_default";
const char kTwitterEmbedControlType[] = "huhi.twitter_embed_default";
const char kLinkedInEmbedControlType[] = "huhi.linkedin_embed_default";
const char kWebTorrentEnabled[] = "huhi.webtorrent_enabled";
const char kHangoutsEnabled[] = "huhi.hangouts_enabled";
const char kIPFSResolveMethod[] = "huhi.ipfs.resolve_method";
const char kIPFSBinaryAvailable[] = "huhi.ipfs.binary_available";
const char kIPFSCompanionEnabled[] = "huhi.ipfs_companion_enabled";
const char kNewTabPageShowClock[] = "huhi.new_tab_page.show_clock";
const char kNewTabPageShowTopSites[] = "huhi.new_tab_page.show_top_sites";
const char kNewTabPageShowStats[] = "huhi.new_tab_page.show_stats";
const char kNewTabPageShowRewards[] = "huhi.new_tab_page.show_rewards";
const char kNewTabPageShowBinance[] = "huhi.new_tab_page.show_binance";
const char kNewTabPageShowGemini[] = "huhi.new_tab_page.show_gemini";
const char kNewTabPageShowTogether[] = "huhi.new_tab_page.show_together";
const char kNewTabPageShowAddCard[] = "huhi.new_tab_page.show_addcard";
const char kHuhiEnabledMediaRouter[] = "huhi.enable_media_router";
const char kHuhiWalletAES256GCMSivNonce[] =
    "huhi.wallet.aes_256_gcm_siv_nonce";
const char kHuhiWalletEncryptedSeed[] = "huhi.wallet.encrypted_seed";
const char kHuhiWalletEnabledDeprecated[] = "huhi.wallet.enabled";
const char kHuhiWalletPrefVersion[] = "huhi.wallet.pref_version";
const char kHuhiWalletWeb3Provider[] = "huhi.wallet.web3_provider";
const char kLoadCryptoWalletsOnStartup[] = "huhi.wallet.load_on_startup";
const char kOptedIntoCryptoWallets[] = "huhi.wallet.opted_in";
const char kBinanceAccessToken[] = "huhi.binance.access_token";
const char kBinanceRefreshToken[] = "huhi.binance.refresh_token";
const char kAlwaysShowBookmarkBarOnNTP[] =
    "huhi.always_show_bookmark_bar_on_ntp";
const char kAutocompleteEnabled[] = "huhi.autocomplete_enabled";
const char kTopSiteSuggestionsEnabled[] = "huhi.top_site_suggestions_enabled";
const char kHuhiSuggestedSiteSuggestionsEnabled[] =
    "huhi.huhi_suggested_site_suggestions_enabled";
const char kHuhiDarkMode[] = "huhi.dark_mode";
const char kOtherBookmarksMigrated[] = "huhi.other_bookmarks_migrated";
const char kHuhiShieldsSettingsVersion[] = "huhi.shields_settings_version";
#if !BUILDFLAG(USE_GCM_FROM_PLATFORM)
const char kHuhiGCMChannelStatus[] = "huhi.gcm.channel_status";
#endif
const char kImportDialogExtensions[] = "import_dialog_extensions";
const char kImportDialogPayments[] = "import_dialog_payments";

#if defined(OS_ANDROID)
const char kDesktopModeEnabled[] = "huhi.desktop_mode_enabled";
const char kPlayYTVideoInBrowserEnabled[] =
    "huhi.play_yt_video_in_browser_enabled";
const char kBackgroundVideoPlaybackEnabled[] =
    "huhi.background_video_playback";
const char kSafetynetCheckFailed[] = "safetynetcheck.failed";
const char kSafetynetStatus[] = "safetynet.status";
#endif
