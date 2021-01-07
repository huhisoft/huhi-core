/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/browser/ui/webui/settings/settings_localized_strings_provider.h"

#include "base/stl_util.h"
#include "base/strings/string16.h"
#include "base/strings/utf_string_conversions.h"
#include "huhi/browser/ui/webui/settings/huhi_privacy_handler.h"
#include "huhi/browser/version_info.h"
#include "huhi/components/moonpay/browser/buildflags/buildflags.h"
#include "huhi/components/crypto_dot_com/browser/buildflags/buildflags.h"
#include "chrome/browser/ui/webui/webui_util.h"
#include "chrome/common/pref_names.h"
#include "components/grit/huhi_components_strings.h"
#include "components/prefs/pref_service.h"

namespace settings {
void HuhiAddLocalizedStrings(content::WebUIDataSource*, Profile*);
}  // namespace settings

// Override some chromium strings
#include "huhi/grit/huhi_generated_resources.h"
#include "chrome/grit/chromium_strings.h"
#include "chrome/grit/generated_resources.h"
#include "extensions/common/extension_urls.h"

#undef IDS_SETTINGS_EDIT_PERSON
#define IDS_SETTINGS_EDIT_PERSON IDS_SETTINGS_HUHI_EDIT_PROFILE
#undef IDS_SETTINGS_PROFILE_NAME_AND_PICTURE
#define IDS_SETTINGS_PROFILE_NAME_AND_PICTURE IDS_SETTINGS_HUHI_EDIT_PROFILE
#undef IDS_SETTINGS_SAFEBROWSING_STANDARD_BULLET_TWO
#define IDS_SETTINGS_SAFEBROWSING_STANDARD_BULLET_TWO \
  IDS_SETTINGS_HUHI_SAFEBROWSING_STANDARD_BULLET_TWO
#undef IDS_SETTINGS_SAFEBROWSING_NONE_DESC
#define IDS_SETTINGS_SAFEBROWSING_NONE_DESC \
  IDS_SETTINGS_HUHI_SAFEBROWSING_NONE_DESC

#define GetVersionNumber GetHuhiVersionNumberForDisplay

#include "../../../../../../../chrome/browser/ui/webui/settings/settings_localized_strings_provider.cc"
#undef GetVersionNumber

#include "huhi/browser/ui/webui/huhi_settings_ui.h"
namespace settings {

const char kWebRTCLearnMoreURL[] =
    "https://support.hnq.vn/hc/en-us/articles/360017989132-How-do-I-change-my-Privacy-Settings-#webrtc";
const char kHuhiBuildInstructionsUrl[] =
    "https://github.com/huhisoft/huhi-browser/wiki";
const char kHuhiLicenseUrl[] = "https://mozilla.org/MPL/2.0/";
const char kHuhiReleaseTagPrefix[] =
    "https://github.com/huhisoft/huhi-browser/releases/tag/v";
const char kGoogleLoginLearnMoreURL[] =
    "https://github.com/huhisoft/huhi-browser/wiki/"
    "Allow-Google-login---Third-Parties-and-Extensions";

void HuhiAddCommonStrings(content::WebUIDataSource* html_source,
                           Profile* profile) {
  webui::LocalizedString localized_strings[] = {
    {"importExtensions",
      IDS_SETTINGS_IMPORT_EXTENSIONS_CHECKBOX},
    {"importPayments",
      IDS_SETTINGS_IMPORT_PAYMENTS_CHECKBOX},
    {"siteSettingsAutoplay",
      IDS_SETTINGS_SITE_SETTINGS_AUTOPLAY},
    {"siteSettingsCategoryAutoplay",
      IDS_SETTINGS_SITE_SETTINGS_AUTOPLAY},
    {"huhiGetStartedTitle",
      IDS_SETTINGS_HUHI_GET_STARTED_TITLE},
    {"huhiAdditionalSettingsTitle",
      IDS_SETTINGS_HUHI_ADDITIONAL_SETTINGS},
    {"appearanceSettingsAskWidevineInstallDesc",
      IDS_SETTINGS_ASK_WIDEVINE_INSTALL_DESC},
    {"appearanceSettingsHuhiTheme",
      IDS_SETTINGS_APPEARANCE_SETTINGS_HUHI_THEMES},
    {"appearanceSettingsLocationBarIsWide",
      IDS_SETTINGS_APPEARANCE_SETTINGS_LOCATION_BAR_IS_WIDE},
    {"appearanceSettingsHideHuhiRewardsButtonLabel",
      IDS_SETTINGS_HIDE_HUHI_REWARDS_BUTTON_LABEL},
    {"appearanceSettingsAlwaysShowBookmarkBarOnNTP",
      IDS_SETTINGS_ALWAYS_SHOW_BOOKMARK_BAR_ON_NTP},
    {"appearanceSettingsShowAutocompleteInAddressBar",
      IDS_SETTINGS_APPEARANCE_SETTINGS_SHOW_AUTOCOMPLETE_IN_ADDRESS_BAR},
    {"appearanceSettingsUseTopSiteSuggestions",
      IDS_SETTINGS_APPEARANCE_SETTINGS_USE_AUTOCOMPLETE_TOP_SITES},
    {"appearanceSettingsUseHuhiSuggestedSiteSuggestions",
      IDS_SETTINGS_APPEARANCE_SETTINGS_USE_AUTOCOMPLETE_HUHI_SUGGESTED_SITES},
    {"appearanceSettingsGetMoreThemes",
      IDS_SETTINGS_APPEARANCE_SETTINGS_GET_MORE_THEMES},
    {"appearanceHuhiDefaultImagesOptionLabel",
      IDS_SETTINGS_APPEARANCE_SETTINGS_HUHI_DEFAULT_IMAGES_OPTION_LABEL},
    {"mruCyclingSettingLabel",
      IDS_SETTINGS_HUHI_MRU_CYCLING_LABEL},
    {"huhiShieldsTitle",
      IDS_SETTINGS_HUHI_SHIELDS_TITLE},
    {"huhiShieldsDefaultsSectionTitle",
      IDS_SETTINGS_HUHI_SHIELDS_DEFAULTS_TITLE},
    {"huhiShieldsDefaultsSectionDescription1",
      IDS_SETTINGS_HUHI_SHIELDS_DEFAULTS_DESCRIPTION_1},
    {"huhiShieldsDefaultsSectionDescription2",
      IDS_SETTINGS_HUHI_SHIELDS_DEFAULTS_DESCRIPTION_2},
    {"huhiShieldsDefaultsSectionDescription3",
      IDS_SETTINGS_HUHI_SHIELDS_DEFAULTS_DESCRIPTION_3},
    {"socialBlocking",
      IDS_SETTINGS_SOCIAL_BLOCKING_DEFAULTS_TITLE},
    {"defaultView",
      IDS_SETTINGS_HUHI_SHIELDS_DEFAULTS_DEFAULT_VIEW_LABEL},
    {"simpleView",
      IDS_SETTINGS_HUHI_SHIELDS_DEFAULTS_SIMPLE_VIEW_LABEL},
    {"advancedView",
      IDS_SETTINGS_HUHI_SHIELDS_DEFAULTS_ADVANCED_VIEW_LABEL},
    {"adControlLabel",
      IDS_SETTINGS_HUHI_SHIELDS_AD_CONTROL_LABEL},
    {"cookieControlLabel",
      IDS_SETTINGS_HUHI_SHIELDS_COOKIE_CONTROL_LABEL},
    {"fingerprintingControlLabel",
      IDS_SETTINGS_HUHI_SHIELDS_FINGERPRINTING_CONTROL_LABEL},
    {"httpsEverywhereControlLabel",
      IDS_SETTINGS_HUHI_SHIELDS_HTTPS_EVERYWHERE_CONTROL_LABEL},
    {"noScriptControlLabel",
      IDS_SETTINGS_HUHI_SHIELDS_NO_SCRIPT_CONTROL_LABEL},
    {"shieldsLookFeelTitle",
      IDS_SETTINGS_HUHI_SHIELDS_LOOK_AND_FEEL_TITLE},
    {"showStatsBlockedBadgeLabel",
      IDS_SETTINGS_HUHI_SHIELDS_SHOW_STATS_BLOCKED_BADGE_LABEL},
    {"googleLoginControlLabel",
      IDS_SETTINGS_HUHI_SHIELDS_GOOGLE_LOGIN_LABEL},
    {"fbEmbedControlLabel",
      IDS_SETTINGS_HUHI_SHIELDS_FACEBOOK_EMBEDDED_POSTS_LABEL},
    {"twitterEmbedControlLabel",
      IDS_SETTINGS_HUHI_SHIELDS_TWITTER_EMBEDDED_TWEETS_LABEL},
    {"linkedInEmbedControlLabel",
      IDS_SETTINGS_HUHI_SHIELDS_LINKEDIN_EMBEDDED_POSTS_LABEL},
    {"blockAdsTrackersAggressive",
      IDS_SETTINGS_BLOCK_ADS_TRACKERS_AGGRESSIVE},
    {"blockAdsTrackersStandard",
      IDS_SETTINGS_BLOCK_ADS_TRACKERS_STANDARD},
    {"allowAdsTrackers",
      IDS_SETTINGS_ALLOW_ADS_TRACKERS},
    {"block3rdPartyCookies",
      IDS_SETTINGS_BLOCK_3RD_PARTY_COOKIES},
    {"allowAllCookies",
      IDS_SETTINGS_ALLOW_ALL_COOKIES},
    {"blockAllCookies",
      IDS_SETTINGS_BLOCK_ALL_COOKIES},
    {"standardFingerprinting",
      IDS_SETTINGS_STANDARD_FINGERPRINTING},
    {"allowAllFingerprinting",
      IDS_SETTINGS_ALLOW_ALL_FINGERPRINTING},
    {"strictFingerprinting",
      IDS_SETTINGS_STRICT_FINGERPRINTING},
    {"webRTCPolicyLabel",
      IDS_SETTINGS_WEBRTC_POLICY_LABEL},
    {"webRTCPolicySubLabel",
      IDS_SETTINGS_WEBRTC_POLICY_SUB_LABEL},
    {"webRTCDefault",
      IDS_SETTINGS_WEBRTC_POLICY_DEFAULT},
    {"pushMessagingLabel",
      IDS_SETTINGS_PUSH_MESSAGING},
    {"defaultPublicAndPrivateInterfaces",
      IDS_SETTINGS_WEBRTC_POLICY_DEFAULT_PUBLIC_AND_PRIVATE_INTERFACES},
    {"defaultPublicInterfaceOnly",
      IDS_SETTINGS_WEBRTC_POLICY_DEFAULT_PUBLIC_INTERFACE_ONLY},
    {"disableNonProxiedUdp",
      IDS_SETTINGS_WEBRTC_POLICY_DISABLE_NON_PROXIED_UDP},
    {"huhiSync",
      IDS_SETTINGS_HUHI_SYNC_TITLE},
    {"huhiSyncSetupActionLabel",
      IDS_SETTINGS_HUHI_SYNC_SETUP_ACTION_LABEL},
    {"huhiSyncSetupTitle",
      IDS_SETTINGS_HUHI_SYNC_SETUP_TITLE},
    {"huhiSyncSetupSubtitle",
      IDS_SETTINGS_HUHI_SYNC_SETUP_SUBTITLE},
    {"huhiSyncManageActionLabel",
      IDS_SETTINGS_HUHI_SYNC_MANAGE_ACTION_LABEL},
    {"huhiSyncWordCount",
      IDS_SETTINGS_HUHI_SYNC_WORD_COUNT},
    {"huhiSyncCopied",
      IDS_SETTINGS_HUHI_SYNC_COPIED_TEXT},
    {"huhiSyncQRCodeAlt",
      IDS_SETTINGS_HUHI_SYNC_QR_IMAGE_ALT},
    {"huhiSyncQRError",
      IDS_SETTINGS_HUHI_SYNC_QR_ERROR},
    {"huhiSyncManagerTitle",
      IDS_SETTINGS_HUHI_SYNC_MANAGER_TITLE},
    {"huhiSyncSettingsTitle",
      IDS_SETTINGS_HUHI_SYNC_SETTINGS_TITLE},
    {"huhiSyncSettingsSubtitle",
      IDS_SETTINGS_HUHI_SYNC_SETTINGS_SUBTITLE},
    {"huhiSyncDeviceListTitle",
      IDS_SETTINGS_HUHI_SYNC_DEVICE_LIST_TITLE},
    {"huhiSyncDeviceListSubtitle",
      IDS_SETTINGS_HUHI_SYNC_DEVICE_LIST_SUBTITLE},
    {"huhiSyncDeviceListNameColumn",
      IDS_SETTINGS_HUHI_SYNC_DEVICE_LIST_NAME_COLUMN},
    {"huhiSyncDeviceListNameThisDevice",
      IDS_SETTINGS_HUHI_SYNC_DEVICE_LIST_NAME_THIS_DEVICE},
    {"huhiSyncDeviceListLastActiveColumn",
      IDS_SETTINGS_HUHI_SYNC_DEVICE_LIST_LAST_ACTIVE_COLUMN},
    {"huhiSyncDeviceListRemoveColumn",
      IDS_SETTINGS_HUHI_SYNC_DEVICE_LIST_REMOVE_COLUMN},
    {"huhiSyncSetupTitle",
      IDS_HUHI_SYNC_SETUP_TITLE},
    {"huhiSyncSetupDesc",
      IDS_HUHI_SYNC_SETUP_DESCRIPTION},
    {"huhiSyncStartNewChain",
      IDS_HUHI_SYNC_START_NEW_CHAIN_BUTTON},
    {"huhiSyncEnterCode",
      IDS_HUHI_SYNC_ENTER_CODE_BUTTON},
    {"huhiSyncChooseDeviceMobileTitle",
      IDS_HUHI_SYNC_CHOOSE_DEVICE_MOBILE_TITLE},
    {"huhiSyncChooseDeviceComputerTitle",
      IDS_HUHI_SYNC_CHOOSE_DEVICE_COMPUTER_TITLE},
    {"huhiSyncScanCodeTitle",
      IDS_HUHI_SYNC_SCAN_CODE_TITLE},
    {"huhiSyncScanCodeDesc1",
      IDS_HUHI_SYNC_SCAN_CODE_DESCRIPTION_PARTIAL_1},
    {"huhiSyncScanCodeDesc2",
      IDS_HUHI_SYNC_SCAN_CODE_DESCRIPTION_PARTIAL_2},
    {"huhiSyncScanCodeDesc3",
      IDS_HUHI_SYNC_SCAN_CODE_DESCRIPTION_PARTIAL_3},
    {"huhiSyncViewCodeTitle",
      IDS_HUHI_SYNC_VIEW_CODE_TITLE},
    {"huhiSyncViewCodeDesc1",
      IDS_HUHI_SYNC_VIEW_CODE_DESCRIPTION_PARTIAL_1},
    {"huhiSyncViewCodeDesc2",
      IDS_HUHI_SYNC_VIEW_CODE_DESCRIPTION_PARTIAL_2},
    {"huhiSyncViewCodeDesc3",
      IDS_HUHI_SYNC_VIEW_CODE_DESCRIPTION_PARTIAL_3},
    {"huhiSyncCodeWarning",
      IDS_HUHI_SYNC_CODE_WARNING},
    {"huhiSyncViewCodeQRCodeButton",
      IDS_HUHI_SYNC_VIEW_CODE_QR_CODE_BUTTON},
    {"huhiSyncEnterCodeTitle",
      IDS_HUHI_SYNC_ENTER_CODE_TITLE},
    {"huhiSyncEnterCodeDesc",
      IDS_HUHI_SYNC_ENTER_CODE_DESCRIPTION},
    {"huhiSyncViewCodeButton",
      IDS_HUHI_SYNC_VIEW_CODE_BUTTON},
    {"huhiSyncAddDevice",
      IDS_HUHI_SYNC_ADD_DEVICE_BUTTON},
    {"huhiSyncChooseDeviceTitle",
      IDS_HUHI_SYNC_CHOOSE_DEVICE_TITLE},
    {"huhiSyncChooseDeviceDesc",
      IDS_HUHI_SYNC_CHOOSE_DEVICE_DESCRIPTION},
    {"huhiSyncInvalidSyncCodeTitle",
      IDS_HUHI_SYNC_INVALID_SYNC_CODE_TITLE},
    {"huhiSyncResetButton",
      IDS_HUHI_SYNC_RESET_BUTTON},
    {"huhiSyncResetConfirmation",
      IDS_HUHI_SYNC_RESET_CONFIRMATION},
    {"huhiSyncDeleteDeviceConfirmation",
      IDS_HUHI_SYNC_DELETE_DEVICE_CONFIRMATION},
    {"huhiHelpTips",
      IDS_SETTINGS_HELP_TIPS},
    {"huhiHelpTipsWaybackMachineLabel",
      IDS_SETTINGS_HELP_TIPS_SHOW_HUHI_WAYBACK_MACHINE_PROMPT},
    // New Tab Page
    { "huhiNewTab", IDS_SETTINGS_NEW_TAB },
    { "huhiNewTabBackgroundImages", IDS_SETTINGS_NEW_TAB_BACKGROUND_IMAGES },
    { "huhiNewTabSponsoredImages", IDS_SETTINGS_NEW_TAB_SPONSORED_IMAGES },
    { "huhiNewTabStats", IDS_SETTINGS_NEW_TAB_STATS },
    { "huhiNewTabHuhiRewards", IDS_SETTINGS_NEW_TAB_HUHI_REWARDS },
    { "huhiNewTabBinance", IDS_SETTINGS_NEW_TAB_BINANCE },
    { "huhiNewTabGemini", IDS_SETTINGS_NEW_TAB_GEMINI },
#if BUILDFLAG(MOONPAY_ENABLED)
    { "huhiNewTabBitcoinDotCom", IDS_SETTINGS_NEW_TAB_BITCOIN_DOT_COM },
#endif
#if BUILDFLAG(CRYPTO_DOT_COM_ENABLED)
    { "huhiNewTabCryptoDotCom", IDS_SETTINGS_NEW_TAB_CRYPTO_DOT_COM },
#endif
    { "huhiNewTabTogether", IDS_SETTINGS_NEW_TAB_TOGETHER },
    { "huhiNewTabTopSites", IDS_SETTINGS_NEW_TAB_TOP_SITES },
    { "huhiNewTabClock", IDS_SETTINGS_NEW_TAB_CLOCK },
    { "huhiNewTabNewTabPageShows", IDS_SETTINGS_NEW_TAB_NEW_TAB_PAGE_SHOWS },
    // Misc (TODO: Organize this)
    {"onExitPageTitle",
      IDS_SETTINGS_HUHI_ON_EXIT},
    {"huhiDefaultExtensions",
      IDS_SETTINGS_HUHI_DEFAULT_EXTENSIONS_TITLE},
    {"webTorrentEnabledDesc",
      IDS_SETTINGS_WEBTORRENT_ENABLED_DESC},
    {"huhiWeb3ProviderDesc",
      IDS_SETTINGS_HUHI_WEB3_PROVIDER_DESC},
    {"loadCryptoWalletsOnStartupDesc",
      IDS_SETTINGS_LOAD_CRYPTO_WALLETS_ON_STARTUP},
    {"googleLoginForExtensionsDesc",
      IDS_SETTINGS_GOOGLE_LOGIN_FOR_EXTENSIONS},
    {"hangoutsEnabledDesc",
      IDS_SETTINGS_HANGOUTS_ENABLED_DESC},
    {"resolveIPFSURLDesc",
      IDS_SETTINGS_RESOLVE_IPFS_URLS_DESC},
    {"ipfsAutoFallbackToGatewayLabel",
      IDS_SETTINGS_IPFS_AUTO_FALLBACK_TO_GATEWAY_LABEL},
    {"ipfsAutoFallbackToGatewayDesc",
      IDS_SETTINGS_IPFS_AUTO_FALLBACK_TO_GATEWAY_DESC},
    {"ipfsCompanionEnabledDesc",
      IDS_SETTINGS_IPFS_COMPANION_ENABLED_DESC},
    {"mediaRouterEnabledDesc",
      IDS_SETTINGS_MEDIA_ROUTER_ENABLED_DESC},
    {"torEnabledLabel",
      IDS_SETTINGS_ENABLE_TOR_TITLE},
    {"torEnabledDesc",
      IDS_SETTINGS_ENABLE_TOR_DESC},
    {"autoOnionLocationLabel",
      IDS_SETTINGS_AUTO_ONION_LOCATION_TITLE},
    {"autoOnionLocationDesc",
      IDS_SETTINGS_AUTO_ONION_LOCATION_DESC},
    {"restartNotice",
      IDS_SETTINGS_RESTART_NOTICE},
    {"relaunchButtonLabel",
      IDS_SETTINGS_RELAUNCH_BUTTON_LABEL},
    {"manageExtensionsLabel",
      IDS_SETTINGS_MANAGE_EXTENSIONS_LABEL},
    {"keyboardShortcuts",
      IDS_EXTENSIONS_SIDEBAR_KEYBOARD_SHORTCUTS},
    {"getMoreExtensionsLabel",
      IDS_HUHI_SETTINGS_GET_MORE_EXTENSIONS_LABEL},
    {"getMoreExtensionsSubLabel",
      IDS_EXTENSIONS_SIDEBAR_OPEN_CHROME_WEB_STORE},
    {"p3aEnableTitle",
      IDS_HUHI_P3A_ENABLE_SETTING},
    {"p3aEnabledDesc",
      IDS_HUHI_P3A_ENABLE_SETTING_SUBITEM},
    {"siteSettings",
      IDS_SETTINGS_SITE_AND_SHIELDS_SETTINGS},
    {"resetRewardsData",
      IDS_SETTINGS_RESET_REWARDS_DATA},
    {"showFullUrls",
      IDS_CONTEXT_MENU_SHOW_FULL_URLS},
  };
  AddLocalizedStringsBulk(html_source, localized_strings);
  html_source->AddString("webRTCLearnMoreURL",
                         base::ASCIIToUTF16(kWebRTCLearnMoreURL));
  html_source->AddString("googleLoginLearnMoreURL",
                        base::ASCIIToUTF16(kGoogleLoginLearnMoreURL));
  html_source->AddString(
      "getMoreExtensionsUrl",
      base::ASCIIToUTF16(
          google_util::AppendGoogleLocaleParam(
              GURL(extension_urls::GetWebstoreExtensionsCategoryURL()),
              g_browser_process->GetApplicationLocale())
              .spec()));
}

void HuhiAddResources(content::WebUIDataSource* html_source,
                       Profile* profile) {
  HuhiSettingsUI::AddResources(html_source, profile);
}

void HuhiAddAboutStrings(content::WebUIDataSource* html_source,
                          Profile* profile) {
  base::string16 license = l10n_util::GetStringFUTF16(
      IDS_HUHI_VERSION_UI_LICENSE, base::ASCIIToUTF16(kHuhiLicenseUrl),
      base::ASCIIToUTF16(chrome::kChromeUICreditsURL),
      base::ASCIIToUTF16(kHuhiBuildInstructionsUrl),
      base::ASCIIToUTF16(kHuhiReleaseTagPrefix) +
          base::UTF8ToUTF16(
              version_info::GetHuhiVersionWithoutChromiumMajorVersion()));
  html_source->AddString("aboutProductLicense", license);
}

void HuhiAddSocialBlockingLoadTimeData(content::WebUIDataSource* html_source,
                                        Profile* profile) {
    html_source->AddBoolean("signInAllowedOnNextStartupInitialValue",
        profile->GetPrefs()->GetBoolean(prefs::kSigninAllowedOnNextStartup));
}

void HuhiAddLocalizedStrings(content::WebUIDataSource* html_source,
                              Profile* profile) {
  HuhiAddCommonStrings(html_source, profile);
  HuhiAddResources(html_source, profile);
  HuhiAddAboutStrings(html_source, profile);
  HuhiPrivacyHandler::AddLoadTimeData(html_source, profile);
  HuhiAddSocialBlockingLoadTimeData(html_source, profile);
}

}  // namespace settings
