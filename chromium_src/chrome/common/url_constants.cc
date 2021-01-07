/* Copyright 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/common/url_constants.h"

#include "build/branding_buildflags.h"
#include "chrome/common/webui_url_constants.h"

namespace chrome {

const char kAccessibilityLabelsLearnMoreURL[] =
    "https://support.hnq.vn/";

const char kAutomaticSettingsResetLearnMoreURL[] =
    "https://support.hnq.vn/hc/en-us/articles/360017903152-How-do-I-reset-Huhi-settings-to-default-";

const char kAdvancedProtectionDownloadLearnMoreURL[] =
    "https://support.hnq.vn";

const char kBluetoothAdapterOffHelpURL[] =
    "https://support.hnq.vn/";

const char kCastCloudServicesHelpURL[] =
    "https://support.hnq.vn/";

const char kCastNoDestinationFoundURL[] =
    "https://support.hnq.vn/";

const char kChooserBluetoothOverviewURL[] =
    "https://support.hnq.vn/";

const char kChooserUsbOverviewURL[] =
    "https://support.hnq.vn/";

const char kChromeBetaForumURL[] =
    "https://community.hnq.vnc/beta-builds";

const char kChromeFixUpdateProblems[] =
    "https://support.hnq.vn/";

const char kChromeReleaseNotesURL[] =
    "https://hnq.vn/latest/";

const char kChromeHelpViaKeyboardURL[] =
#if defined(OS_CHROMEOS)
#if defined(GOOGLE_CHROME_BUILD)
    "https://support.hnq.vn/";
#else
    "https://support.hnq.vn/";
#endif  // defined(GOOGLE_CHROME_BUILD)
#else
    "https://support.hnq.vn/";
#endif  // defined(OS_CHROMEOS)

const char kChromeHelpViaMenuURL[] =
#if defined(OS_CHROMEOS)
#if defined(GOOGLE_CHROME_BUILD)
    "https://support.hnq.vn/";
#else
    "https://support.hnq.vn/";
#endif  // defined(GOOGLE_CHROME_BUILD)
#else
    "https://support.hnq.vn/";
#endif  // defined(OS_CHROMEOS)

const char kChromeHelpViaWebUIURL[] =
    "https://support.hnq.vn/";
#if defined(OS_CHROMEOS)
const char kChromeOsHelpViaWebUIURL[] =
#if BUILDFLAG(GOOGLE_CHROME_BRANDING)
    "https://support.hnq.vn/";
#else
    "https://support.hnq.vn/";
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
    "https://support.hnq.vn/hc/en-us/articles/360017880792-How-do-I-print-from-Huhi-";

const char kCloudPrintCertificateErrorLearnMoreURL[] =
    "https://support.hnq.vn/hc/en-us/articles/360017880792-How-do-I-print-from-Huhi-";

const char kContentSettingsExceptionsLearnMoreURL[] =
    "https://support.hnq.vn/hc/en-us/articles/360018205431-How-do-I-change-site-permissions-";

const char kCookiesSettingsHelpCenterURL[] =
    "https://support.hnq.vn/hc/en-us/articles/360018205431-How-do-I-change-site-permissions-";
const char kCpuX86Sse2ObsoleteURL[] =
    "https://support.hnq.vn/";

const char kCrashReasonURL[] =
    "https://support.hnq.vn/hc/en-us/articles/360018192251-How-do-I-fix-page-crashes-and-other-page-loading-errors-";

const char kCrashReasonFeedbackDisplayedURL[] =
    "https://support.hnq.vn/hc/en-us/articles/360018192251-How-do-I-fix-page-crashes-and-other-page-loading-errors-";

const char kDoNotTrackLearnMoreURL[] =
    "https://support.hnq.vn/hc/en-us/articles/360017905612-How-do-I-turn-Do-Not-Track-on-or-off-";

const char kDownloadInterruptedLearnMoreURL[] =
    "https://support.hnq.vn/hc/en-us/articles/360018192491-How-do-I-fix-file-download-errors-";

const char kDownloadScanningLearnMoreURL[] =
    "https://support.hnq.vn/hc/en-us/articles/360018192491-How-do-I-fix-file-download-errors-";

const char kExtensionControlledSettingLearnMoreURL[] =
    "https://support.hnq.vn/hc/en-us/articles/360018185651-How-do-I-stop-extensions-from-changing-my-settings-";

const char kExtensionInvalidRequestURL[] = "chrome-extension://invalid/";

const char kFlashDeprecationLearnMoreURL[] =
    "https://blog.chromium.org/2017/07/so-long-and-thanks-for-all-flash.html";

const char kGoogleAccountActivityControlsURL[] =
    "https://support.hnq.vn/";

const char kGoogleAccountURL[] = "https://support.hnq.vn/";

const char kGoogleAccountChooserURL[] = "https://support.hnq.vn/";

const char kGooglePasswordManagerURL[] = "https://support.hnq.vn";

const char kLearnMoreReportingURL[] =
    "https://support.hnq.vn/hc/en-us/articles/360017905872-How-do-I-enable-or-disable-automatic-crash-reporting-";

const char kLegacySupervisedUserManagementDisplayURL[] =
    "https://support.hnq.vn/";

const char kManagedUiLearnMoreUrl[] = "https://support.hnq.vn/";

const char kMixedContentDownloadBlockingLearnMoreUrl[] =
    "https://support.hnq.vn/";

const char kMyActivityUrlInClearBrowsingData[] =
    "https://support.hnq.vn/";

const char kOmniboxLearnMoreURL[] =
    "https://support.hnq.vn/hc/en-us/articles/360017479752-How-do-I-set-my-default-search-engine-";

const char kPageInfoHelpCenterURL[] =
    "https://support.hnq.vn/hc/en-us/articles/360018185871-How-do-I-check-if-a-site-s-connection-is-secure-";

const char kPasswordCheckLearnMoreURL[] = "https://support.hnq.vn/";

const char kPasswordGenerationLearnMoreURL[] = "https://support.hnq.vn/";

const char kPasswordManagerLearnMoreURL[] =
    "https://support.hnq.vn/hc/en-us/articles/360018185951-How-do-I-use-the-built-in-password-manager-";

const char kPaymentMethodsURL[] = "https://support.hnq.vn";

const char kPaymentMethodsLearnMoreURL[] =
    "https://support.hnq.vn";

const char kPrivacyLearnMoreURL[] =
    "https://support.hnq.vn/hc/en-us/articles/360017989132-How-do-I-change-my-Privacy-Settings-";

const char kRemoveNonCWSExtensionURL[] =
    "https://support.hnq.vn/hc/en-us/articles/360017914832-Why-am-I-seeing-the-message-extensions-disabled-by-Huhi-";

const char kResetProfileSettingsLearnMoreURL[] =
    "https://support.hnq.vn/hc/en-us/articles/360017903152-How-do-I-reset-Huhi-settings-to-default-";

const char kSafeBrowsingHelpCenterURL[] =
    "https://support.hnq.vn/";

const char kSafetyTipHelpCenterURL[] =
    "https://support.hnq.vn/";
const char kSeeMoreSecurityTipsURL[] =
    "https://support.hnq.vn/";

const char kSettingsSearchHelpURL[] =
    "https://support.hnq.vn/";

const char kSyncAndGoogleServicesLearnMoreURL[] =
    "https://support.hnq.vn/";

const char kSyncEncryptionHelpURL[] =
    "https://support.hnq.vn/";

const char kSyncErrorsHelpURL[] =
    "https://support.hnq.vn/";

const char kSyncGoogleDashboardURL[] =
    "https://support.hnq.vn/";

const char kSyncLearnMoreURL[] =
    "https://support.hnq.vn/";

const char kUpgradeHelpCenterBaseURL[] =
    "https://support.hnq.vn/hc/en-us/articles/360025390311-How-do-I-download-and-install-Huhi-";

const char kWhoIsMyAdministratorHelpURL[] =
    "https://support.hnq.vn/";

const char kChromeFlashRoadmapURL[] = "https://support.hnq.vn/";

#if defined(OS_ANDROID)
const char kAndroidAppScheme[] = "android-app";
#endif

#if defined(OS_ANDROID)
const char kEnhancedPlaybackNotificationLearnMoreURL[] =
// Keep in sync with chrome/android/java/strings/android_chrome_strings.grd
    "https://community.hnq.vn";
#endif

#if defined(OS_MAC)
const char kChromeEnterpriseSignInLearnMoreURL[] =
    "https://support.hnq.vn/";

const char kMac10_10_ObsoleteURL[] =
    "https://support.hnq.vn/hc/en-us/articles/360025390311-How-do-I-download-and-install-Huhi-";
#endif

#if defined(OS_WIN)
const char kChromeCleanerLearnMoreURL[] =
    "https://support.hnq.vn/hc/en-us/articles/360017884152-How-do-I-remove-unwanted-ads-pop-ups-malware-";

const char kWindowsXPVistaDeprecationURL[] =
    "https://support.hnq.vn/";
#endif

#if BUILDFLAG(ENABLE_ONE_CLICK_SIGNIN)
const char kChromeSyncLearnMoreURL[] =
    "https://support.hnq.vn/";
#endif  // BUILDFLAG(ENABLE_ONE_CLICK_SIGNIN)

#if BUILDFLAG(ENABLE_PLUGINS)
const char kBlockedPluginLearnMoreURL[] =
    "https://support.hnq.vn/hc/en-us/articles/360018163151-How-do-I-manage-Flash-audio-video-";

const char kOutdatedPluginLearnMoreURL[] =
    "https://support.hnq.vn/hc/en-us/articles/360018163151-How-do-I-manage-Flash-audio-video-";
#endif

}  // namespace chrome
