/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/profiles/profile_util.h"
#include "huhi/common/webui_url_constants.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_finder.h"
#include "chrome/browser/ui/browser_navigator_params.h"
#include "chrome/common/webui_url_constants.h"
#include "url/gurl.h"

namespace {

bool HandleURLInParent(NavigateParams* params, Profile* profile) {
  if (huhi::IsTorProfile(profile) &&
      !params->browser->profile()->IsOffTheRecord()) {
    return true;
  }

  return false;
}

// GetOrCreateBrowser is not accessible here
Browser* HuhiGetOrCreateBrowser(Profile* profile, bool user_gesture) {
  Browser* browser = chrome::FindTabbedBrowser(profile, false);
  return browser ? browser
                 : new Browser(Browser::CreateParams(profile, user_gesture));
}

void UpdateHuhiScheme(NavigateParams* params) {
  if (params->url.SchemeIs(content::kHuhiUIScheme)) {
    GURL::Replacements replacements;
    replacements.SetSchemeStr(content::kChromeUIScheme);
    params->url = params->url.ReplaceComponents(replacements);
  }
}

void MaybeHandleInParent(NavigateParams* params, bool allow_in_incognito) {
  auto* profile = params->initiating_profile;
  if (huhi::IsSessionProfile(profile)) {
    if (!allow_in_incognito) {
      params->initiating_profile =
          profile->IsOffTheRecord()
              ? huhi::GetParentProfile(profile)->GetOffTheRecordProfile()
              : huhi::GetParentProfile(profile);
    } else if (HandleURLInParent(params, profile)) {
      params->browser = HuhiGetOrCreateBrowser(
          huhi::GetParentProfile(profile), params->user_gesture);
    }
  }
}

bool IsHostAllowedInIncognitoHuhiImpl(const base::StringPiece& host) {
  if (host == kWalletHost ||
      host == kRewardsPageHost ||
      host == chrome::kChromeUISyncInternalsHost) {
    return false;
  }

  return true;
}

}  // namespace

#define HUHI_ADJUST_NAVIGATE_PARAMS_FOR_URL           \
  UpdateHuhiScheme(params);                           \
  MaybeHandleInParent(params, IsURLAllowedInIncognito( \
                                  params->url, params->initiating_profile));

#include "../../../../../chrome/browser/ui/browser_navigator.cc"
#undef HUHI_ADJUST_NAVIGATE_PARAMS_FOR_URL
