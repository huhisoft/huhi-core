/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "base/stl_util.h"
#include "base/strings/utf_string_conversions.h"
#include "components/country_codes/country_codes.h"

// Pull in definitions for Huhi prepopulated engines. It's ugly but these need
// to be built as part of the search_engines static library.
#include "../../../components/search_engines/huhi_prepopulated_engines.cc"  // NOLINT
#include "../../../components/search_engines/huhi_prepopulated_engines.h"

#define GetDataVersion GetDataVersion_ChromiumImpl
#define GetEngineType GetEngineType_ChromiumImpl
#if defined(OS_ANDROID)
#define GetLocalPrepopulatedEngines GetLocalPrepopulatedEngines_Unused
#endif
#define GetPrepopulatedDefaultSearch GetPrepopulatedDefaultSearch_Unused
#define GetPrepopulatedEngine GetPrepopulatedEngine_Unused
#define GetPrepopulatedEngines GetPrepopulatedEngines_Unused
#include "../../../../components/search_engines/template_url_prepopulate_data.cc"  // NOLINT
#undef GetDataVersion
#undef GetEngineType
#if defined(OS_ANDROID)
#undef GetLocalPrepopulatedEngines
#endif
#undef GetPrepopulatedDefaultSearch
#undef GetPrepopulatedEngine
#undef GetPrepopulatedEngines

namespace TemplateURLPrepopulateData {

void LocalizeEngineList(
    int country_id, std::vector<HuhiPrepopulatedEngineID>* engines);

namespace {

// Maps HuhiPrepopulatedEngineID to Chromium's PrepopulatedEngine.
const std::map<HuhiPrepopulatedEngineID, const PrepopulatedEngine*>
    huhi_engines_map = {
        {PREPOPULATED_ENGINE_ID_GOOGLE, &google},
        {PREPOPULATED_ENGINE_ID_YAHOO, &huhi_yahoo},
        {PREPOPULATED_ENGINE_ID_YAHOO_AR, &huhi_yahoo_ar},
        {PREPOPULATED_ENGINE_ID_YAHOO_AT, &huhi_yahoo_at},
        {PREPOPULATED_ENGINE_ID_YAHOO_AU, &huhi_yahoo_au},
        {PREPOPULATED_ENGINE_ID_YAHOO_BR, &huhi_yahoo_br},
        {PREPOPULATED_ENGINE_ID_YAHOO_CA, &huhi_yahoo_ca},
        {PREPOPULATED_ENGINE_ID_YAHOO_CH, &huhi_yahoo_ch},
        {PREPOPULATED_ENGINE_ID_YAHOO_CL, &huhi_yahoo_cl},
        {PREPOPULATED_ENGINE_ID_YAHOO_CO, &huhi_yahoo_co},
        {PREPOPULATED_ENGINE_ID_YAHOO_DE, &huhi_yahoo_de},
        {PREPOPULATED_ENGINE_ID_YAHOO_DK, &huhi_yahoo_dk},
        {PREPOPULATED_ENGINE_ID_YAHOO_ES, &huhi_yahoo_es},
        {PREPOPULATED_ENGINE_ID_YAHOO_FI, &huhi_yahoo_fi},
        {PREPOPULATED_ENGINE_ID_YAHOO_FR, &huhi_yahoo_fr},
        {PREPOPULATED_ENGINE_ID_YAHOO_HK, &huhi_yahoo_hk},
        {PREPOPULATED_ENGINE_ID_YAHOO_ID, &huhi_yahoo_id},
        {PREPOPULATED_ENGINE_ID_YAHOO_IE, &huhi_yahoo_ie},
        {PREPOPULATED_ENGINE_ID_YAHOO_IN, &huhi_yahoo_in},
        {PREPOPULATED_ENGINE_ID_YAHOO_IT, &huhi_yahoo_it},
        {PREPOPULATED_ENGINE_ID_YAHOO_MX, &huhi_yahoo_mx},
        {PREPOPULATED_ENGINE_ID_YAHOO_MY, &huhi_yahoo_my},
        {PREPOPULATED_ENGINE_ID_YAHOO_NL, &huhi_yahoo_nl},
        {PREPOPULATED_ENGINE_ID_YAHOO_NO, &huhi_yahoo_no},
        {PREPOPULATED_ENGINE_ID_YAHOO_NZ, &huhi_yahoo_nz},
        {PREPOPULATED_ENGINE_ID_YAHOO_PE, &huhi_yahoo_pe},
        {PREPOPULATED_ENGINE_ID_YAHOO_PH, &huhi_yahoo_ph},
        {PREPOPULATED_ENGINE_ID_YAHOO_SE, &huhi_yahoo_se},
        {PREPOPULATED_ENGINE_ID_YAHOO_SG, &huhi_yahoo_sg},
        {PREPOPULATED_ENGINE_ID_YAHOO_TH, &huhi_yahoo_th},
        {PREPOPULATED_ENGINE_ID_YAHOO_TW, &huhi_yahoo_tw},
        {PREPOPULATED_ENGINE_ID_YAHOO_UK, &huhi_yahoo_uk},
        {PREPOPULATED_ENGINE_ID_YAHOO_VE, &huhi_yahoo_ve},
        {PREPOPULATED_ENGINE_ID_YAHOO_VN, &huhi_yahoo_vn},
        {PREPOPULATED_ENGINE_ID_BING, &bing},
        {PREPOPULATED_ENGINE_ID_DUCKDUCKGO, &duckduckgo},
        {PREPOPULATED_ENGINE_ID_DUCKDUCKGO_DE, &duckduckgo_de},
        {PREPOPULATED_ENGINE_ID_DUCKDUCKGO_AU_NZ_IE, &duckduckgo_au_nz_ie},
        {PREPOPULATED_ENGINE_ID_QWANT, &qwant},
        {PREPOPULATED_ENGINE_ID_STARTPAGE, &startpage},
};

// Default order in which engines will appear in the UI.
const std::vector<HuhiPrepopulatedEngineID> huhi_engines_default = {
    PREPOPULATED_ENGINE_ID_GOOGLE,
    PREPOPULATED_ENGINE_ID_DUCKDUCKGO,
    PREPOPULATED_ENGINE_ID_QWANT,
    PREPOPULATED_ENGINE_ID_BING,
    PREPOPULATED_ENGINE_ID_STARTPAGE,
};

// Variations of the order / default options by country.
const std::vector<HuhiPrepopulatedEngineID> huhi_engines_with_yahoo = {
    PREPOPULATED_ENGINE_ID_YAHOO,
    PREPOPULATED_ENGINE_ID_GOOGLE,
    PREPOPULATED_ENGINE_ID_DUCKDUCKGO,
    PREPOPULATED_ENGINE_ID_QWANT,
    PREPOPULATED_ENGINE_ID_BING,
    PREPOPULATED_ENGINE_ID_STARTPAGE,
};

const std::vector<HuhiPrepopulatedEngineID> huhi_engines_DE = {
    PREPOPULATED_ENGINE_ID_YAHOO,
    PREPOPULATED_ENGINE_ID_DUCKDUCKGO_DE,
    PREPOPULATED_ENGINE_ID_QWANT,
    PREPOPULATED_ENGINE_ID_GOOGLE,
    PREPOPULATED_ENGINE_ID_BING,
    PREPOPULATED_ENGINE_ID_STARTPAGE,
};

const std::vector<HuhiPrepopulatedEngineID> huhi_engines_FR = {
    PREPOPULATED_ENGINE_ID_YAHOO,
    PREPOPULATED_ENGINE_ID_QWANT,
    PREPOPULATED_ENGINE_ID_GOOGLE,
    PREPOPULATED_ENGINE_ID_DUCKDUCKGO,
    PREPOPULATED_ENGINE_ID_BING,
    PREPOPULATED_ENGINE_ID_STARTPAGE,
};

const std::vector<HuhiPrepopulatedEngineID> huhi_engines_AU_NZ_IE = {
    PREPOPULATED_ENGINE_ID_YAHOO,
    PREPOPULATED_ENGINE_ID_DUCKDUCKGO_AU_NZ_IE,
    PREPOPULATED_ENGINE_ID_GOOGLE,
    PREPOPULATED_ENGINE_ID_QWANT,
    PREPOPULATED_ENGINE_ID_BING,
    PREPOPULATED_ENGINE_ID_STARTPAGE};

// A map to keep track of a full list of default engines for countries
// that don't use the default list.
const std::map<int, const std::vector<HuhiPrepopulatedEngineID>*>
    default_engines_by_country_id_map = {
        {country_codes::CountryCharsToCountryID('A', 'R'),
         &huhi_engines_with_yahoo},
        {country_codes::CountryCharsToCountryID('A', 'T'),
         &huhi_engines_with_yahoo},
        {country_codes::CountryCharsToCountryID('A', 'U'),
         &huhi_engines_AU_NZ_IE},
        {country_codes::CountryCharsToCountryID('B', 'R'),
         &huhi_engines_with_yahoo},
        {country_codes::CountryCharsToCountryID('C', 'A'),
         &huhi_engines_with_yahoo},
        {country_codes::CountryCharsToCountryID('C', 'H'),
         &huhi_engines_with_yahoo},
        {country_codes::CountryCharsToCountryID('C', 'L'),
         &huhi_engines_with_yahoo},
        {country_codes::CountryCharsToCountryID('C', 'O'),
         &huhi_engines_with_yahoo},
        {country_codes::CountryCharsToCountryID('D', 'E'),
         &huhi_engines_DE},
        {country_codes::CountryCharsToCountryID('D', 'K'),
         &huhi_engines_with_yahoo},
        {country_codes::CountryCharsToCountryID('E', 'S'),
         &huhi_engines_with_yahoo},
        {country_codes::CountryCharsToCountryID('F', 'I'),
         &huhi_engines_with_yahoo},
        {country_codes::CountryCharsToCountryID('F', 'R'),
         &huhi_engines_FR},
        {country_codes::CountryCharsToCountryID('G', 'B'),
         &huhi_engines_with_yahoo},
        {country_codes::CountryCharsToCountryID('H', 'K'),
         &huhi_engines_with_yahoo},
        {country_codes::CountryCharsToCountryID('I', 'D'),
         &huhi_engines_with_yahoo},
        {country_codes::CountryCharsToCountryID('I', 'E'),
         &huhi_engines_AU_NZ_IE},
        {country_codes::CountryCharsToCountryID('I', 'N'),
         &huhi_engines_with_yahoo},
        {country_codes::CountryCharsToCountryID('I', 'T'),
         &huhi_engines_with_yahoo},
        {country_codes::CountryCharsToCountryID('M', 'X'),
         &huhi_engines_with_yahoo},
        {country_codes::CountryCharsToCountryID('M', 'Y'),
         &huhi_engines_with_yahoo},
        {country_codes::CountryCharsToCountryID('N', 'L'),
         &huhi_engines_with_yahoo},
        {country_codes::CountryCharsToCountryID('N', 'O'),
         &huhi_engines_with_yahoo},
        {country_codes::CountryCharsToCountryID('N', 'Z'),
         &huhi_engines_AU_NZ_IE},
        {country_codes::CountryCharsToCountryID('P', 'E'),
         &huhi_engines_with_yahoo},
        {country_codes::CountryCharsToCountryID('P', 'H'),
         &huhi_engines_with_yahoo},
        {country_codes::CountryCharsToCountryID('S', 'E'),
         &huhi_engines_with_yahoo},
        {country_codes::CountryCharsToCountryID('S', 'G'),
         &huhi_engines_with_yahoo},
        {country_codes::CountryCharsToCountryID('T', 'H'),
         &huhi_engines_with_yahoo},
        {country_codes::CountryCharsToCountryID('T', 'W'),
         &huhi_engines_with_yahoo},
        {country_codes::CountryCharsToCountryID('U', 'S'),
         &huhi_engines_with_yahoo},
        {country_codes::CountryCharsToCountryID('V', 'E'),
         &huhi_engines_with_yahoo},
        {country_codes::CountryCharsToCountryID('V', 'N'),
         &huhi_engines_with_yahoo}};

// Default search engine. Overridable on a per-country basis.
const HuhiPrepopulatedEngineID default_engine =
    PREPOPULATED_ENGINE_ID_GOOGLE;

// A map tracking the singular default search engine per-country.
const std::map<int, HuhiPrepopulatedEngineID>
    default_engine_by_country_id_map = {
        {country_codes::CountryCharsToCountryID('A', 'U'),
         PREPOPULATED_ENGINE_ID_DUCKDUCKGO_AU_NZ_IE},
        {country_codes::CountryCharsToCountryID('F', 'R'),
         PREPOPULATED_ENGINE_ID_QWANT},
        {country_codes::CountryCharsToCountryID('D', 'E'),
         PREPOPULATED_ENGINE_ID_DUCKDUCKGO_DE},
        {country_codes::CountryCharsToCountryID('I', 'E'),
         PREPOPULATED_ENGINE_ID_DUCKDUCKGO_AU_NZ_IE},
        {country_codes::CountryCharsToCountryID('N', 'Z'),
         PREPOPULATED_ENGINE_ID_DUCKDUCKGO_AU_NZ_IE}};

// A map to keep track of country-specific implementations of Yahoo.
// Used in LocalizeEngineList.
const std::map<int, HuhiPrepopulatedEngineID>
    yahoo_engines_by_country_id_map = {
        {country_codes::CountryCharsToCountryID('A', 'R'),
         PREPOPULATED_ENGINE_ID_YAHOO_AR},
        {country_codes::CountryCharsToCountryID('A', 'T'),
         PREPOPULATED_ENGINE_ID_YAHOO_AT},
        {country_codes::CountryCharsToCountryID('A', 'U'),
         PREPOPULATED_ENGINE_ID_YAHOO_AU},
        {country_codes::CountryCharsToCountryID('B', 'R'),
         PREPOPULATED_ENGINE_ID_YAHOO_BR},
        {country_codes::CountryCharsToCountryID('C', 'A'),
         PREPOPULATED_ENGINE_ID_YAHOO_CA},
        {country_codes::CountryCharsToCountryID('C', 'H'),
         PREPOPULATED_ENGINE_ID_YAHOO_CH},
        {country_codes::CountryCharsToCountryID('C', 'L'),
         PREPOPULATED_ENGINE_ID_YAHOO_CL},
        {country_codes::CountryCharsToCountryID('C', 'O'),
         PREPOPULATED_ENGINE_ID_YAHOO_CO},
        {country_codes::CountryCharsToCountryID('D', 'E'),
         PREPOPULATED_ENGINE_ID_YAHOO_DE},
        {country_codes::CountryCharsToCountryID('D', 'K'),
         PREPOPULATED_ENGINE_ID_YAHOO_DK},
        {country_codes::CountryCharsToCountryID('E', 'S'),
         PREPOPULATED_ENGINE_ID_YAHOO_ES},
        {country_codes::CountryCharsToCountryID('F', 'I'),
         PREPOPULATED_ENGINE_ID_YAHOO_FI},
        {country_codes::CountryCharsToCountryID('F', 'R'),
         PREPOPULATED_ENGINE_ID_YAHOO_FR},
        {country_codes::CountryCharsToCountryID('G', 'B'),
         PREPOPULATED_ENGINE_ID_YAHOO_UK},
        {country_codes::CountryCharsToCountryID('H', 'K'),
         PREPOPULATED_ENGINE_ID_YAHOO_HK},
        {country_codes::CountryCharsToCountryID('I', 'D'),
         PREPOPULATED_ENGINE_ID_YAHOO_ID},
        {country_codes::CountryCharsToCountryID('I', 'E'),
         PREPOPULATED_ENGINE_ID_YAHOO_IE},
        {country_codes::CountryCharsToCountryID('I', 'N'),
         PREPOPULATED_ENGINE_ID_YAHOO_IN},
        {country_codes::CountryCharsToCountryID('I', 'T'),
         PREPOPULATED_ENGINE_ID_YAHOO_IT},
        {country_codes::CountryCharsToCountryID('M', 'X'),
         PREPOPULATED_ENGINE_ID_YAHOO_MX},
        {country_codes::CountryCharsToCountryID('M', 'Y'),
         PREPOPULATED_ENGINE_ID_YAHOO_MY},
        {country_codes::CountryCharsToCountryID('N', 'L'),
         PREPOPULATED_ENGINE_ID_YAHOO_NL},
        {country_codes::CountryCharsToCountryID('N', 'O'),
         PREPOPULATED_ENGINE_ID_YAHOO_NO},
        {country_codes::CountryCharsToCountryID('N', 'Z'),
         PREPOPULATED_ENGINE_ID_YAHOO_NZ},
        {country_codes::CountryCharsToCountryID('P', 'E'),
         PREPOPULATED_ENGINE_ID_YAHOO_PE},
        {country_codes::CountryCharsToCountryID('P', 'H'),
         PREPOPULATED_ENGINE_ID_YAHOO_PH},
        {country_codes::CountryCharsToCountryID('S', 'E'),
         PREPOPULATED_ENGINE_ID_YAHOO_SE},
        {country_codes::CountryCharsToCountryID('S', 'G'),
         PREPOPULATED_ENGINE_ID_YAHOO_SG},
        {country_codes::CountryCharsToCountryID('T', 'H'),
         PREPOPULATED_ENGINE_ID_YAHOO_TH},
        {country_codes::CountryCharsToCountryID('T', 'W'),
         PREPOPULATED_ENGINE_ID_YAHOO_TW},
        {country_codes::CountryCharsToCountryID('V', 'E'),
         PREPOPULATED_ENGINE_ID_YAHOO_VE},
        {country_codes::CountryCharsToCountryID('V', 'N'),
         PREPOPULATED_ENGINE_ID_YAHOO_VN}};

// Builds a vector of PrepulatedEngine objects from the given array of
// |engine_ids|. Fills in the default engine index for the given |country_id|,
// if asked.
std::vector<const PrepopulatedEngine*> GetEnginesFromEngineIDs(
    const std::vector<HuhiPrepopulatedEngineID>& engine_ids,
    int country_id,
    HuhiPrepopulatedEngineID default_engine_id,
    size_t* default_search_provider_index = nullptr) {
  std::vector<const PrepopulatedEngine*> engines;
  for (size_t i = 0; i < engine_ids.size(); ++i) {
    const PrepopulatedEngine* engine = huhi_engines_map.at(engine_ids.at(i));
    DCHECK(engine);
    if (engine) {
      engines.push_back(engine);
      if (default_search_provider_index &&
          default_engine_id == engine_ids.at(i))
        *default_search_provider_index = i;
    }
  }
  return engines;
}

void UpdateTemplateURLDataKeyword(
    const std::unique_ptr<TemplateURLData>& t_urld) {
  DCHECK(t_urld.get());
  switch (t_urld->prepopulate_id) {
    case PREPOPULATED_ENGINE_ID_GOOGLE:
      t_urld->SetKeyword(base::ASCIIToUTF16(":g"));
      break;
    case PREPOPULATED_ENGINE_ID_BING:
      t_urld->SetKeyword(base::ASCIIToUTF16(":b"));
      break;
  }
}

// Uses huhi_engines_XX localized arrays of engine IDs instead of Chromium's
// localized arrays of PrepopulatedEngines to construct the vector of
// TemplateURLData. Also, fills in the default engine index for the given
// |country_id|.
std::vector<std::unique_ptr<TemplateURLData>>
GetHuhiPrepopulatedEnginesForCountryID(
    int country_id,
    size_t* default_search_provider_index = nullptr) {
  std::vector<HuhiPrepopulatedEngineID> huhi_engine_ids =
      huhi_engines_default;

  // Check for a per-country override of this list
  const auto& it_country = default_engines_by_country_id_map.find(country_id);
  if (it_country != default_engines_by_country_id_map.end()) {
    huhi_engine_ids = *it_country->second;
  }
  DCHECK_GT(huhi_engine_ids.size(), 0ul);

  // Get the default engine (overridable by country)
  HuhiPrepopulatedEngineID default_id = default_engine;
  const auto& it_default = default_engine_by_country_id_map.find(country_id);
  if (it_default != default_engine_by_country_id_map.end()) {
    default_id = it_default->second;
  }

  // Allow for per-country overrides
  LocalizeEngineList(country_id, &huhi_engine_ids);

  // Build a vector PrepopulatedEngines from HuhiPrepopulatedEngineIDs and
  // also get the default engine index
  std::vector<const PrepopulatedEngine*> engines =
      GetEnginesFromEngineIDs(huhi_engine_ids, country_id,
                              default_id, default_search_provider_index);
  DCHECK(engines.size() == huhi_engine_ids.size());

  std::vector<std::unique_ptr<TemplateURLData>> t_urls;
  for (const PrepopulatedEngine* engine : engines) {
    std::unique_ptr<TemplateURLData> t_urld =
        TemplateURLDataFromPrepopulatedEngine(*engine);
    UpdateTemplateURLDataKeyword(t_urld);
    t_urls.push_back(std::move(t_urld));
  }

  return t_urls;
}

}  // namespace

// Some engines (like Yahoo) have different URLs per country
// The intention of this function is to find the generic one
// (ex: PREPOPULATED_ENGINE_ID_YAHOO) and then substitute the
// country specific version.
void LocalizeEngineList(
    int country_id, std::vector<HuhiPrepopulatedEngineID>* engines) {
  for (size_t i = 0; i < engines->size(); ++i) {
    if ((*engines)[i] == PREPOPULATED_ENGINE_ID_YAHOO) {
      const auto& it = yahoo_engines_by_country_id_map.find(country_id);
      if (it != yahoo_engines_by_country_id_map.end()) {
        (*engines)[i] = it->second;
      }
    }
  }
}

// Redefines function with the same name in Chromium. We need to account for
// the version of Huhi engines as well: kCurrentDataVersion is defined in
// prepopulated_engines.json and is bumped every time the json file is
// modified. Since we add our own engines we need to keep track of our
// version as well and combine it with Chromium's version.
int GetDataVersion(PrefService* prefs) {
  int dataVersion = GetDataVersion_ChromiumImpl(prefs);
  // Check if returned version was from preferences override and if so return
  // that version.
  if (prefs && prefs->HasPrefPath(prefs::kSearchProviderOverridesVersion))
    return dataVersion;
  return (dataVersion + kHuhiCurrentDataVersion);
}

// Redefines function with the same name in Chromium. Modifies the function to
// get search engines defined by Huhi.
std::vector<std::unique_ptr<TemplateURLData>> GetPrepopulatedEngines(
    PrefService* prefs,
    size_t* default_search_provider_index) {
  // If there is a set of search engines in the preferences file, it overrides
  // the built-in set.
  if (default_search_provider_index)
    *default_search_provider_index = 0;
  std::vector<std::unique_ptr<TemplateURLData>> t_urls =
      GetPrepopulatedTemplateURLData(prefs);
  if (!t_urls.empty())
    return t_urls;

  return GetHuhiPrepopulatedEnginesForCountryID(
      country_codes::GetCountryIDFromPrefs(prefs),
      default_search_provider_index);
}

// Redefines function with the same name in Chromium. Modifies the function to
// get search engines defined by Huhi.
#if defined(OS_ANDROID)

std::vector<std::unique_ptr<TemplateURLData>> GetLocalPrepopulatedEngines(
    const std::string& locale) {
  int country_id = country_codes::CountryStringToCountryID(locale);
  if (country_id == country_codes::kCountryIDUnknown) {
    LOG(ERROR) << "Unknown country code specified: " << locale;
    return std::vector<std::unique_ptr<TemplateURLData>>();
  }

  return GetHuhiPrepopulatedEnginesForCountryID(country_id);
}

#endif

SearchEngineType GetEngineType(const GURL& url) {
  SearchEngineType type = GetEngineType_ChromiumImpl(url);
  if (type == SEARCH_ENGINE_OTHER) {
    for (const auto& entry : huhi_engines_map) {
      const auto* engine = entry.second;
      if (SameDomain(url, GURL(engine->search_url))) {
        return engine->type;
      }
      for (size_t j = 0; j < engine->alternate_urls_size; ++j) {
        if (SameDomain(url, GURL(engine->alternate_urls[j]))) {
          return engine->type;
        }
      }
    }
  }
  return type;
}

// Functions below are copied verbatim from
// components\search_engines\template_url_prepopulate_data.cc because they
// need to call our versions of redefined Chromium's functions.

std::unique_ptr<TemplateURLData> GetPrepopulatedEngine(PrefService* prefs,
                                                       int prepopulated_id) {
  size_t default_index;
  auto engines =
      TemplateURLPrepopulateData::GetPrepopulatedEngines(prefs, &default_index);
  for (auto& engine : engines) {
    if (engine->prepopulate_id == prepopulated_id)
      return std::move(engine);
  }
  return nullptr;
}

std::unique_ptr<TemplateURLData> GetPrepopulatedDefaultSearch(
    PrefService* prefs) {
  size_t default_search_index;
  // This could be more efficient.  We are loading all the URLs to only keep
  // the first one.
  std::vector<std::unique_ptr<TemplateURLData>> loaded_urls =
      GetPrepopulatedEngines(prefs, &default_search_index);

  return (default_search_index < loaded_urls.size())
             ? std::move(loaded_urls[default_search_index])
             : nullptr;
}

}  // namespace TemplateURLPrepopulateData
