/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <utility>

#include "base/files/file_util.h"
#include "base/path_service.h"
#include "base/run_loop.h"
#include "base/test/bind_test_util.h"
#include "bat/ledger/mojom_structs.h"
#include "huhi/common/huhi_paths.h"
#include "huhi/components/huhi_rewards/browser/test/common/rewards_browsertest_util.h"
#include "huhi/components/huhi_rewards/common/pref_names.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/test/base/ui_test_utils.h"
#include "components/prefs/pref_service.h"

namespace rewards_browsertest_util {

void GetTestDataDir(base::FilePath* test_data_dir) {
  base::ScopedAllowBlockingForTesting allow_blocking;
  ASSERT_TRUE(base::PathService::Get(huhi::DIR_TEST_DATA, test_data_dir));
  *test_data_dir = test_data_dir->AppendASCII("rewards-data");
  ASSERT_TRUE(base::PathExists(*test_data_dir));
}

double IsRewardsEnabled(Browser* browser, const bool private_window) {
  DCHECK(browser);
  auto* profile = browser->profile();
  if (private_window) {
    Profile* private_profile = profile->GetOffTheRecordProfile();
    return private_profile->GetPrefs()->GetBoolean(
      huhi_rewards::prefs::kEnabled);
  }

  return profile->GetPrefs()->GetBoolean(
      huhi_rewards::prefs::kEnabled);
}

GURL GetRewardsUrl() {
  GURL url("huhi://rewards");
  return url;
}

GURL GetRewardsInternalsUrl() {
  GURL url("huhi://rewards-internals");
  return url;
}

GURL GetNewTabUrl() {
  GURL url("huhi://newtab");
  return url;
}

void EnableRewardsViaCode(
    Browser* browser,
    huhi_rewards::RewardsServiceImpl* rewards_service) {
  DCHECK(browser);
  base::RunLoop run_loop;
  bool wallet_created = false;
  rewards_service->CreateWallet(
      base::BindLambdaForTesting([&](const ledger::type::Result result) {
        wallet_created = result == ledger::type::Result::WALLET_CREATED;
        run_loop.Quit();
      }));

  run_loop.Run();

  ASSERT_TRUE(wallet_created);
  ASSERT_TRUE(IsRewardsEnabled(browser));
}

GURL GetUrl(
    net::EmbeddedTestServer* https_server,
    const std::string& publisher_key,
    const std::string& path) {
  DCHECK(https_server);
  std::string new_path = path;
  if (new_path.empty()) {
    new_path = "/index.html";
  }
  return https_server->GetURL(publisher_key, new_path);
}

void ActivateTabAtIndex(Browser* browser, const int32_t index) {
  DCHECK(browser);
  browser->tab_strip_model()->ActivateTabAt(
      index,
      TabStripModel::UserGestureDetails(TabStripModel::GestureType::kOther));
}

std::string BalanceDoubleToString(double amount) {
  return base::StringPrintf("%.3f", amount);
}

std::string GetUpholdExternalAddress() {
  return "abe5f454-fedd-4ea9-9203-470ae7315bb3";
}

void NavigateToPublisherPage(
    Browser* browser,
    net::EmbeddedTestServer* https_server,
    const std::string& publisher_key,
    const std::string& path) {
  DCHECK(browser && https_server);
  ui_test_utils::NavigateToURLWithDisposition(
      browser,
      GetUrl(https_server, publisher_key, path),
      WindowOpenDisposition::NEW_FOREGROUND_TAB,
      ui_test_utils::BROWSER_TEST_WAIT_FOR_LOAD_STOP);
}

void WaitForLedgerStop(huhi_rewards::RewardsServiceImpl* rewards_service) {
  base::RunLoop run_loop;
  rewards_service->StopLedger(
      base::BindLambdaForTesting([&](const ledger::type::Result) {
        run_loop.Quit();
      }));
  run_loop.Run();
}

}  // namespace rewards_browsertest_util