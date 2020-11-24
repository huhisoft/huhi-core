/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/common/translate_network_constants.h"

const char kTranslateInitiatorURL[] = "https://translate.googleapis.com/";
const char kTranslateElementJSPattern[] = "https://translate.googleapis.com/translate_a/element.js*"; // NOLINT
const char kTranslateElementMainJSPattern[] = "https://translate.googleapis.com/element/*/js/element/element_main.js"; // NOLINT
const char kTranslateMainJSPattern[] = "https://translate.googleapis.com/translate_static/js/element/main.js"; // NOLINT
const char kTranslateRequestPattern[] = "https://translate.googleapis.com/translate_a/t?anno=3&client=te_lib&*"; // NOLINT
const char kTranslateLanguagePattern[] = "https://translate.googleapis.com/translate_a/l?client=chrome&*"; // NOLINT
const char kTranslateGen204Pattern[] = "https://translate.google.com/gen204*";
const char kTranslateElementMainCSSPattern[] = "https://translate.googleapis.com/translate_static/css/translateelement.css"; // NOLINT
const char kTranslateBrandingPNGPattern[] = "https://www.gstatic.com/images/branding/product/*x/translate_24dp.png"; // NOLINT
const char kHuhiTranslateServer[] = "https://translate-relay.huhisoft.com";
const char kHuhiTranslateEndpoint[] = "https://translate-relay.huhisoft.com/translate"; // NOLINT
const char kHuhiTranslateLanguageEndpoint[] = "https://translate-relay.huhisoft.com/language"; // NOLINT
const char kHuhiTranslateServerPrefix[] = "https://translate-relay.huhisoft.com/*"; // NOLINT
