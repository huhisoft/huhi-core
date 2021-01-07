/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/ui/huhi_browser_command_controller.h"

#include <vector>

#include "huhi/app/huhi_command_ids.h"
#include "huhi/browser/profiles/profile_util.h"
#include "huhi/browser/ui/huhi_pages.h"
#include "huhi/browser/ui/browser_commands.h"
#include "huhi/common/pref_names.h"
#include "huhi/components/huhi_rewards/browser/buildflags/buildflags.h"
#include "huhi/components/huhi_sync/buildflags/buildflags.h"
#include "huhi/components/huhi_wallet/buildflags/buildflags.h"
#include "chrome/app/chrome_command_ids.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_commands.h"
#include "chrome/browser/ui/tabs/tab_strip_model.h"
#include "components/prefs/pref_service.h"

#if BUILDFLAG(ENABLE_HUHI_SYNC)
#include "components/sync/driver/sync_driver_switches.h"
#endif

namespace {

bool IsHuhiCommands(int id) {
  return id >= IDC_HUHI_COMMANDS_START && id <= IDC_HUHI_COMMANDS_LAST;
}

bool IsHuhiOverrideCommands(int id) {
  static std::vector<int> override_commands({
      IDC_NEW_WINDOW,
      IDC_NEW_INCOGNITO_WINDOW,
  });
  return std::find(override_commands.begin(), override_commands.end(), id) !=
         override_commands.end();
}

}  // namespace

namespace chrome {

HuhiBrowserCommandController::HuhiBrowserCommandController(Browser* browser)
    : BrowserCommandController(browser),
      browser_(browser),
      huhi_command_updater_(nullptr) {
  InitHuhiCommandState();
}

bool HuhiBrowserCommandController::SupportsCommand(int id) const {
  return IsHuhiCommands(id)
      ? huhi_command_updater_.SupportsCommand(id)
      : BrowserCommandController::SupportsCommand(id);
}

bool HuhiBrowserCommandController::IsCommandEnabled(int id) const {
  return IsHuhiCommands(id)
      ? huhi_command_updater_.IsCommandEnabled(id)
      : BrowserCommandController::IsCommandEnabled(id);
}

bool HuhiBrowserCommandController::ExecuteCommandWithDisposition(
    int id,
    WindowOpenDisposition disposition,
    base::TimeTicks time_stamp) {
  return IsHuhiCommands(id) || IsHuhiOverrideCommands(id)
             ? ExecuteHuhiCommandWithDisposition(id, disposition, time_stamp)
             : BrowserCommandController::ExecuteCommandWithDisposition(
                   id, disposition, time_stamp);
}

void HuhiBrowserCommandController::AddCommandObserver(
    int id, CommandObserver* observer) {
  IsHuhiCommands(id)
      ? huhi_command_updater_.AddCommandObserver(id, observer)
      : BrowserCommandController::AddCommandObserver(id, observer);
}

void HuhiBrowserCommandController::RemoveCommandObserver(
    int id, CommandObserver* observer) {
  IsHuhiCommands(id)
      ? huhi_command_updater_.RemoveCommandObserver(id, observer)
      : BrowserCommandController::RemoveCommandObserver(id, observer);
}

void HuhiBrowserCommandController::RemoveCommandObserver(
    CommandObserver* observer) {
  huhi_command_updater_.RemoveCommandObserver(observer);
  BrowserCommandController::RemoveCommandObserver(observer);
}

bool HuhiBrowserCommandController::UpdateCommandEnabled(int id, bool state) {
  return IsHuhiCommands(id)
      ? huhi_command_updater_.UpdateCommandEnabled(id, state)
      : BrowserCommandController::UpdateCommandEnabled(id, state);
}

void HuhiBrowserCommandController::InitHuhiCommandState() {
  // Sync & Rewards pages doesn't work on tor(guest) session.
  // They also doesn't work on private window but they are redirected
  // to normal window in this case.
  const bool is_guest_session = browser_->profile()->IsGuestSession();
  if (!is_guest_session) {
#if BUILDFLAG(HUHI_REWARDS_ENABLED)
    UpdateCommandForHuhiRewards();
#endif
#if BUILDFLAG(HUHI_WALLET_ENABLED)
    UpdateCommandForHuhiWallet();
#endif
#if BUILDFLAG(ENABLE_HUHI_SYNC)
    if (switches::IsSyncAllowedByFlag())
      UpdateCommandForHuhiSync();
#endif
  }
  UpdateCommandForHuhiAdblock();
  UpdateCommandForWebcompatReporter();
#if BUILDFLAG(ENABLE_TOR)
  UpdateCommandForTor();
#endif
  UpdateCommandEnabled(IDC_ADD_NEW_PROFILE, !is_guest_session);
  UpdateCommandEnabled(IDC_OPEN_GUEST_PROFILE, !is_guest_session);
  UpdateCommandEnabled(IDC_TOGGLE_SPEEDREADER, true);
}

void HuhiBrowserCommandController::UpdateCommandForHuhiRewards() {
  UpdateCommandEnabled(IDC_SHOW_HUHI_REWARDS, true);
}

void HuhiBrowserCommandController::UpdateCommandForHuhiAdblock() {
  UpdateCommandEnabled(IDC_SHOW_HUHI_ADBLOCK, true);
}

void HuhiBrowserCommandController::UpdateCommandForWebcompatReporter() {
  UpdateCommandEnabled(IDC_SHOW_HUHI_WEBCOMPAT_REPORTER, true);
}

#if BUILDFLAG(ENABLE_TOR)
void HuhiBrowserCommandController::UpdateCommandForTor() {
  // Enable new tor connection only for tor profile.
  UpdateCommandEnabled(IDC_NEW_TOR_CONNECTION_FOR_SITE,
                       huhi::IsTorProfile(browser_->profile()));
  UpdateCommandEnabled(IDC_NEW_OFFTHERECORD_WINDOW_TOR,
                       !huhi::IsTorDisabledForProfile(browser_->profile()));
}
#endif

void HuhiBrowserCommandController::UpdateCommandForHuhiSync() {
  UpdateCommandEnabled(IDC_SHOW_HUHI_SYNC, true);
}

void HuhiBrowserCommandController::UpdateCommandForHuhiWallet() {
  UpdateCommandEnabled(IDC_SHOW_HUHI_WALLET, true);
}

bool HuhiBrowserCommandController::ExecuteHuhiCommandWithDisposition(
    int id,
    WindowOpenDisposition disposition,
    base::TimeTicks time_stamp) {
  if (!SupportsCommand(id) || !IsCommandEnabled(id))
    return false;

  if (browser_->tab_strip_model()->active_index() == TabStripModel::kNoTab)
    return true;

  DCHECK(IsCommandEnabled(id)) << "Invalid/disabled command " << id;

  switch (id) {
    case IDC_NEW_WINDOW:
      // Use chromium's action for non-Tor profiles.
      if (!huhi::IsTorProfile(browser_->profile()))
        return BrowserCommandController::ExecuteCommandWithDisposition(
            id, disposition, time_stamp);
      NewEmptyWindow(huhi::GetParentProfile(browser_->profile()));
      break;
    case IDC_NEW_INCOGNITO_WINDOW:
      // Use chromium's action for non-Tor profiles.
      if (!huhi::IsTorProfile(browser_->profile()))
        return BrowserCommandController::ExecuteCommandWithDisposition(
            id, disposition, time_stamp);
      NewIncognitoWindow(huhi::GetParentProfile(browser_->profile()));
      break;
    case IDC_SHOW_HUHI_REWARDS:
      huhi::ShowHuhiRewards(browser_);
      break;
    case IDC_SHOW_HUHI_ADBLOCK:
      huhi::ShowHuhiAdblock(browser_);
      break;
    case IDC_SHOW_HUHI_WEBCOMPAT_REPORTER:
      huhi::ShowWebcompatReporter(browser_);
      break;
    case IDC_NEW_OFFTHERECORD_WINDOW_TOR:
      huhi::NewOffTheRecordWindowTor(browser_);
      break;
    case IDC_NEW_TOR_CONNECTION_FOR_SITE:
      huhi::NewTorConnectionForSite(browser_);
      break;
    case IDC_SHOW_HUHI_SYNC:
      huhi::ShowSync(browser_);
      break;
    case IDC_SHOW_HUHI_WALLET:
      huhi::ShowHuhiWallet(browser_);
      break;
    case IDC_ADD_NEW_PROFILE:
      huhi::AddNewProfile();
      break;
    case IDC_OPEN_GUEST_PROFILE:
      huhi::OpenGuestProfile();
      break;
    case IDC_TOGGLE_SPEEDREADER:
      huhi::ToggleSpeedreader(browser_);
      break;
    default:
      LOG(WARNING) << "Received Unimplemented Command: " << id;
      break;
  }

  return true;
}

}  // namespace chrome
