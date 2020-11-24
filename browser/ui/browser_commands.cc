/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/ui/browser_commands.h"

#include "huhi/browser/profiles/profile_util.h"
#include "huhi/browser/tor/tor_profile_service.h"
#include "huhi/browser/tor/tor_profile_service_factory.h"
#include "huhi/components/speedreader/buildflags.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_manager.h"
#include "chrome/browser/profiles/profile_metrics.h"
#include "chrome/browser/profiles/profile_window.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_commands.h"
#include "chrome/browser/ui/tabs/tab_strip_model.h"
#include "chrome/common/pref_names.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/web_contents.h"

#if BUILDFLAG(ENABLE_SPEEDREADER)
#include "huhi/browser/speedreader/speedreader_service_factory.h"
#include "huhi/components/speedreader/speedreader_service.h"
#endif

using content::WebContents;

namespace {
}  // namespace

namespace huhi {

void NewOffTheRecordWindowTor(Browser* browser) {
  if (huhi::IsTorProfile(browser->profile())) {
    chrome::NewEmptyWindow(browser->profile());
    return;
  }

  profiles::SwitchToTorProfile(ProfileManager::CreateCallback());
}

void NewTorConnectionForSite(Browser* browser) {
  Profile* profile = browser->profile();
  DCHECK(profile);
  tor::TorProfileService* service =
    TorProfileServiceFactory::GetForProfile(profile);
  DCHECK(service);
  WebContents* current_tab =
    browser->tab_strip_model()->GetActiveWebContents();
  if (!current_tab)
    return;
  service->SetNewTorCircuit(current_tab);
}

void AddNewProfile() {
  profiles::CreateAndSwitchToNewProfile(
    ProfileManager::CreateCallback(),
    ProfileMetrics::ADD_NEW_USER_MENU);
}

void OpenGuestProfile() {
  PrefService* service = g_browser_process->local_state();
  DCHECK(service);
  DCHECK(service->GetBoolean(prefs::kBrowserGuestModeEnabled));
  profiles::SwitchToGuestProfile(ProfileManager::CreateCallback());
}

void ToggleSpeedreader(Browser* browser) {
#if BUILDFLAG(ENABLE_SPEEDREADER)
  speedreader::SpeedreaderService* service =
      speedreader::SpeedreaderServiceFactory::GetForProfile(browser->profile());
  if (service) {
    // This will trigger a button update via a pref change subscribition.
    service->ToggleSpeedreader();

    WebContents* contents = browser->tab_strip_model()->GetActiveWebContents();
    if (contents) {
      contents->GetController().Reload(content::ReloadType::NORMAL, false);
    }
  }
#endif  // BUILDFLAG(ENABLE_SPEEDREADER)
}

}  // namespace huhi
