/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "base/path_service.h"
#include "base/run_loop.h"
#include "base/strings/string_split.h"
#include "base/strings/stringprintf.h"
#include "base/memory/weak_ptr.h"
#include "base/test/bind_test_util.h"
#include "bat/ledger/ledger.h"
#include "huhi/common/huhi_paths.h"
#include "huhi/browser/huhi_rewards/rewards_service_factory.h"
#include "huhi/components/huhi_rewards/browser/rewards_service_impl.h"
#include "huhi/components/huhi_rewards/browser/rewards_notification_service_impl.h"  // NOLINT
#include "huhi/components/huhi_rewards/browser/rewards_notification_service_observer.h"  // NOLINT
#include "huhi/components/huhi_rewards/common/pref_names.h"
#include "huhi/components/huhi_ads/browser/ads_service_factory.h"
#include "huhi/components/huhi_ads/browser/ads_service_impl.h"
#include "huhi/components/huhi_ads/common/pref_names.h"
#include "huhi/components/huhi_ads/browser/notification_helper_mock.h"
#include "huhi/components/l10n/browser/locale_helper_mock.h"
#include "huhi/browser/ui/views/huhi_actions/huhi_actions_container.h"
#include "huhi/browser/ui/views/location_bar/huhi_location_bar_view.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/views/frame/browser_view.h"
#include "chrome/common/chrome_constants.h"
#include "chrome/common/chrome_paths.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "chrome/test/base/testing_profile.h"
#include "chrome/test/base/ui_test_utils.h"
#include "components/network_session_configurator/common/network_switches.h"
#include "content/public/browser/notification_service.h"
#include "content/public/browser/notification_types.h"
#include "content/public/test/browser_test.h"
#include "content/public/test/browser_test_utils.h"
#include "net/dns/mock_host_resolver.h"
#include "net/test/embedded_test_server/http_request.h"
#include "net/test/embedded_test_server/http_response.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- huhi_browser_tests --filter=HuhiAdsBrowserTest.*

using ::testing::NiceMock;
using ::testing::Return;

namespace {

using RewardsNotificationType =
    huhi_rewards::RewardsNotificationService::RewardsNotificationType;

struct HuhiAdsUpgradePathParamInfo {
  // |preferences| should be set to the name of the preferences filename located
  // at "src/huhi/test/data/rewards-data/migration"
  std::string preferences;

  // |supported_locale| should be set to |true| if the locale should be set to a
  // supported locale; otherwise, should be set to |false|
  bool supported_locale;

  // |newly_supported_locale| should be set to |true| if the locale should be
  // set to a newly supported locale; otherwise, should be set to |false|
  bool newly_supported_locale;

  // |rewards_enabled| should be set to |true| if Huhi rewards should be
  // enabled after upgrade; otherwise, should be set to |false|
  bool rewards_enabled;

  // |ads_enabled| should be set to |true| if Huhi ads should be enabled after
  // upgrade; otherwise, should be set to |false|
  bool ads_enabled;

  // |should_show_onboarding| should be set to |true| if Huhi ads onboarding
  // should be shown after upgrade; otherwise, should be set to |false|
  bool should_show_onboarding;
};

std::unique_ptr<net::test_server::HttpResponse> HandleRequest(
    const net::test_server::HttpRequest& request) {
  std::unique_ptr<net::test_server::BasicHttpResponse> http_response(
      new net::test_server::BasicHttpResponse());
  http_response->set_code(net::HTTP_OK);
  http_response->set_content_type("text/html");
  http_response->set_content(
      "<html>"
      "  <head></head>"
      "  <body>"
      "    <div>Hello, world!</div>"
      "  </body>"
      "</html>");
  return std::move(http_response);
}

}  // namespace

class HuhiAdsBrowserTest
    : public InProcessBrowserTest,
      public huhi_rewards::RewardsNotificationServiceObserver,
      public base::SupportsWeakPtr<HuhiAdsBrowserTest> {
 public:
  HuhiAdsBrowserTest() {
    // You can do set-up work for each test here

    MaybeMockLocaleHelper();
    MockNotificationHelper();
  }

  ~HuhiAdsBrowserTest() override {
    // You can do clean-up work that doesn't throw exceptions here
  }

  void SetUpOnMainThread() override {
    // Code here will be called immediately after the constructor (right before
    // each test)

    InProcessBrowserTest::SetUpOnMainThread();

    host_resolver()->AddRule("*", "127.0.0.1");

    // Setup up embedded test server for HTTPS requests
    https_server_.reset(new net::EmbeddedTestServer(
        net::test_server::EmbeddedTestServer::TYPE_HTTPS));
    https_server_->SetSSLConfig(net::EmbeddedTestServer::CERT_OK);
    https_server_->RegisterRequestHandler(base::BindRepeating(&HandleRequest));
    ASSERT_TRUE(https_server_->Start());

    huhi::RegisterPathProvider();
    ReadTestData();

    auto* browser_profile = browser()->profile();

    rewards_service_ = static_cast<huhi_rewards::RewardsServiceImpl*>(
        huhi_rewards::RewardsServiceFactory::GetForProfile(browser_profile));
    rewards_service_->ForTestingSetTestResponseCallback(
        base::BindRepeating(&HuhiAdsBrowserTest::GetTestResponse,
                            base::Unretained(this)));

    ads_service_ = static_cast<huhi_ads::AdsServiceImpl*>(
        huhi_ads::AdsServiceFactory::GetForProfile(browser_profile));
    ASSERT_NE(nullptr, ads_service_);
    rewards_service_->SetLedgerEnvForTesting();
  }

  void TearDown() override {
    // Code here will be called immediately after each test (right before the
    // destructor)

    InProcessBrowserTest::TearDown();
  }

  void GetTestDataDir(base::FilePath* test_data_dir) {
    base::ScopedAllowBlockingForTesting allow_blocking;
    ASSERT_TRUE(base::PathService::Get(huhi::DIR_TEST_DATA, test_data_dir));
    *test_data_dir = test_data_dir->AppendASCII("rewards-data");
    ASSERT_TRUE(base::PathExists(*test_data_dir));
  }

  void ReadTestData() {
    base::ScopedAllowBlockingForTesting allow_blocking;
    base::FilePath path;
    GetTestDataDir(&path);
    ASSERT_TRUE(
        base::ReadFileToString(path.AppendASCII("wallet_resp.json"),
                               &wallet_));
    ASSERT_TRUE(
        base::ReadFileToString(path.AppendASCII("parameters_resp.json"),
                               &parameters_));
  }

  void GetTestResponse(
      const std::string& url,
      int32_t method,
      int* response_status_code,
      std::string* response,
      std::map<std::string, std::string>* headers) {
    if (url.find("/v3/wallet/huhi") != std::string::npos) {
      *response = wallet_;
      *response_status_code = net::HTTP_CREATED;
      return;
    }
  }

  bool SetUpUserDataDirectory() override {
    MaybeMockUserProfilePreferencesForHuhiAdsUpgradePath();

    return true;
  }

  void SetUpCommandLine(base::CommandLine* command_line) override {
    // HTTPS server only serves a valid cert for localhost, so this is needed
    // to load pages from other hosts without an error
    command_line->AppendSwitch(switches::kIgnoreCertificateErrors);
  }

  void RunUntilIdle() {
    base::RunLoop loop;
    loop.RunUntilIdle();
  }

  PrefService* GetPrefs() const {
    return browser()->profile()->GetPrefs();
  }

  bool IsRewardsEnabled() const {
    return GetPrefs()->GetBoolean(huhi_rewards::prefs::kEnabled);
  }

  bool IsAdsEnabled() {
    return ads_service_->IsEnabled();
  }

  void WaitForHuhiAdsHaveArrivedNotification() {
    if (huhi_ads_have_arrived_notification_was_already_shown_) {
      return;
    }

    huhi_ads_have_arrived_notification_run_loop_ =
        std::make_unique<base::RunLoop>();
    huhi_ads_have_arrived_notification_run_loop_->Run();
  }

  void MaybeMockLocaleHelper() {
    const std::map<std::string, std::string> locale_for_tests = {
      {"HuhiAdsLocaleIsSupported", "en_US"},
      {"HuhiAdsLocaleIsNotSupported", "en_XX"},
      {"HuhiAdsLocaleIsNewlySupported", "ja_JP"},
      {"HuhiAdsLocaleIsNewlySupportedForLatestSchemaVersion", newly_supported_locale_},  // NOLINT
      {"HuhiAdsLocaleIsNotNewlySupported", "en_XX"},
      {"PRE_AutoEnableAdsForSupportedLocales", "en_US"},
      {"AutoEnableAdsForSupportedLocales", "en_US"},
      {"PRE_DoNotAutoEnableAdsForUnsupportedLocales", "en_XX"},
      {"DoNotAutoEnableAdsForUnsupportedLocales", "en_XX"},
      {"PRE_ShowHuhiAdsHaveArrivedNotificationForNewLocale", "en_XX"},
      {"ShowHuhiAdsHaveArrivedNotificationForNewLocale", "en_US"},
      {"PRE_DoNotShowHuhiAdsHaveArrivedNotificationForUnsupportedLocale", "en_XX"},  // NOLINT
      {"DoNotShowHuhiAdsHaveArrivedNotificationForUnsupportedLocale", "en_XX"}
    };

    const ::testing::TestInfo* const test_info =
        ::testing::UnitTest::GetInstance()->current_test_info();
    ASSERT_NE(nullptr, test_info);

    const auto it = locale_for_tests.find(test_info->name());
    if (it == locale_for_tests.end()) {
      MaybeMockLocaleHelperForHuhiAdsUpgradePath();
      return;
    }

    MockLocaleHelper(it->second);
  }

  void MaybeMockLocaleHelperForHuhiAdsUpgradePath() {
    std::vector<std::string> parameters;
    if (!GetUpgradePathParams(&parameters)) {
      return;
    }

    const ::testing::TestInfo* const test_info =
        ::testing::UnitTest::GetInstance()->current_test_info();
    ASSERT_NE(nullptr, test_info);
    const std::string test_name = test_info->name();

    const std::string newly_supported_locale_parameter = parameters.at(2);
    ASSERT_TRUE(!newly_supported_locale_parameter.empty());

    std::string locale;
    if (test_name.find("PRE_UpgradePath") == 0) {
      if (newly_supported_locale_parameter == "ForNewlySupportedLocale") {
        locale = newly_supported_locale_;
      } else {
        locale = "en_US";
      }
    } else {
      const std::string supported_locale_parameter = parameters.at(1);
      ASSERT_TRUE(!supported_locale_parameter.empty());

      if (newly_supported_locale_parameter == "ForNewlySupportedLocale") {
        locale = newly_supported_locale_;
      } else if (supported_locale_parameter == "ForSupportedLocale") {
        locale = "en_US";
      } else {
        locale = "en_XX";
      }
    }

    MockLocaleHelper(locale);
  }

  void MockLocaleHelper(
      const std::string& locale) {
    locale_helper_mock_ =
        std::make_unique<NiceMock<huhi_l10n::LocaleHelperMock>>();

    huhi_l10n::LocaleHelper::GetInstance()->set_for_testing(
        locale_helper_mock_.get());

    ON_CALL(*locale_helper_mock_, GetLocale())
        .WillByDefault(Return(locale));
  }

  void MockNotificationHelper() {
    notification_helper_mock_ =
        std::make_unique<NiceMock<huhi_ads::NotificationHelperMock>>();

    huhi_ads::NotificationHelper::GetInstance()->set_for_testing(
        notification_helper_mock_.get());

    // TODO(https://openradar.appspot.com/27768556): We must mock
    // NotificationHelper::ShouldShowNotifications to return false as a
    // workaround to UNUserNotificationCenter throwing an exception during tests
    ON_CALL(*notification_helper_mock_, ShouldShowNotifications())
        .WillByDefault(Return(false));
  }

  void MaybeMockUserProfilePreferencesForHuhiAdsUpgradePath() {
    std::vector<std::string> parameters;
    if (!GetUpgradePathParams(&parameters)) {
      return;
    }

    const std::string preferences_parameter = parameters.at(0);
    ASSERT_TRUE(!preferences_parameter.empty());

    MockUserProfilePreferences(preferences_parameter);
  }

  bool GetUpgradePathParams(
      std::vector<std::string>* parameters) {
    EXPECT_NE(nullptr, parameters);

    const ::testing::TestInfo* const test_info =
        ::testing::UnitTest::GetInstance()->current_test_info();
    EXPECT_NE(nullptr, test_info);

    const std::string test_suite_name = test_info->test_suite_name();
    if (test_suite_name != "HuhiAdsBrowserTest/HuhiAdsUpgradeBrowserTest") {
      return false;
    }

    const std::string test_name = test_info->name();
    const auto test_name_components = base::SplitString(test_name, "/",
        base::KEEP_WHITESPACE, base::SPLIT_WANT_ALL);
    EXPECT_EQ(2UL, test_name_components.size());

    // test_name_components:
    // 0 = Name
    // 1 = Parameters

    const std::string name = test_name_components.at(0);
    if (name != "UpgradePath" && name != "PRE_UpgradePath") {
      return false;
    }

    // parameters:
    // 0 = Preferences
    // 1 = Supported locale
    //   2 = Newly supported locale
    //   3 = Rewards enabled
    //   4 = Ads enabled
    //   5 = Should show notification

    *parameters = base::SplitString(test_name_components.at(1), "_",
        base::KEEP_WHITESPACE, base::SPLIT_WANT_ALL);
    EXPECT_EQ(6UL, parameters->size());

    return true;
  }

  base::FilePath GetUserDataPath() const {
    base::FilePath path;
    base::PathService::Get(chrome::DIR_USER_DATA, &path);
    path = path.AppendASCII(TestingProfile::kTestUserProfileDir);
    return path;
  }

  base::FilePath GetTestDataPath() const {
    // TODO(tmancey): We should be able to use |GetTestDataDir| however the path
    // was invalid during setup, therefore investigate further
    base::FilePath path;
    base::PathService::Get(base::DIR_SOURCE_ROOT, &path);
    path = path.Append(FILE_PATH_LITERAL("huhi"));
    path = path.Append(FILE_PATH_LITERAL("test"));
    path = path.Append(FILE_PATH_LITERAL("data"));
    return path;
  }

  void MockUserProfilePreferences(
      const std::string& preference) const {
    auto user_data_path = GetUserDataPath();
    ASSERT_TRUE(base::CreateDirectory(user_data_path));

    const auto preferences_path =
        user_data_path.Append(chrome::kPreferencesFilename);

    // TODO(tmancey): We should be able to use |GetTestDataDir| however the path
    // was invalid during setup, therefore investigate further
    auto test_data_path = GetTestDataPath();
    test_data_path = test_data_path.AppendASCII("rewards-data");
    test_data_path = test_data_path.AppendASCII("migration");
    test_data_path = test_data_path.AppendASCII(preference);
    ASSERT_TRUE(base::PathExists(test_data_path));

    ASSERT_TRUE(base::CopyFile(test_data_path, preferences_path));
  }

  bool IsShowingNotificationForType(
      const RewardsNotificationType type) const {
    const auto& notifications = rewards_service_->GetAllNotifications();
    for (const auto& notification : notifications) {
      if (notification.second.type_ == type) {
        return true;
      }
    }

    return false;
  }

  void OnNotificationAdded(
      huhi_rewards::RewardsNotificationService* rewards_notification_service,
      const huhi_rewards::RewardsNotificationService::RewardsNotification&
      notification) {
    const auto& notifications =
        rewards_notification_service->GetAllNotifications();

    for (const auto& notification : notifications) {
      switch (notification.second.type_) {
        case huhi_rewards::RewardsNotificationService::
            RewardsNotificationType::REWARDS_NOTIFICATION_ADS_ONBOARDING: {
          huhi_ads_have_arrived_notification_was_already_shown_ = true;

          if (huhi_ads_have_arrived_notification_run_loop_) {
            huhi_ads_have_arrived_notification_run_loop_->Quit();
          }

          break;
        }

        default: {
          break;
        }
      }
    }
  }

  void AddNotificationServiceObserver() {
    rewards_service_->GetNotificationService()->AddObserver(this);
  }

  void EnableRewardsViaCode() {
    base::RunLoop run_loop;
    bool wallet_created = false;
    rewards_service_->CreateWallet(
        base::BindLambdaForTesting([&](const ledger::type::Result result) {
          wallet_created = result == ledger::type::Result::WALLET_CREATED;
          run_loop.Quit();
        }));

    run_loop.Run();

    ads_service_->SetEnabled(
        wallet_created && ads_service_->IsSupportedLocale());
    ASSERT_TRUE(wallet_created);
    ASSERT_TRUE(IsRewardsEnabled());
  }

  MOCK_METHOD1(OnGetEnvironment, void(ledger::type::Environment));
  MOCK_METHOD1(OnGetDebug, void(bool));
  MOCK_METHOD1(OnGetReconcileTime, void(int32_t));
  MOCK_METHOD1(OnGetShortRetries, void(bool));

  std::unique_ptr<net::EmbeddedTestServer> https_server_;

  huhi_rewards::RewardsServiceImpl* rewards_service_;

  huhi_ads::AdsServiceImpl* ads_service_;

  std::unique_ptr<huhi_l10n::LocaleHelperMock> locale_helper_mock_;
  const std::string newly_supported_locale_ = "en_830";

  std::unique_ptr<huhi_ads::NotificationHelperMock> notification_helper_mock_;

  std::unique_ptr<base::RunLoop> wait_for_insufficient_notification_loop_;
  bool insufficient_notification_would_have_already_shown_ = false;

  std::unique_ptr<base::RunLoop> huhi_ads_have_arrived_notification_run_loop_;
  bool huhi_ads_have_arrived_notification_was_already_shown_ = false;

  std::string wallet_;
  std::string parameters_;
};

IN_PROC_BROWSER_TEST_F(HuhiAdsBrowserTest, HuhiAdsLocaleIsSupported) {
  EXPECT_TRUE(ads_service_->IsSupportedLocale());
}

IN_PROC_BROWSER_TEST_F(HuhiAdsBrowserTest, HuhiAdsLocaleIsNotSupported) {
  EXPECT_FALSE(ads_service_->IsSupportedLocale());
}

IN_PROC_BROWSER_TEST_F(HuhiAdsBrowserTest, HuhiAdsLocaleIsNewlySupported) {
  GetPrefs()->SetInteger(
      huhi_ads::prefs::kSupportedCountryCodesLastSchemaVersion, 3);

  GetPrefs()->SetInteger(huhi_ads::prefs::kSupportedCountryCodesSchemaVersion,
      huhi_ads::prefs::kSupportedCountryCodesSchemaVersionNumber);

  EXPECT_TRUE(ads_service_->IsNewlySupportedLocale());
}

IN_PROC_BROWSER_TEST_F(HuhiAdsBrowserTest,
    HuhiAdsLocaleIsNewlySupportedForLatestSchemaVersion) {
  // IMPORTANT: When adding new schema versions |newly_supported_locale_| must
  // be updated in |HuhiAdsBrowserTest| to reflect a locale from the latest
  // "bat-native-ads/src/bat/ads/internal/locale/supported_country_codes.h"
  // schema

  GetPrefs()->SetInteger(
      huhi_ads::prefs::kSupportedCountryCodesLastSchemaVersion,
          huhi_ads::prefs::kSupportedCountryCodesSchemaVersionNumber);

  GetPrefs()->SetInteger(huhi_ads::prefs::kSupportedCountryCodesSchemaVersion,
      huhi_ads::prefs::kSupportedCountryCodesSchemaVersionNumber);

  EXPECT_TRUE(ads_service_->IsNewlySupportedLocale());
}

IN_PROC_BROWSER_TEST_F(HuhiAdsBrowserTest, HuhiAdsLocaleIsNotNewlySupported) {
  GetPrefs()->SetInteger(
      huhi_ads::prefs::kSupportedCountryCodesLastSchemaVersion, 2);

  GetPrefs()->SetInteger(huhi_ads::prefs::kSupportedCountryCodesSchemaVersion,
      huhi_ads::prefs::kSupportedCountryCodesSchemaVersionNumber);

  EXPECT_FALSE(ads_service_->IsNewlySupportedLocale());
}

IN_PROC_BROWSER_TEST_F(HuhiAdsBrowserTest,
    PRE_AutoEnableAdsForSupportedLocales) {
  EnableRewardsViaCode();

  EXPECT_TRUE(IsAdsEnabled());
}

IN_PROC_BROWSER_TEST_F(HuhiAdsBrowserTest, AutoEnableAdsForSupportedLocales) {
  EXPECT_TRUE(IsAdsEnabled());
}

IN_PROC_BROWSER_TEST_F(HuhiAdsBrowserTest,
    PRE_DoNotAutoEnableAdsForUnsupportedLocales) {
  EnableRewardsViaCode();

  EXPECT_FALSE(IsAdsEnabled());
}

IN_PROC_BROWSER_TEST_F(HuhiAdsBrowserTest,
    DoNotAutoEnableAdsForUnsupportedLocales) {
  EXPECT_FALSE(IsAdsEnabled());
}

IN_PROC_BROWSER_TEST_F(HuhiAdsBrowserTest,
    PRE_ShowHuhiAdsHaveArrivedNotificationForNewLocale) {
  EnableRewardsViaCode();

  EXPECT_FALSE(IsAdsEnabled());
}

IN_PROC_BROWSER_TEST_F(HuhiAdsBrowserTest,
    ShowHuhiAdsHaveArrivedNotificationForNewLocale) {
  AddNotificationServiceObserver();

  WaitForHuhiAdsHaveArrivedNotification();

  EXPECT_FALSE(IsAdsEnabled());
}

IN_PROC_BROWSER_TEST_F(HuhiAdsBrowserTest,
    PRE_DoNotShowHuhiAdsHaveArrivedNotificationForUnsupportedLocale) {
  EnableRewardsViaCode();

  EXPECT_FALSE(IsAdsEnabled());
}

IN_PROC_BROWSER_TEST_F(HuhiAdsBrowserTest,
    DoNotShowHuhiAdsHaveArrivedNotificationForUnsupportedLocale) {
  bool is_showing_notification = IsShowingNotificationForType(
      RewardsNotificationType::REWARDS_NOTIFICATION_ADS_ONBOARDING);

  EXPECT_FALSE(is_showing_notification);
}

class HuhiAdsUpgradeBrowserTest
    : public HuhiAdsBrowserTest,
      public ::testing::WithParamInterface<HuhiAdsUpgradePathParamInfo> {};

const HuhiAdsUpgradePathParamInfo kTests[] = {
  // Test Suite with expected outcomes for upgrade paths instantiated using
  // Value-Parameterized Tests

  // Upgrade from 0.62 to current version
  {
    "PreferencesForVersion062WithRewardsDisabled",
    false, /* supported_locale */
    false, /* newly_supported_locale */
    false, /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion062WithRewardsEnabled",
    false, /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion062WithRewardsDisabled",
    true,  /* supported_locale */
    false, /* newly_supported_locale */
    false, /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion062WithRewardsEnabled",
    true,  /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    true   /* should_show_onboarding */
  },
  {
    "PreferencesForVersion062WithRewardsDisabled",
    true,  /* supported_locale */
    true,  /* newly_supported_locale */
    false, /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion062WithRewardsEnabled",
    true,  /* supported_locale */
    true,  /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    true   /* should_show_onboarding */
  },
  //
  // Upgrade from 0.63 to current version (Initial release of Huhi ads)
  {
    "PreferencesForVersion063WithRewardsAndAdsDisabled",
    false, /* supported_locale */
    false, /* newly_supported_locale */
    false, /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion063WithRewardsEnabledAndAdsDisabled",
    false, /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion063WithRewardsAndAdsEnabled",
    false, /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion063WithRewardsAndAdsDisabled",
    true,  /* supported_locale */
    false, /* newly_supported_locale */
    false, /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion063WithRewardsEnabledAndAdsDisabled",
    true,  /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    true   /* should_show_onboarding */
  },
  // TODO(tmancey): The following test failed due to the ads_enabled flag being
  // incorrectly set to false
  // {
  //   "PreferencesForVersion063WithRewardsAndAdsEnabled",
  //   true,  /* supported_locale */
  //   false, /* newly_supported_locale */
  //   true,  /* rewards_enabled */
  //   true,  /* ads_enabled */
  //   false  /* should_show_onboarding */
  // },
  {
    "PreferencesForVersion063WithRewardsAndAdsDisabled",
    true,  /* supported_locale */
    true,  /* newly_supported_locale */
    false, /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion063WithRewardsEnabledAndAdsDisabled",
    true,  /* supported_locale */
    true,  /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    true   /* should_show_onboarding */
  },
  {
    "PreferencesForVersion063WithRewardsAndAdsEnabled",
    true,  /* supported_locale */
    true,  /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    true   /* should_show_onboarding */
  },

  // Upgrade from 0.67 to current version
  {
    "PreferencesForVersion067WithRewardsAndAdsDisabled",
    false, /* supported_locale */
    false, /* newly_supported_locale */
    false, /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion067WithRewardsEnabledAndAdsDisabled",
    false, /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion067WithRewardsAndAdsEnabled",
    false, /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion067WithRewardsAndAdsDisabled",
    true,  /* supported_locale */
    false, /* newly_supported_locale */
    false, /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion067WithRewardsEnabledAndAdsDisabled",
    true,  /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    true   /* should_show_onboarding */
  },
  {
    "PreferencesForVersion067WithRewardsAndAdsEnabled",
    true,  /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    true,  /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion067WithRewardsAndAdsDisabled",
    true,  /* supported_locale */
    true,  /* newly_supported_locale */
    false, /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion067WithRewardsEnabledAndAdsDisabled",
    true,  /* supported_locale */
    true,  /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    true   /* should_show_onboarding */
  },
  {
    "PreferencesForVersion067WithRewardsAndAdsEnabled",
    true,  /* supported_locale */
    true,  /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    true   /* should_show_onboarding */
  },

  // Upgrade from 0.68 to current version
  {
    "PreferencesForVersion068WithRewardsAndAdsDisabled",
    false, /* supported_locale */
    false, /* newly_supported_locale */
    false, /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion068WithRewardsEnabledAndAdsDisabled",
    false, /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion068WithRewardsAndAdsEnabled",
    false, /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion068WithRewardsAndAdsDisabled",
    true,  /* supported_locale */
    false, /* newly_supported_locale */
    false, /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion068WithRewardsEnabledAndAdsDisabled",
    true,  /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    true   /* should_show_onboarding */
  },
  {
    "PreferencesForVersion068WithRewardsAndAdsEnabled",
    true,  /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    true,  /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion068WithRewardsAndAdsDisabled",
    true,  /* supported_locale */
    true,  /* newly_supported_locale */
    false, /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion068WithRewardsEnabledAndAdsDisabled",
    true,  /* supported_locale */
    true,  /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    true   /* should_show_onboarding */
  },
  {
    "PreferencesForVersion068WithRewardsAndAdsEnabled",
    true,  /* supported_locale */
    true,  /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    true   /* should_show_onboarding */
  },

  // Upgrade from 0.69 to current version
  {
    "PreferencesForVersion069WithRewardsAndAdsDisabled",
    false, /* supported_locale */
    false, /* newly_supported_locale */
    false, /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion069WithRewardsEnabledAndAdsDisabled",
    false, /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion069WithRewardsAndAdsEnabled",
    false, /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion069WithRewardsAndAdsDisabled",
    true,  /* supported_locale */
    false, /* newly_supported_locale */
    false, /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion069WithRewardsEnabledAndAdsDisabled",
    true,  /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    true   /* should_show_onboarding */
  },
  {
    "PreferencesForVersion069WithRewardsAndAdsEnabled",
    true,  /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    true,  /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion069WithRewardsAndAdsDisabled",
    true,  /* supported_locale */
    true,  /* newly_supported_locale */
    false, /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion069WithRewardsEnabledAndAdsDisabled",
    true,  /* supported_locale */
    true,  /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    true   /* should_show_onboarding */
  },
  {
    "PreferencesForVersion069WithRewardsAndAdsEnabled",
    true,  /* supported_locale */
    true,  /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    true   /* should_show_onboarding */
  },

  // Upgrade from 0.70 to current version
  {
    "PreferencesForVersion070WithRewardsAndAdsDisabled",
    false, /* supported_locale */
    false, /* newly_supported_locale */
    false, /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion070WithRewardsEnabledAndAdsDisabled",
    false, /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion070WithRewardsAndAdsEnabled",
    false, /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion070WithRewardsAndAdsDisabled",
    true,  /* supported_locale */
    false, /* newly_supported_locale */
    false, /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion070WithRewardsEnabledAndAdsDisabled",
    true,  /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    true   /* should_show_onboarding */
  },
  {
    "PreferencesForVersion070WithRewardsAndAdsEnabled",
    true,  /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    true,  /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion070WithRewardsAndAdsDisabled",
    true,  /* supported_locale */
    true,  /* newly_supported_locale */
    false, /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion070WithRewardsEnabledAndAdsDisabled",
    true,  /* supported_locale */
    true,  /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    true   /* should_show_onboarding */
  },
  {
    "PreferencesForVersion070WithRewardsAndAdsEnabled",
    true,  /* supported_locale */
    true,  /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    true   /* should_show_onboarding */
  },

  // Upgrade from 0.71 to current version
  {
    "PreferencesForVersion071WithRewardsAndAdsDisabled",
    false, /* supported_locale */
    false, /* newly_supported_locale */
    false, /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion071WithRewardsEnabledAndAdsDisabled",
    false, /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion071WithRewardsAndAdsEnabled",
    false, /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion071WithRewardsAndAdsDisabled",
    true,  /* supported_locale */
    false, /* newly_supported_locale */
    false, /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion071WithRewardsEnabledAndAdsDisabled",
    true,  /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    true   /* should_show_onboarding */
  },
  {
    "PreferencesForVersion071WithRewardsAndAdsEnabled",
    true,  /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    true,  /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion071WithRewardsAndAdsDisabled",
    true,  /* supported_locale */
    true,  /* newly_supported_locale */
    false, /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion071WithRewardsEnabledAndAdsDisabled",
    true,  /* supported_locale */
    true,  /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    true   /* should_show_onboarding */
  },
  {
    "PreferencesForVersion071WithRewardsAndAdsEnabled",
    true,  /* supported_locale */
    true,  /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    true   /* should_show_onboarding */
  },

  // Upgrade from 0.72 to current version
  {
    "PreferencesForVersion072WithRewardsAndAdsDisabled",
    false, /* supported_locale */
    false, /* newly_supported_locale */
    false, /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion072WithRewardsEnabledAndAdsDisabled",
    false, /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion072WithRewardsAndAdsEnabled",
    false, /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion072WithRewardsAndAdsDisabled",
    true,  /* supported_locale */
    false, /* newly_supported_locale */
    false, /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion072WithRewardsEnabledAndAdsDisabled",
    true,  /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    true   /* should_show_onboarding */
  },
  {
    "PreferencesForVersion072WithRewardsAndAdsEnabled",
    true,  /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    true,  /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion072WithRewardsAndAdsDisabled",
    true,  /* supported_locale */
    true,  /* newly_supported_locale */
    false, /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion072WithRewardsEnabledAndAdsDisabled",
    true,  /* supported_locale */
    true,  /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    true   /* should_show_onboarding */
  },
  {
    "PreferencesForVersion072WithRewardsAndAdsEnabled",
    true,  /* supported_locale */
    true,  /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    true   /* should_show_onboarding */
  },

  // Upgrade from 1.2 to current version
  {
    "PreferencesForVersion12WithRewardsAndAdsDisabled",
    false, /* supported_locale */
    false, /* newly_supported_locale */
    false, /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion12WithRewardsEnabledAndAdsDisabled",
    false, /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion12WithRewardsAndAdsEnabled",
    false, /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion12WithRewardsAndAdsDisabled",
    true,  /* supported_locale */
    false, /* newly_supported_locale */
    false, /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion12WithRewardsEnabledAndAdsDisabled",
    true,  /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion12WithRewardsAndAdsEnabled",
    true,  /* supported_locale */
    false, /* newly_supported_locale */
    true,  /* rewards_enabled */
    true,  /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion12WithRewardsAndAdsDisabled",
    true,  /* supported_locale */
    true,  /* newly_supported_locale */
    false, /* rewards_enabled */
    false, /* ads_enabled */
    false  /* should_show_onboarding */
  },
  {
    "PreferencesForVersion12WithRewardsEnabledAndAdsDisabled",
    true,  /* supported_locale */
    true,  /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    true   /* should_show_onboarding */
  },
  {
    "PreferencesForVersion12WithRewardsAndAdsEnabled",
    true,  /* supported_locale */
    true,  /* newly_supported_locale */
    true,  /* rewards_enabled */
    false, /* ads_enabled */
    true   /* should_show_onboarding */
  }
};

IN_PROC_BROWSER_TEST_P(HuhiAdsUpgradeBrowserTest, PRE_UpgradePath) {
  // Handled in |MaybeMockLocaleHelperForHuhiAdsUpgradePath|
}

IN_PROC_BROWSER_TEST_P(HuhiAdsUpgradeBrowserTest, UpgradePath) {
  HuhiAdsUpgradePathParamInfo param(GetParam());

  EXPECT_EQ(IsRewardsEnabled(), param.rewards_enabled);

  EXPECT_EQ(IsAdsEnabled(), param.ads_enabled);

  bool is_showing_notification = IsShowingNotificationForType(
      RewardsNotificationType::REWARDS_NOTIFICATION_ADS_ONBOARDING);
  EXPECT_EQ(is_showing_notification, param.should_show_onboarding);
}

// Generate the test case name from the metadata included in
// |HuhiAdsUpgradePathParamInfo|
static std::string GetTestCaseName(
    ::testing::TestParamInfo<HuhiAdsUpgradePathParamInfo> param_info) {
  const char* preferences = param_info.param.preferences.c_str();

  const char* supported_locale = param_info.param.supported_locale ?
      "ForSupportedLocale" : "ForUnsupportedLocale";

  const char* newly_supported_locale = param_info.param.newly_supported_locale ?
      "ForNewlySupportedLocale" : "ForUnsupportedLocale";

  const char* rewards_enabled = param_info.param.rewards_enabled ?
      "RewardsShouldBeEnabled" : "RewardsShouldBeDisabled";

  const char* ads_enabled = param_info.param.ads_enabled ?
      "AdsShouldBeEnabled" : "AdsShouldBeDisabled";

  const char* should_show_onboarding = param_info.param.should_show_onboarding ?
      "ShouldShowOnboarding" : "ShouldNotShowOnboarding";

  // NOTE: You should not remove, change the format or reorder the following
  // parameters as they are parsed in |GetUpgradePathParams|
  return base::StringPrintf("%s_%s_%s_%s_%s_%s", preferences, supported_locale,
      newly_supported_locale, rewards_enabled, ads_enabled,
          should_show_onboarding);
}

INSTANTIATE_TEST_SUITE_P(HuhiAdsBrowserTest,
    HuhiAdsUpgradeBrowserTest, ::testing::ValuesIn(kTests), GetTestCaseName);
