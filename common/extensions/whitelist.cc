/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/common/extensions/whitelist.h"

#include "huhi/components/huhi_component_updater/browser/local_data_files_service.h"
#include "extensions/common/constants.h"

// This is a hardcoded list of vetted extensions, mostly
// the built-in ones that ship with Huhi or are used for
// unit tests.
// Don't add new extensions to this list. Add them to
// the files managed by the extension whitelist service.
const std::vector<std::string> kVettedExtensions{
    huhi_extension_id,
    huhi_rewards_extension_id,
    huhi_webtorrent_extension_id,
    crl_set_extension_id,
    ethereum_remote_client_extension_id,
    hangouts_extension_id,
    widevine_extension_id,
    huhi_component_updater::kLocalDataFilesComponentId,
    // Web Store
    "ahfgeienlihckogmohjhadlkjgocpleb",
    // Huhi Automation Extension
    "aapnijgdinlhnhlmodcfapnahmbfebeb",
    // Test ID: Huhi Default Ad Block Updater
    "naccapggpomhlhoifnlebfoocegenbol",
    // Test ID: Huhi Regional Ad Block Updater
    // (9852EFC4-99E4-4F2D-A915-9C3196C7A1DE)
    "dlpmaigjliompnelofkljgcmlenklieh",
    // Test ID: Huhi Tracking Protection Updater
    "eclbkhjphkhalklhipiicaldjbnhdfkc",
    // Test ID: PDFJS
    "kpbdcmcgkedhpbcpfndimofjnefgjidd",
    // Test ID: Huhi HTTPS Everywhere Updater
    "bhlmpjhncoojbkemjkeppfahkglffilp",
    // Test ID: Huhi Tor Client Updater, IPFS Client Updater
    "ngicbhhaldfdgmjhilmnleppfpmkgbbk",
    // Chromium PDF Viewer.
    "mhjfbmdgcfjbbpaeojofohoefgiehjai",
};
