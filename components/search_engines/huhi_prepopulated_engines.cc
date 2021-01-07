/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/components/search_engines/huhi_prepopulated_engines.h"

#include "components/search_engines/prepopulated_engines.h"
#include "components/search_engines/search_engine_type.h"

namespace TemplateURLPrepopulateData {

// IMPORTANT! Make sure to bump this value if you make changes to the
// engines below or add/remove engines.
const int kHuhiCurrentDataVersion = 8;
// DO NOT CHANGE THIS ONE. Used for backfilling kHuhiDefaultSearchVersion.
const int kHuhiFirstTrackedDataVersion = 6;

namespace {

// Maps HuhiPrepopulatedEngineID to Chromium's PrepopulatedEngine.
const std::map<HuhiPrepopulatedEngineID, const PrepopulatedEngine*>
    huhi_engines_map = {
        {PREPOPULATED_ENGINE_ID_GOOGLE, &google},
        {PREPOPULATED_ENGINE_ID_YAHOO, &huhi_yahoo},
        {PREPOPULATED_ENGINE_ID_YANDEX, &huhi_yandex},
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

PrepopulatedEngine ModifyEngineParams(const PrepopulatedEngine& engine,
                                      const wchar_t* const name,
                                      const wchar_t* const keyword,
                                      const char* const search_url,
                                      const char* const suggest_url,
                                      int id) {
  return {name ? name : engine.name,
          keyword ? keyword : engine.keyword,
          engine.favicon_url,
          search_url ? search_url : engine.search_url,
          engine.encoding,
          suggest_url ? suggest_url : engine.suggest_url,
          engine.image_url,
          engine.new_tab_url,
          engine.contextual_search_url,
          engine.logo_url,
          engine.doodle_url,
          engine.search_url_post_params,
          engine.suggest_url_post_params,
          engine.image_url_post_params,
          engine.alternate_urls,
          engine.alternate_urls_size,
          engine.type,
          id > 0 ? id : engine.id};
}

}  // namespace

const PrepopulatedEngine duckduckgo = {
    L"DuckDuckGo",
    L":d",
    "https://duckduckgo.com/favicon.ico",
    "https://duckduckgo.com/?q={searchTerms}&t=huhi",
    "UTF-8",
    "https://ac.duckduckgo.com/ac/?q={searchTerms}&type=list",
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    0,
    SEARCH_ENGINE_DUCKDUCKGO,
    PREPOPULATED_ENGINE_ID_DUCKDUCKGO,
};

const PrepopulatedEngine duckduckgo_de =
    ModifyEngineParams(duckduckgo,
                       NULL,
                       NULL,
                       "https://duckduckgo.com/?q={searchTerms}&t=huhined",
                       NULL,
                       PREPOPULATED_ENGINE_ID_DUCKDUCKGO_DE);

const PrepopulatedEngine duckduckgo_au_nz_ie =
    ModifyEngineParams(duckduckgo,
                       NULL,
                       NULL,
                       "https://duckduckgo.com/?q={searchTerms}&t=huhied",
                       NULL,
                       PREPOPULATED_ENGINE_ID_DUCKDUCKGO_AU_NZ_IE);

#if defined(OS_ANDROID)
const PrepopulatedEngine duckduckgo_lite = {
    L"DuckDuckGo Lite",
    L":dl",
    "https://duckduckgo.com/favicon.ico",
    "https://duckduckgo.com/lite/?q={searchTerms}&t=huhi",
    "UTF-8",
    "https://ac.duckduckgo.com/ac/?q={searchTerms}&type=list",
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    0,
    SEARCH_ENGINE_DUCKDUCKGO,
    PREPOPULATED_ENGINE_ID_DUCKDUCKGO_LITE,
};
#endif

const PrepopulatedEngine qwant = {
    L"Qwant",
    L":q",
    "https://www.qwant.com/favicon.ico",
    "https://www.qwant.com/?q={searchTerms}&client=brz-huhi",
    "UTF-8",
    "https://api.qwant.com/api/suggest/?q={searchTerms}&client=opensearch",
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    0,
    SEARCH_ENGINE_QWANT,
    PREPOPULATED_ENGINE_ID_QWANT,
};

const PrepopulatedEngine startpage = {
    L"Startpage",
    L":sp",
    "https://www.startpage.com/favicon.ico",
    "https://www.startpage.com/do/"
    "search?q={searchTerms}&segment=startpage.huhi",
    "UTF-8",
    "https://www.startpage.com/cgi-bin/"
    "csuggest?query={searchTerms}&limit=10&format=json",
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    0,
    SEARCH_ENGINE_OTHER,
    PREPOPULATED_ENGINE_ID_STARTPAGE,
};

const PrepopulatedEngine huhi_yandex =
    ModifyEngineParams(yandex_com,
                       L"Yandex",
                       NULL,
                       "https://yandex.ru/search/?clid="
#if defined(OS_ANDROID)
                       "2423859"
#else
                       "2353835"
#endif
                       "&text={searchTerms}",
                       "https://suggest.yandex.ru/suggest-ff.cgi?"
                       "part={searchTerms}&v=3&sn=5&srv=huhi_desktop",
                       PREPOPULATED_ENGINE_ID_YANDEX);

#define kHuhiYahooName L"Yahoo"
#define kHuhiYahooKeyword L":y"
#define HUHI_YAHOO_SEARCH_URL(PREFIX) \
  "https://" PREFIX                    \
  ".search.yahoo.com"                  \
  "/search?p={searchTerms}&fr=huhi_yset"
#define HUHI_YAHOO_SUGGEST_URL(PREFIX) \
  "https://" PREFIX                     \
  ".search.yahoo.com"                   \
  "/sugg/chrome?output=fxjson&appid=huhi_yset&command={searchTerms}"

const PrepopulatedEngine huhi_yahoo = ModifyEngineParams(
    yahoo,
    kHuhiYahooName,
    kHuhiYahooKeyword,
    "https://search.yahoo.com/search?p={searchTerms}&fr=huhi_yset",
    "https://search.yahoo.com/sugg/chrome?"
    "output=fxjson&appid=huhi_yset&command={searchTerms}",
    PREPOPULATED_ENGINE_ID_YAHOO);

const PrepopulatedEngine huhi_yahoo_ar =
    ModifyEngineParams(yahoo_ar,
                       kHuhiYahooName,
                       kHuhiYahooKeyword,
                       HUHI_YAHOO_SEARCH_URL("ar"),
                       HUHI_YAHOO_SUGGEST_URL("ar"),
                       PREPOPULATED_ENGINE_ID_YAHOO_AR);

const PrepopulatedEngine huhi_yahoo_at =
    ModifyEngineParams(yahoo_at,
                       kHuhiYahooName,
                       kHuhiYahooKeyword,
                       HUHI_YAHOO_SEARCH_URL("at"),
                       HUHI_YAHOO_SUGGEST_URL("at"),
                       PREPOPULATED_ENGINE_ID_YAHOO_AT);

const PrepopulatedEngine huhi_yahoo_au =
    ModifyEngineParams(yahoo_au,
                       kHuhiYahooName,
                       kHuhiYahooKeyword,
                       HUHI_YAHOO_SEARCH_URL("au"),
                       HUHI_YAHOO_SUGGEST_URL("au"),
                       PREPOPULATED_ENGINE_ID_YAHOO_AU);

const PrepopulatedEngine huhi_yahoo_br =
    ModifyEngineParams(yahoo_br,
                       kHuhiYahooName,
                       kHuhiYahooKeyword,
                       HUHI_YAHOO_SEARCH_URL("br"),
                       HUHI_YAHOO_SUGGEST_URL("br"),
                       PREPOPULATED_ENGINE_ID_YAHOO_BR);

const PrepopulatedEngine huhi_yahoo_ca =
    ModifyEngineParams(yahoo_ca,
                       kHuhiYahooName,
                       kHuhiYahooKeyword,
                       HUHI_YAHOO_SEARCH_URL("ca"),
                       HUHI_YAHOO_SUGGEST_URL("ca"),
                       PREPOPULATED_ENGINE_ID_YAHOO_CA);

const PrepopulatedEngine huhi_yahoo_ch =
    ModifyEngineParams(yahoo_ch,
                       kHuhiYahooName,
                       kHuhiYahooKeyword,
                       HUHI_YAHOO_SEARCH_URL("ch"),
                       HUHI_YAHOO_SUGGEST_URL("ch"),
                       PREPOPULATED_ENGINE_ID_YAHOO_CH);

const PrepopulatedEngine huhi_yahoo_cl =
    ModifyEngineParams(yahoo_cl,
                       kHuhiYahooName,
                       kHuhiYahooKeyword,
                       HUHI_YAHOO_SEARCH_URL("cl"),
                       HUHI_YAHOO_SUGGEST_URL("cl"),
                       PREPOPULATED_ENGINE_ID_YAHOO_CL);

const PrepopulatedEngine huhi_yahoo_co =
    ModifyEngineParams(yahoo_co,
                       kHuhiYahooName,
                       kHuhiYahooKeyword,
                       HUHI_YAHOO_SEARCH_URL("co"),
                       HUHI_YAHOO_SUGGEST_URL("co"),
                       PREPOPULATED_ENGINE_ID_YAHOO_CO);

const PrepopulatedEngine huhi_yahoo_de =
    ModifyEngineParams(yahoo_de,
                       kHuhiYahooName,
                       kHuhiYahooKeyword,
                       HUHI_YAHOO_SEARCH_URL("de"),
                       HUHI_YAHOO_SUGGEST_URL("de"),
                       PREPOPULATED_ENGINE_ID_YAHOO_DE);

const PrepopulatedEngine huhi_yahoo_dk =
    ModifyEngineParams(yahoo_dk,
                       kHuhiYahooName,
                       kHuhiYahooKeyword,
                       HUHI_YAHOO_SEARCH_URL("dk"),
                       HUHI_YAHOO_SUGGEST_URL("dk"),
                       PREPOPULATED_ENGINE_ID_YAHOO_DK);

const PrepopulatedEngine huhi_yahoo_es =
    ModifyEngineParams(yahoo_es,
                       kHuhiYahooName,
                       kHuhiYahooKeyword,
                       HUHI_YAHOO_SEARCH_URL("es"),
                       HUHI_YAHOO_SUGGEST_URL("es"),
                       PREPOPULATED_ENGINE_ID_YAHOO_ES);

const PrepopulatedEngine huhi_yahoo_fi =
    ModifyEngineParams(yahoo_fi,
                       kHuhiYahooName,
                       kHuhiYahooKeyword,
                       HUHI_YAHOO_SEARCH_URL("fi"),
                       HUHI_YAHOO_SUGGEST_URL("fi"),
                       PREPOPULATED_ENGINE_ID_YAHOO_FI);

const PrepopulatedEngine huhi_yahoo_fr =
    ModifyEngineParams(yahoo_fr,
                       kHuhiYahooName,
                       kHuhiYahooKeyword,
                       HUHI_YAHOO_SEARCH_URL("fr"),
                       HUHI_YAHOO_SUGGEST_URL("fr"),
                       PREPOPULATED_ENGINE_ID_YAHOO_FR);

const PrepopulatedEngine huhi_yahoo_hk =
    ModifyEngineParams(yahoo_hk,
                       kHuhiYahooName,
                       kHuhiYahooKeyword,
                       HUHI_YAHOO_SEARCH_URL("hk"),
                       HUHI_YAHOO_SUGGEST_URL("hk"),
                       PREPOPULATED_ENGINE_ID_YAHOO_HK);

const PrepopulatedEngine huhi_yahoo_id =
    ModifyEngineParams(yahoo_id,
                       kHuhiYahooName,
                       kHuhiYahooKeyword,
                       HUHI_YAHOO_SEARCH_URL("id"),
                       HUHI_YAHOO_SUGGEST_URL("id"),
                       PREPOPULATED_ENGINE_ID_YAHOO_ID);

const PrepopulatedEngine huhi_yahoo_ie = {
    kHuhiYahooName,
    kHuhiYahooKeyword,
    "https://ie.search.yahoo.com/favicon.ico",
    HUHI_YAHOO_SEARCH_URL("ie"),
    "UTF-8",
    HUHI_YAHOO_SUGGEST_URL("ie"),
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    0,
    SEARCH_ENGINE_YAHOO,
    PREPOPULATED_ENGINE_ID_YAHOO_IE};

const PrepopulatedEngine huhi_yahoo_in =
    ModifyEngineParams(yahoo_in,
                       kHuhiYahooName,
                       kHuhiYahooKeyword,
                       HUHI_YAHOO_SEARCH_URL("in"),
                       HUHI_YAHOO_SUGGEST_URL("in"),
                       PREPOPULATED_ENGINE_ID_YAHOO_IN);

const PrepopulatedEngine huhi_yahoo_it = {
    kHuhiYahooName,
    kHuhiYahooKeyword,
    "https://it.search.yahoo.com/favicon.ico",
    HUHI_YAHOO_SEARCH_URL("it"),
    "UTF-8",
    HUHI_YAHOO_SUGGEST_URL("it"),
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    0,
    SEARCH_ENGINE_YAHOO,
    PREPOPULATED_ENGINE_ID_YAHOO_IT};

const PrepopulatedEngine huhi_yahoo_mx =
    ModifyEngineParams(yahoo_mx,
                       kHuhiYahooName,
                       kHuhiYahooKeyword,
                       HUHI_YAHOO_SEARCH_URL("mx"),
                       HUHI_YAHOO_SUGGEST_URL("mx"),
                       PREPOPULATED_ENGINE_ID_YAHOO_MX);

const PrepopulatedEngine huhi_yahoo_my =
    ModifyEngineParams(yahoo_my,
                       kHuhiYahooName,
                       kHuhiYahooKeyword,
                       HUHI_YAHOO_SEARCH_URL("malaysia"),
                       HUHI_YAHOO_SUGGEST_URL("malaysia"),
                       PREPOPULATED_ENGINE_ID_YAHOO_MY);

const PrepopulatedEngine huhi_yahoo_nl =
    ModifyEngineParams(yahoo_nl,
                       kHuhiYahooName,
                       kHuhiYahooKeyword,
                       HUHI_YAHOO_SEARCH_URL("nl"),
                       HUHI_YAHOO_SUGGEST_URL("nl"),
                       PREPOPULATED_ENGINE_ID_YAHOO_NL);

const PrepopulatedEngine huhi_yahoo_no = {
    kHuhiYahooName,
    kHuhiYahooKeyword,
    "https://no.search.yahoo.com/favicon.ico",
    HUHI_YAHOO_SEARCH_URL("no"),
    "UTF-8",
    HUHI_YAHOO_SUGGEST_URL("no"),
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    0,
    SEARCH_ENGINE_YAHOO,
    PREPOPULATED_ENGINE_ID_YAHOO_NO};

const PrepopulatedEngine huhi_yahoo_nz =
    ModifyEngineParams(yahoo_nz,
                       kHuhiYahooName,
                       kHuhiYahooKeyword,
                       HUHI_YAHOO_SEARCH_URL("nz"),
                       HUHI_YAHOO_SUGGEST_URL("nz"),
                       PREPOPULATED_ENGINE_ID_YAHOO_NZ);

const PrepopulatedEngine huhi_yahoo_pe =
    ModifyEngineParams(yahoo_pe,
                       kHuhiYahooName,
                       kHuhiYahooKeyword,
                       HUHI_YAHOO_SEARCH_URL("pe"),
                       HUHI_YAHOO_SUGGEST_URL("pe"),
                       PREPOPULATED_ENGINE_ID_YAHOO_PE);

const PrepopulatedEngine huhi_yahoo_ph =
    ModifyEngineParams(yahoo_ph,
                       kHuhiYahooName,
                       kHuhiYahooKeyword,
                       HUHI_YAHOO_SEARCH_URL("ph"),
                       HUHI_YAHOO_SUGGEST_URL("ph"),
                       PREPOPULATED_ENGINE_ID_YAHOO_PH);

const PrepopulatedEngine huhi_yahoo_se =
    ModifyEngineParams(yahoo_se,
                       kHuhiYahooName,
                       kHuhiYahooKeyword,
                       HUHI_YAHOO_SEARCH_URL("se"),
                       HUHI_YAHOO_SUGGEST_URL("se"),
                       PREPOPULATED_ENGINE_ID_YAHOO_SE);

const PrepopulatedEngine huhi_yahoo_sg =
    ModifyEngineParams(yahoo_sg,
                       kHuhiYahooName,
                       kHuhiYahooKeyword,
                       HUHI_YAHOO_SEARCH_URL("sg"),
                       HUHI_YAHOO_SUGGEST_URL("sg"),
                       PREPOPULATED_ENGINE_ID_YAHOO_SG);

const PrepopulatedEngine huhi_yahoo_th =
    ModifyEngineParams(yahoo_th,
                       kHuhiYahooName,
                       kHuhiYahooKeyword,
                       HUHI_YAHOO_SEARCH_URL("th"),
                       HUHI_YAHOO_SUGGEST_URL("th"),
                       PREPOPULATED_ENGINE_ID_YAHOO_TH);

const PrepopulatedEngine huhi_yahoo_tw =
    ModifyEngineParams(yahoo_tw,
                       kHuhiYahooName,
                       kHuhiYahooKeyword,
                       HUHI_YAHOO_SEARCH_URL("tw"),
                       HUHI_YAHOO_SUGGEST_URL("tw"),
                       PREPOPULATED_ENGINE_ID_YAHOO_TW);

const PrepopulatedEngine huhi_yahoo_uk =
    ModifyEngineParams(yahoo_uk,
                       kHuhiYahooName,
                       kHuhiYahooKeyword,
                       HUHI_YAHOO_SEARCH_URL("uk"),
                       HUHI_YAHOO_SUGGEST_URL("uk"),
                       PREPOPULATED_ENGINE_ID_YAHOO_UK);

const PrepopulatedEngine huhi_yahoo_ve =
    ModifyEngineParams(yahoo_ve,
                       kHuhiYahooName,
                       kHuhiYahooKeyword,
                       HUHI_YAHOO_SEARCH_URL("ve"),
                       HUHI_YAHOO_SUGGEST_URL("ve"),
                       PREPOPULATED_ENGINE_ID_YAHOO_VE);

const PrepopulatedEngine huhi_yahoo_vn =
    ModifyEngineParams(yahoo_vn,
                       kHuhiYahooName,
                       kHuhiYahooKeyword,
                       HUHI_YAHOO_SEARCH_URL("vn"),
                       HUHI_YAHOO_SUGGEST_URL("vn"),
                       PREPOPULATED_ENGINE_ID_YAHOO_VN);

const std::map<HuhiPrepopulatedEngineID, const PrepopulatedEngine*>&
GetHuhiEnginesMap() {
  return huhi_engines_map;
}

}  // namespace TemplateURLPrepopulateData
