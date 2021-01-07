// Copyright (c) 2020 The Huhi Authors
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#include "huhi/browser/ui/webui/navigation_bar_data_provider.h"
#include "huhi/grit/huhi_generated_resources.h"
#include "content/public/browser/web_ui_data_source.h"

#define HUHI_CREATE_BOOKMARKS_UI_HTML_SOURCE \
  NavigationBarDataProvider::Initialize(source); \
  source->AddLocalizedString( \
      "emptyList", IDS_HUHI_BOOKMARK_MANAGER_EMPTY_LIST);

#include "../../../../../../../chrome/browser/ui/webui/bookmarks/bookmarks_ui.cc"

#undef HUHI_CREATE_BOOKMARKS_UI_HTML_SOURCE
