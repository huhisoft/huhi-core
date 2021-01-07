/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/install_static/buildflags.h"

#if defined(OFFICIAL_BUILD)
#undef BUILDFLAG_INTERNAL_USE_GOOGLE_UPDATE_INTEGRATION
#define BUILDFLAG_INTERNAL_USE_GOOGLE_UPDATE_INTEGRATION() (1)
#endif

#define HUHI_INSTALL_MODES                                                 \
  std::wstring GetClientsKeyPathForApp(const wchar_t* app_guid) {           \
    return std::wstring(L"Software\\HuhiSoftware\\Update\\Clients\\")      \
        .append(app_guid);                                                  \
  }                                                                         \
                                                                            \
  std::wstring GetClientStateKeyPathForApp(const wchar_t* app_guid) {       \
    return std::wstring(L"Software\\HuhiSoftware\\Update\\ClientState\\")  \
        .append(app_guid);                                                  \
  }                                                                         \
                                                                            \
  std::wstring GetClientStateMediumKeyPathForApp(const wchar_t* app_guid) { \
    return std::wstring(                                                    \
               L"Software\\HuhiSoftware\\Update\\ClientStateMedium\\")     \
        .append(app_guid);                                                  \
  }

#include "../../../../chrome/install_static/install_modes.cc"
#undef HUHI_INSTALL_MODES

#if defined(OFFICIAL_BUILD)
#undef BUILDFLAG_INTERNAL_USE_GOOGLE_UPDATE_INTEGRATION
#endif
