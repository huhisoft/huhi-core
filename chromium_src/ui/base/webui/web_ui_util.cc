// Copyright (c) 2020 The Huhi Authors
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#include "ui/base/webui/web_ui_util.h"

#include "huhi/ui/webui/resources/grit/huhi_webui_resources.h"
#include "ui/resources/grit/webui_resources.h"

// Replace text_defaults.css with huhi's text_defaults.css
// which is defined in huhi_webui_resources.grd.
#define IDR_WEBUI_CSS_TEXT_DEFAULTS_MD_PREVIOUS IDR_WEBUI_CSS_TEXT_DEFAULTS_MD
#undef IDR_WEBUI_CSS_TEXT_DEFAULTS_MD
#define IDR_WEBUI_CSS_TEXT_DEFAULTS_MD IDR_HUHI_WEBUI_CSS_TEXT_DEFAULTS
#include "../../../../../ui/base/webui/web_ui_util.cc"  // NOLINT
#undef IDR_WEBUI_CSS_TEXT_DEFAULTS_MD
#define IDR_WEBUI_CSS_TEXT_DEFAULTS_MD IDR_WEBUI_CSS_TEXT_DEFAULTS_MD_PREVIOUS

#if !defined(OS_ANDROID)
#endif
