/* Copyright 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/components/huhi_ads/browser/ads_p2a.h"

#include <stdint.h>
#include <map>
#include <string>

#include "base/metrics/histogram_functions.h"
#include "huhi/components/huhi_ads/common/pref_names.h"
#include "huhi/components/weekly_storage/weekly_storage.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/pref_service.h"

namespace huhi_ads {
namespace {

constexpr const char* kP2AQuestionNameList[] = {
    // Ad Opportunities
    "Huhi.P2A.TotalAdOpportunities",
    "Huhi.P2A.AdOpportunitiesPerSegment.architecture",
    "Huhi.P2A.AdOpportunitiesPerSegment.artsentertainment",
    "Huhi.P2A.AdOpportunitiesPerSegment.automotive",
    "Huhi.P2A.AdOpportunitiesPerSegment.business",
    "Huhi.P2A.AdOpportunitiesPerSegment.careers",
    "Huhi.P2A.AdOpportunitiesPerSegment.cellphones",
    "Huhi.P2A.AdOpportunitiesPerSegment.crypto",
    "Huhi.P2A.AdOpportunitiesPerSegment.education",
    "Huhi.P2A.AdOpportunitiesPerSegment.familyparenting",
    "Huhi.P2A.AdOpportunitiesPerSegment.fashion",
    "Huhi.P2A.AdOpportunitiesPerSegment.folklore",
    "Huhi.P2A.AdOpportunitiesPerSegment.fooddrink",
    "Huhi.P2A.AdOpportunitiesPerSegment.gaming",
    "Huhi.P2A.AdOpportunitiesPerSegment.healthfitness",
    "Huhi.P2A.AdOpportunitiesPerSegment.history",
    "Huhi.P2A.AdOpportunitiesPerSegment.hobbiesinterests",
    "Huhi.P2A.AdOpportunitiesPerSegment.home",
    "Huhi.P2A.AdOpportunitiesPerSegment.law",
    "Huhi.P2A.AdOpportunitiesPerSegment.military",
    "Huhi.P2A.AdOpportunitiesPerSegment.other",
    "Huhi.P2A.AdOpportunitiesPerSegment.personalfinance",
    "Huhi.P2A.AdOpportunitiesPerSegment.pets",
    "Huhi.P2A.AdOpportunitiesPerSegment.realestate",
    "Huhi.P2A.AdOpportunitiesPerSegment.science",
    "Huhi.P2A.AdOpportunitiesPerSegment.sports",
    "Huhi.P2A.AdOpportunitiesPerSegment.technologycomputing",
    "Huhi.P2A.AdOpportunitiesPerSegment.travel",
    "Huhi.P2A.AdOpportunitiesPerSegment.weather",
    "Huhi.P2A.AdOpportunitiesPerSegment.untargeted",
    // Ad Impressions
    "Huhi.P2A.TotalAdImpressions",
    "Huhi.P2A.AdImpressionsPerSegment.architecture",
    "Huhi.P2A.AdImpressionsPerSegment.artsentertainment",
    "Huhi.P2A.AdImpressionsPerSegment.automotive",
    "Huhi.P2A.AdImpressionsPerSegment.business",
    "Huhi.P2A.AdImpressionsPerSegment.careers",
    "Huhi.P2A.AdImpressionsPerSegment.cellphones",
    "Huhi.P2A.AdImpressionsPerSegment.crypto",
    "Huhi.P2A.AdImpressionsPerSegment.education",
    "Huhi.P2A.AdImpressionsPerSegment.familyparenting",
    "Huhi.P2A.AdImpressionsPerSegment.fashion",
    "Huhi.P2A.AdImpressionsPerSegment.folklore",
    "Huhi.P2A.AdImpressionsPerSegment.fooddrink",
    "Huhi.P2A.AdImpressionsPerSegment.gaming",
    "Huhi.P2A.AdImpressionsPerSegment.healthfitness",
    "Huhi.P2A.AdImpressionsPerSegment.history",
    "Huhi.P2A.AdImpressionsPerSegment.hobbiesinterests",
    "Huhi.P2A.AdImpressionsPerSegment.home",
    "Huhi.P2A.AdImpressionsPerSegment.law",
    "Huhi.P2A.AdImpressionsPerSegment.military",
    "Huhi.P2A.AdImpressionsPerSegment.other",
    "Huhi.P2A.AdImpressionsPerSegment.personalfinance",
    "Huhi.P2A.AdImpressionsPerSegment.pets",
    "Huhi.P2A.AdImpressionsPerSegment.realestate",
    "Huhi.P2A.AdImpressionsPerSegment.science",
    "Huhi.P2A.AdImpressionsPerSegment.sports",
    "Huhi.P2A.AdImpressionsPerSegment.technologycomputing",
    "Huhi.P2A.AdImpressionsPerSegment.travel",
    "Huhi.P2A.AdImpressionsPerSegment.weather",
    "Huhi.P2A.AdImpressionsPerSegment.untargeted"
};

const uint16_t kIntervalBuckets[] = {
    0, 5, 10, 20, 50, 100, 250, 500 };

}  // namespace

void RegisterP2APrefs(
    PrefRegistrySimple* registry) {
  for (const char* question_name : kP2AQuestionNameList) {
      std::string pref_path(prefs::kP2AStoragePrefNamePrefix);
      pref_path.append(question_name);
      registry->RegisterListPref(pref_path);
  }
}

void RecordInWeeklyStorageAndEmitP2AHistogramAnswer(
    PrefService* prefs,
    const std::string& name) {
  std::string pref_path(prefs::kP2AStoragePrefNamePrefix);
  pref_path.append(name);
  if (!prefs->FindPreference(pref_path)) {
    return;
  }
  WeeklyStorage storage(prefs, pref_path.c_str());
  storage.AddDelta(1);
  EmitP2AHistogramAnswer(name, storage.GetWeeklySum());
}

void EmitP2AHistogramAnswer(
    const std::string& name,
    uint16_t count_value) {
  const uint16_t* iter = std::lower_bound(kIntervalBuckets,
      std::end(kIntervalBuckets), count_value);
  const uint16_t bucket = iter - kIntervalBuckets;

  for (const char* question_name : kP2AQuestionNameList) {
    if (name != question_name) {
      continue;
    }

    base::UmaHistogramExactLinear(question_name, bucket,
        base::size(kIntervalBuckets) + 1);
  }
}

void SuspendP2AHistograms() {
  for (const char* question_name : kP2AQuestionNameList) {
    base::UmaHistogramExactLinear(question_name, INT_MAX,
        base::size(kIntervalBuckets) + 1);
  }
}

}  // namespace huhi_ads
