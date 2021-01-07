// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stddef.h>

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

#include "base/command_line.h"
#include "base/files/scoped_temp_dir.h"
#include "base/macros.h"
#include "base/stl_util.h"
#include "base/strings/utf_string_conversions.h"
#include "base/values.h"
#include "huhi/common/pref_names.h"
#include "huhi/components/search_engines/huhi_prepopulated_engines.h"
#include "components/google/core/common/google_switches.h"
#include "components/search_engines/search_engines_pref_names.h"
#include "components/search_engines/search_terms_data.h"
#include "components/search_engines/template_url.h"
#include "components/search_engines/template_url_data_util.h"
#include "components/search_engines/template_url_prepopulate_data.h"
#include "components/search_engines/template_url_service.h"
#include "components/search_engines/testing_search_terms_data.h"
#include "components/sync_preferences/testing_pref_service_syncable.h"
#include "testing/gtest/include/gtest/gtest.h"

using base::ASCIIToUTF16;

namespace {

const char kCountryIDAtInstall[] = "countryid_at_install";

std::string GetHostFromTemplateURLData(const TemplateURLData& data) {
  return TemplateURL(data).url_ref().GetHost(SearchTermsData());
}

using namespace TemplateURLPrepopulateData;  // NOLINT

const PrepopulatedEngine* const kHuhiAddedEngines[] = {
    &startpage,
};

const std::unordered_set<std::wstring> kOverriddenEnginesNames = {L"DuckDuckGo",
                                                                  L"Qwant"};

std::vector<const PrepopulatedEngine*> GetAllPrepopulatedEngines() {
  std::vector<const PrepopulatedEngine*> engines =
      TemplateURLPrepopulateData::GetAllPrepopulatedEngines();
  engines.insert(engines.end(), std::begin(kHuhiAddedEngines),
                 std::end(kHuhiAddedEngines));
  return engines;
}

}  // namespace

class HuhiTemplateURLPrepopulateDataTest : public testing::Test {
 public:
  void SetUp() override {
    TemplateURLPrepopulateData::RegisterProfilePrefs(prefs_.registry());
    // Real registration happens in `huhi/browser/huhi_profile_prefs.cc`
    // Calling huhi::RegisterProfilePrefs() causes some problems though
    auto* registry = prefs_.registry();
    registry->RegisterIntegerPref(
        kHuhiDefaultSearchVersion,
        TemplateURLPrepopulateData::kHuhiCurrentDataVersion);
  }

  void CheckForCountry(char digit1, char digit2, const std::string& expected) {
    prefs_.SetInteger(kCountryIDAtInstall, digit1 << 8 | digit2);
    prefs_.SetInteger(kHuhiDefaultSearchVersion,
                      TemplateURLPrepopulateData::kHuhiCurrentDataVersion);
    size_t default_index;
    std::vector<std::unique_ptr<TemplateURLData>> t_urls =
        TemplateURLPrepopulateData::GetPrepopulatedEngines(&prefs_,
                                                           &default_index);
    EXPECT_EQ(ASCIIToUTF16(expected), t_urls[default_index]->short_name());
  }

 protected:
  sync_preferences::TestingPrefServiceSyncable prefs_;
};

// Verifies that the set of all prepopulate data doesn't contain entries with
// duplicate keywords. This should make us notice if Chromium adds a search
// engine in the future that Huhi already added.
TEST_F(HuhiTemplateURLPrepopulateDataTest, UniqueKeywords) {
  using PrepopulatedEngine = TemplateURLPrepopulateData::PrepopulatedEngine;
  const std::vector<const PrepopulatedEngine*> all_engines =
      ::GetAllPrepopulatedEngines();
  std::set<std::wstring> unique_keywords;
  for (const PrepopulatedEngine* engine : all_engines) {
    ASSERT_TRUE(unique_keywords.find(engine->keyword) == unique_keywords.end());
    unique_keywords.insert(engine->keyword);
  }
}

// Verifies that engines we override are used and not the original engines.
TEST_F(HuhiTemplateURLPrepopulateDataTest, OverriddenEngines) {
  using PrepopulatedEngine = TemplateURLPrepopulateData::PrepopulatedEngine;
  const std::vector<const PrepopulatedEngine*> all_engines =
      ::GetAllPrepopulatedEngines();
  for (const PrepopulatedEngine* engine : all_engines) {
    if (kOverriddenEnginesNames.count(engine->name) > 0)
      ASSERT_GE(static_cast<unsigned int>(engine->id),
                TemplateURLPrepopulateData::HUHI_PREPOPULATED_ENGINES_START);
  }
}

// Verifies that the set of prepopulate data for each locale
// doesn't contain entries with duplicate ids.
TEST_F(HuhiTemplateURLPrepopulateDataTest, UniqueIDs) {
  const int kCountryIds[] = {'D' << 8 | 'E', 'F' << 8 | 'R', 'U' << 8 | 'S',
                             -1};

  for (size_t i = 0; i < base::size(kCountryIds); ++i) {
    prefs_.SetInteger(kCountryIDAtInstall, kCountryIds[i]);
    std::vector<std::unique_ptr<TemplateURLData>> urls =
        GetPrepopulatedEngines(&prefs_, nullptr);
    std::set<int> unique_ids;
    for (size_t turl_i = 0; turl_i < urls.size(); ++turl_i) {
      ASSERT_TRUE(unique_ids.find(urls[turl_i]->prepopulate_id) ==
                  unique_ids.end());
      unique_ids.insert(urls[turl_i]->prepopulate_id);
    }
  }
}

// Verifies that each prepopulate data entry has required fields
TEST_F(HuhiTemplateURLPrepopulateDataTest, ProvidersFromPrepopulated) {
  size_t default_index;
  std::vector<std::unique_ptr<TemplateURLData>> t_urls =
      TemplateURLPrepopulateData::GetPrepopulatedEngines(&prefs_,
                                                         &default_index);

  // Ensure all the URLs have the required fields populated.
  ASSERT_FALSE(t_urls.empty());
  for (size_t i = 0; i < t_urls.size(); ++i) {
    ASSERT_FALSE(t_urls[i]->short_name().empty());
    ASSERT_FALSE(t_urls[i]->keyword().empty());
    ASSERT_FALSE(t_urls[i]->favicon_url.host().empty());
    ASSERT_FALSE(GetHostFromTemplateURLData(*t_urls[i]).empty());
    ASSERT_FALSE(t_urls[i]->input_encodings.empty());
    EXPECT_GT(t_urls[i]->prepopulate_id, 0);
    EXPECT_TRUE(t_urls[0]->safe_for_autoreplace);
    EXPECT_TRUE(t_urls[0]->date_created.is_null());
    EXPECT_TRUE(t_urls[0]->last_modified.is_null());
  }
}

// Verifies default search provider for locale
TEST_F(HuhiTemplateURLPrepopulateDataTest, DefaultSearchProvidersForUSA) {
  CheckForCountry('U', 'S', "Google");
}

TEST_F(HuhiTemplateURLPrepopulateDataTest, DefaultSearchProvidersForGermany) {
  CheckForCountry('D', 'E', "DuckDuckGo");
}

TEST_F(HuhiTemplateURLPrepopulateDataTest, DefaultSearchProvidersForFrance) {
  CheckForCountry('F', 'R', "Qwant");
}

TEST_F(HuhiTemplateURLPrepopulateDataTest,
       DefaultSearchProvidersForAustralia) {
  CheckForCountry('A', 'U', "DuckDuckGo");
}

TEST_F(HuhiTemplateURLPrepopulateDataTest,
       DefaultSearchProvidersForNewZealand) {
  CheckForCountry('N', 'Z', "DuckDuckGo");
}

TEST_F(HuhiTemplateURLPrepopulateDataTest, DefaultSearchProvidersForIreland) {
  CheckForCountry('I', 'E', "DuckDuckGo");
}

TEST_F(HuhiTemplateURLPrepopulateDataTest,
       DefaultSearchProvidersForRepublicOfArmenia) {
  CheckForCountry('A', 'M', "Yandex");
}

TEST_F(HuhiTemplateURLPrepopulateDataTest,
       DefaultSearchProvidersForRepublicOfAzerbaijan) {
  CheckForCountry('A', 'Z', "Yandex");
}

TEST_F(HuhiTemplateURLPrepopulateDataTest,
       DefaultSearchProvidersForRepublicOfBelarus) {
  CheckForCountry('B', 'Y', "Yandex");
}

TEST_F(HuhiTemplateURLPrepopulateDataTest,
       DefaultSearchProvidersForKyrgyzRepublic) {
  CheckForCountry('K', 'G', "Yandex");
}

TEST_F(HuhiTemplateURLPrepopulateDataTest,
       DefaultSearchProvidersForRepublicOfKazakhstan) {
  CheckForCountry('K', 'Z', "Yandex");
}

TEST_F(HuhiTemplateURLPrepopulateDataTest,
       DefaultSearchProvidersForRepublicOfMoldova) {
  CheckForCountry('M', 'D', "Yandex");
}

TEST_F(HuhiTemplateURLPrepopulateDataTest,
       DefaultSearchProvidersForRussianFederation) {
  CheckForCountry('R', 'U', "Yandex");
}

TEST_F(HuhiTemplateURLPrepopulateDataTest,
       DefaultSearchProvidersForRepublicOfTajikistan) {
  CheckForCountry('T', 'J', "Yandex");
}

TEST_F(HuhiTemplateURLPrepopulateDataTest,
       DefaultSearchProvidersForTurkmenistan) {
  CheckForCountry('T', 'M', "Yandex");
}

TEST_F(HuhiTemplateURLPrepopulateDataTest,
       DefaultSearchProvidersForRepublicOfUzbekistan) {
  CheckForCountry('U', 'Z', "Yandex");
}
