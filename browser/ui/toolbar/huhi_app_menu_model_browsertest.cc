/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/ui/toolbar/huhi_app_menu_model.h"

#include <algorithm>
#include <vector>

#include "huhi/browser/profiles/profile_util.h"
#include "huhi/browser/tor/buildflags.h"
#include "huhi/browser/ui/huhi_browser_command_controller.h"
#include "huhi/browser/ui/browser_commands.h"
#include "huhi/components/huhi_rewards/browser/buildflags/buildflags.h"
#include "huhi/components/huhi_sync/buildflags/buildflags.h"
#include "huhi/components/huhi_wallet/browser/buildflags/buildflags.h"
#include "chrome/app/chrome_command_ids.h"
#include "chrome/browser/chrome_notification_types.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_window.h"
#include "chrome/browser/ui/browser_list.h"
#include "chrome/browser/ui/views/frame/browser_view.h"
#include "chrome/browser/ui/views/toolbar/toolbar_view.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "content/public/browser/notification_service.h"
#include "content/public/test/browser_test.h"
#include "content/public/test/test_utils.h"

#if BUILDFLAG(ENABLE_HUHI_SYNC)
#include "components/sync/driver/sync_driver_switches.h"
#endif

using HuhiAppMenuBrowserTest = InProcessBrowserTest;

void CheckCommandsAreDisabledInMenuModel(
    Browser* browser,
    const std::vector<int>& disabled_commands) {
  auto* browser_view = BrowserView::GetBrowserViewForBrowser(browser);
  HuhiAppMenuModel model(browser_view->toolbar(), browser);
  model.Init();
  for (int id : disabled_commands)
    EXPECT_EQ(-1, model.GetIndexOfCommandId(id));
}

void CheckCommandsAreInOrderInMenuModel(
    Browser* browser,
    const std::vector<int>& commands_in_order) {
  auto* browser_view = BrowserView::GetBrowserViewForBrowser(browser);
  HuhiAppMenuModel model(browser_view->toolbar(), browser);
  model.Init();

  std::vector<int> commands_index;
  for (int id : commands_in_order) {
    int index = model.GetIndexOfCommandId(id);
    EXPECT_NE(-1, index);
    commands_index.push_back(index);
  }
  EXPECT_TRUE(std::is_sorted(std::begin(commands_index),
                             std::end(commands_index)));
}

// Test huhi menu order test.
// Huhi menu is inserted based on corresponding commands enable status.
// So, this doesn't test for each profiles(normal, private, tor and guest).
// Instead, HuhiBrowserCommandControllerTest will do that.
IN_PROC_BROWSER_TEST_F(HuhiAppMenuBrowserTest, MenuOrderTest) {
  std::vector<int> commands_in_order_for_normal_profile = {
    IDC_NEW_TAB,
    IDC_NEW_WINDOW,
    IDC_NEW_INCOGNITO_WINDOW,
#if BUILDFLAG(ENABLE_TOR)
    IDC_NEW_OFFTHERECORD_WINDOW_TOR,
#endif
#if BUILDFLAG(HUHI_REWARDS_ENABLED)
    IDC_SHOW_HUHI_REWARDS,
#endif
    IDC_RECENT_TABS_MENU,
    IDC_BOOKMARKS_MENU,
    IDC_SHOW_DOWNLOADS,
#if BUILDFLAG(HUHI_WALLET_ENABLED)
    IDC_SHOW_HUHI_WALLET,
#endif
    IDC_MANAGE_EXTENSIONS,
#if BUILDFLAG(ENABLE_HUHI_SYNC)
    IDC_SHOW_HUHI_SYNC,
#endif
    IDC_SHOW_HUHI_ADBLOCK,
    IDC_ADD_NEW_PROFILE,
    IDC_OPEN_GUEST_PROFILE,
    IDC_SHOW_HUHI_WEBCOMPAT_REPORTER
  };
  std::vector<int> commands_disabled_for_normal_profile = {
    IDC_NEW_TOR_CONNECTION_FOR_SITE,
  };
#if BUILDFLAG(ENABLE_HUHI_SYNC)
  if (!switches::IsSyncAllowedByFlag()) {
    commands_in_order_for_normal_profile.erase(
        std::remove(commands_in_order_for_normal_profile.begin(),
                    commands_in_order_for_normal_profile.end(),
                    IDC_SHOW_HUHI_SYNC),
        commands_in_order_for_normal_profile.end());
    commands_disabled_for_normal_profile.push_back(IDC_SHOW_HUHI_SYNC);
  }
#endif
  CheckCommandsAreInOrderInMenuModel(browser(),
                                     commands_in_order_for_normal_profile);
  CheckCommandsAreDisabledInMenuModel(browser(),
                                      commands_disabled_for_normal_profile);

  auto* private_browser = CreateIncognitoBrowser();
  std::vector<int> commands_in_order_for_private_profile = {
    IDC_NEW_TAB,
    IDC_NEW_WINDOW,
    IDC_NEW_INCOGNITO_WINDOW,
#if BUILDFLAG(ENABLE_TOR)
    IDC_NEW_OFFTHERECORD_WINDOW_TOR,
#endif
#if BUILDFLAG(HUHI_REWARDS_ENABLED)
    IDC_SHOW_HUHI_REWARDS,
#endif
    IDC_BOOKMARKS_MENU,
    IDC_SHOW_DOWNLOADS,
#if BUILDFLAG(HUHI_WALLET_ENABLED)
    IDC_SHOW_HUHI_WALLET,
#endif
    IDC_MANAGE_EXTENSIONS,
#if BUILDFLAG(ENABLE_HUHI_SYNC)
    IDC_SHOW_HUHI_SYNC,
#endif
    IDC_SHOW_HUHI_ADBLOCK,
    IDC_ADD_NEW_PROFILE,
    IDC_OPEN_GUEST_PROFILE,
    IDC_SHOW_HUHI_WEBCOMPAT_REPORTER
  };
  std::vector<int> commands_disabled_for_private_profile = {
    IDC_NEW_TOR_CONNECTION_FOR_SITE,
    IDC_RECENT_TABS_MENU,
  };
#if BUILDFLAG(ENABLE_HUHI_SYNC)
  if (!switches::IsSyncAllowedByFlag()) {
    commands_in_order_for_private_profile.erase(
        std::remove(commands_in_order_for_private_profile.begin(),
                    commands_in_order_for_private_profile.end(),
                    IDC_SHOW_HUHI_SYNC),
        commands_in_order_for_private_profile.end());
    commands_disabled_for_private_profile.push_back(IDC_SHOW_HUHI_SYNC);
  }
#endif
  CheckCommandsAreInOrderInMenuModel(private_browser,
                                     commands_in_order_for_private_profile);
  CheckCommandsAreDisabledInMenuModel(private_browser,
                                      commands_disabled_for_private_profile);

  content::WindowedNotificationObserver browser_creation_observer(
      chrome::NOTIFICATION_BROWSER_OPENED,
      content::NotificationService::AllSources());
  profiles::SwitchToGuestProfile(ProfileManager::CreateCallback());

  browser_creation_observer.Wait();

  auto* browser_list = BrowserList::GetInstance();
  Browser* guest_browser = nullptr;
  for (Browser* browser : *browser_list) {
    if (browser->profile()->IsGuestSession()) {
      guest_browser = browser;
      break;
    }
  }
  DCHECK(guest_browser);
  std::vector<int> commands_in_order_for_guest_profile = {
    IDC_NEW_TAB,
    IDC_NEW_WINDOW,
    IDC_SHOW_DOWNLOADS,
    IDC_SHOW_HUHI_ADBLOCK,
    IDC_SHOW_HUHI_WEBCOMPAT_REPORTER
  };
  CheckCommandsAreInOrderInMenuModel(guest_browser,
                                     commands_in_order_for_guest_profile);
  std::vector<int> commands_disabled_for_guest_profile = {
    IDC_NEW_INCOGNITO_WINDOW,
#if BUILDFLAG(ENABLE_TOR)
    IDC_NEW_OFFTHERECORD_WINDOW_TOR,
#endif
#if BUILDFLAG(HUHI_REWARDS_ENABLED)
    IDC_SHOW_HUHI_REWARDS,
#endif
    IDC_RECENT_TABS_MENU,
    IDC_BOOKMARKS_MENU,
#if BUILDFLAG(HUHI_WALLET_ENABLED)
    IDC_SHOW_HUHI_WALLET,
#endif
    IDC_MANAGE_EXTENSIONS,
    IDC_ADD_NEW_PROFILE,
    IDC_OPEN_GUEST_PROFILE,
  };
  CheckCommandsAreDisabledInMenuModel(guest_browser,
                                      commands_disabled_for_guest_profile);

  content::WindowedNotificationObserver tor_browser_creation_observer(
      chrome::NOTIFICATION_BROWSER_OPENED,
      content::NotificationService::AllSources());
  huhi::NewOffTheRecordWindowTor(browser());
  tor_browser_creation_observer.Wait();
  Browser* tor_browser = nullptr;
  for (Browser* browser : *browser_list) {
    if (huhi::IsTorProfile(browser->profile())) {
      tor_browser = browser;
      break;
    }
  }
  DCHECK(tor_browser);
  std::vector<int> commands_in_order_for_tor_profile = {
    IDC_NEW_TAB,
    IDC_NEW_TOR_CONNECTION_FOR_SITE,
    IDC_NEW_WINDOW,
    IDC_NEW_INCOGNITO_WINDOW,
#if BUILDFLAG(ENABLE_TOR)
    IDC_NEW_OFFTHERECORD_WINDOW_TOR,
#endif
#if BUILDFLAG(HUHI_REWARDS_ENABLED)
    IDC_SHOW_HUHI_REWARDS,
#endif
    IDC_BOOKMARKS_MENU,
    IDC_SHOW_DOWNLOADS,
#if BUILDFLAG(HUHI_WALLET_ENABLED)
    IDC_SHOW_HUHI_WALLET,
#endif
#if BUILDFLAG(ENABLE_HUHI_SYNC)
    IDC_SHOW_HUHI_SYNC,
#endif
    IDC_SHOW_HUHI_ADBLOCK,
    IDC_ADD_NEW_PROFILE,
    IDC_OPEN_GUEST_PROFILE,
    IDC_SHOW_HUHI_WEBCOMPAT_REPORTER
  };
  std::vector<int> commands_disabled_for_tor_profile = {
    IDC_RECENT_TABS_MENU,
  };
#if BUILDFLAG(ENABLE_HUHI_SYNC)
  if (!switches::IsSyncAllowedByFlag()) {
    commands_in_order_for_tor_profile.erase(
        std::remove(commands_in_order_for_tor_profile.begin(),
                    commands_in_order_for_tor_profile.end(),
                    IDC_SHOW_HUHI_SYNC),
        commands_in_order_for_tor_profile.end());
    commands_disabled_for_tor_profile.push_back(IDC_SHOW_HUHI_SYNC);
  }
#endif
  CheckCommandsAreInOrderInMenuModel(tor_browser,
                                     commands_in_order_for_tor_profile);
  CheckCommandsAreDisabledInMenuModel(tor_browser,
                                      commands_disabled_for_tor_profile);
}
