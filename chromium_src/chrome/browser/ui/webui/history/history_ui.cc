// Copyright (c) 2020 The Huhi Software Authors
// This Source Code Form is subject to the terms of the Huhi Software
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#include "huhi/browser/ui/webui/navigation_bar_data_provider.h"

namespace {

void HuhiCustomizeHistoryDataSource(content::WebUIDataSource* source) {
  NavigationBarDataProvider::Initialize(source);
}

}  // namespace

#include "../../../../../../../chrome/browser/ui/webui/history/history_ui.cc"  // NOLINT
