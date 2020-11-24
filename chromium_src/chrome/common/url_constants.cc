/* Copyright 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/common/url_constants.h"

#include "build/branding_buildflags.h"
#include "chrome/common/webui_url_constants.h"

namespace chrome {

const char kAccessibilityLabelsLearnMoreURL[] =
    "https://support.huhisoft.com/";

const char kAutomaticSettingsResetLearnMoreURL[] =
    "https://support.huhisoft.com/hc/en-us/articles/"
    "360017903152-How-do-I-reset-Huhi-settings-to-default-";

const char kAdvancedProtectionDownloadLearnMoreURL[] =
    "https://support.huhisoft.com";

const char kBluetoothAdapterOffHelpURL[] =
    "https://support.huhisoft.com/";

const char kCastCloudServicesHelpURL[] =
    "https://support.huhisoft.com/";

const char kCastNoDestinationFoundURL[] =
    "https://support.huhisoft.com/";

const char kChooserBluetoothOverviewURL[] =
    "https://support.huhisoft.com/";

const char kChooserUsbOverviewURL[] =
    "https://support.huhisoft.com/";

const char kChromeBetaForumURL[] =
    "https://community.huhisoft.com/c/beta-builds";

const char kChromeFixUpdateProblems[] =
    "https://support.huhisoft.com/";

const char kChromeReleaseNotesURL[] =
    "https://huhisoft.com/latest/";

const char kChromeHelpViaKeyboardURL[] =
#if defined(OS_CHROMEOS)
#if defined(GOOGLE_CHROME_BUILD)
    "https://support.huhisoft.com/";
#else
    "https://support.huhisoft.com/";
#endif  // defined(GOOGLE_CHROME_BUILD)
#else
    "https://support.huhisoft.com/";
#endif  // defined(OS_CHROMEOS)

const char kChromeHelpViaMenuURL[] =
#if defined(OS_CHROMEOS)
#if defined(GOOGLE_CHROME_BUILD)
    "https://support.huhisoft.com/";
#else
    "https://support.huhisoft.com/";
#endif  // defined(GOOGLE_CHROME_BUILD)
#else
    "https://support.huhisoft.com/";
#endif  // defined(OS_CHROMEOS)

const char kChromeHelpViaWebUIURL[] =
    "https://support.huhisoft.com/";
#if defined(OS_CHROMEOS)
const char kChromeOsHelpViaWebUIURL[] =
#if BUILDFLAG(GOOGLE_CHROME_BRANDING)
    "https://support.huhisoft.com/";
#else
    "https://support.huhisoft.com/";
#endif  // BUILDFLAG(GOOGLE_CHROME_BRANDING)
#endif  // defined(OS_CHROMEOS)

const char kChromeNativeScheme[] = "chrome-native";

const char kChromeSearchLocalNtpHost[] = "local-ntp";
const char kChromeSearchLocalNtpUrl[] =
    "chrome-search://local-ntp/local-ntp.html";

const char kChromeSearchMostVisitedHost[] = "most-visited";
const char kChromeSearchMostVisitedUrl[] = "chrome-search://most-visited/";

const char kChromeSearchLocalNtpBackgroundUrl[] =
    "chrome-search://local-ntp/background.jpg";
const char kChromeSearchLocalNtpBackgroundFilename[] = "background.jpg";

const char kChromeSearchRemoteNtpHost[] = "remote-ntp";

const char kChromeSearchScheme[] = "chrome-search";

const char kChromeUIUntrustedNewTabPageUrl[] =
    "chrome-untrusted://new-tab-page/";

const char kChromiumProjectURL[] = "https://github.com/huhisoft/huhi-browser/";

const char kCloudPrintLearnMoreURL[] =
    "https://support.huhisoft.com/hc/en-us/articles/"
    "360017880792-How-do-I-print-from-Huhi-";

const char kCloudPrintCertificateErrorLearnMoreURL[] =
    "https://support.huhisoft.com/hc/en-us/articles/"
    "360017880792-How-do-I-print-from-Huhi-";

const char kContentSettingsExceptionsLearnMoreURL[] =
    "https://support.huhisoft.com/hc/en-us/articles/"
    "360018205431-How-do-I-change-site-permissions-";

const char kCookiesSettingsHelpCenterURL[] =
    "https://support.huhisoft.com/hc/en-us/articles/"
    "360018205431-How-do-I-change-site-permissions-";

const char kCrashReasonURL[] =
    "https://support.huhisoft.com/hc/en-us/articles/"
    "360018192251-How-do-I-fix-page-crashes-and-other-page-loading-errors-";

const char kCrashReasonFeedbackDisplayedURL[] =
    "https://support.huhisoft.com/hc/en-us/articles/"
    "360018192251-How-do-I-fix-page-crashes-and-other-page-loading-errors-";

const char kDoNotTrackLearnMoreURL[] =
    "https://support.huhisoft.com/hc/en-us/articles/"
    "360017905612-How-do-I-turn-Do-Not-Track-on-or-off-";

const char kDownloadInterruptedLearnMoreURL[] =
    "https://support.huhisoft.com/hc/en-us/articles/"
    "360018192491-How-do-I-fix-file-download-errors-";

const char kDownloadScanningLearnMoreURL[] =
    "https://support.huhisoft.com/hc/en-us/articles/"
    "360018192491-How-do-I-fix-file-download-errors-";

const char kExtensionControlledSettingLearnMoreURL[] =
    "https://support.huhisoft.com/hc/en-us/articles/"
    "360018185651-How-do-I-stop-extensions-from-changing-my-settings-";

const char kExtensionInvalidRequestURL[] = "chrome-extension://invalid/";

const char kFlashDeprecationLearnMoreURL[] =
    "https://blog.chromium.org/2017/07/so-long-and-thanks-for-all-flash.html";

const char kGoogleAccountActivityControlsURL[] =
    "https://support.huhisoft.com/";

const char kGoogleAccountURL[] = "https://support.huhisoft.com/";

const char kGoogleAccountChooserURL[] = "https://support.huhisoft.com/";

const char kGooglePasswordManagerURL[] = "https://support.huhisoft.com";

const char kLearnMoreReportingURL[] =
    "https://support.huhisoft.com/hc/en-us/articles/"
    "360017905872-How-do-I-enable-or-disable-automatic-crash-reporting-";

const char kLegacySupervisedUserManagementDisplayURL[] =
    "https://support.huhisoft.com/";

const char kManagedUiLearnMoreUrl[] = "https://support.huhisoft.com/";

const char kMixedContentDownloadBlockingLearnMoreUrl[] =
    "https://support.huhisoft.com/";

const char kMyActivityUrlInClearBrowsingData[] =
    "https://support.huhisoft.com/";

const char kOmniboxLearnMoreURL[] =
    "https://support.huhisoft.com/hc/en-us/articles/"
    "360017479752-How-do-I-set-my-default-search-engine-";

const char kPageInfoHelpCenterURL[] =
    "https://support.huhisoft.com/hc/en-us/articles/"
    "360018185871-How-do-I-check-if-a-site-s-connection-is-secure-";

const char kPasswordCheckLearnMoreURL[] = "https://support.huhisoft.com/";

const char kPasswordManagerLearnMoreURL[] =
    "https://support.huhisoft.com/hc/en-us/articles/"
    "360018185951-How-do-I-use-the-built-in-password-manager-";

const char kPaymentMethodsURL[] = "https://support.huhisoft.com";

const char kPaymentMethodsLearnMoreURL[] =
    "https://support.huhisoft.com";

const char kPrivacyLearnMoreURL[] =
    "https://support.huhisoft.com/hc/en-us/articles/"
    "360017989132-How-do-I-change-my-Privacy-Settings-";

const char kRemoveNonCWSExtensionURL[] =
    "https://support.huhisoft.com/hc/en-us/articles/"
    "360017914832-Why-am-I-seeing-the-message-extensions-disabled-by-Huhi-";

const char kResetProfileSettingsLearnMoreURL[] =
    "https://support.huhisoft.com/hc/en-us/articles/"
    "360017903152-How-do-I-reset-Huhi-settings-to-default-";

const char kSafeBrowsingHelpCenterURL[] =
    "https://support.huhisoft.com/";

const char kSafetyTipHelpCenterURL[] =
    "https://support.huhisoft.com/";

const char kSettingsSearchHelpURL[] =
    "https://support.huhisoft.com/";

const char kSyncAndGoogleServicesLearnMoreURL[] =
    "https://support.huhisoft.com/";

const char kSyncEncryptionHelpURL[] =
    "https://support.huhisoft.com/";

const char kSyncErrorsHelpURL[] =
    "https://support.huhisoft.com/";

const char kSyncGoogleDashboardURL[] =
    "https://support.huhisoft.com/";

const char kSyncLearnMoreURL[] =
    "https://support.huhisoft.com/";

const char kUpgradeHelpCenterBaseURL[] =
    "https://support.huhisoft.com/hc/en-us/articles/"
    "360025390311-How-do-I-download-and-install-Huhi-";

const char kWhoIsMyAdministratorHelpURL[] =
    "https://support.huhisoft.com/";

const char kChromeFlashRoadmapURL[] = "https://support.huhisoft.com/";

#if defined(OS_ANDROID)
const char kAndroidAppScheme[] = "android-app";
#endif

#if defined(OS_ANDROID)
const char kEnhancedPlaybackNotificationLearnMoreURL[] =
// Keep in sync with chrome/android/java/strings/android_chrome_strings.grd
    "https://community.huhisoft.com";
#endif

#if defined(OS_MAC)
const char kChromeEnterpriseSignInLearnMoreURL[] =
    "https://support.huhisoft.com/";

const char kMac10_9_ObsoleteURL[] =
    "https://support.huhisoft.com/hc/en-us/articles/"
    "360025390311-How-do-I-download-and-install-Huhi-";
#endif

#if defined(OS_WIN)
const char kChromeCleanerLearnMoreURL[] =
    "https://support.huhisoft.com/hc/en-us/articles/"
    "360017884152-How-do-I-remove-unwanted-ads-pop-ups-malware-";

const char kWindowsXPVistaDeprecationURL[] =
    "https://support.huhisoft.com/";
#endif

#if BUILDFLAG(ENABLE_ONE_CLICK_SIGNIN)
const char kChromeSyncLearnMoreURL[] =
    "https://support.huhisoft.com/";
#endif  // BUILDFLAG(ENABLE_ONE_CLICK_SIGNIN)

#if BUILDFLAG(ENABLE_PLUGINS)
const char kBlockedPluginLearnMoreURL[] =
    "https://support.huhisoft.com/hc/en-us/articles/"
    "360018163151-How-do-I-manage-Flash-audio-video-";

const char kOutdatedPluginLearnMoreURL[] =
    "https://support.huhisoft.com/hc/en-us/articles/"
    "360018163151-How-do-I-manage-Flash-audio-video-";
#endif

}  // namespace chrome
