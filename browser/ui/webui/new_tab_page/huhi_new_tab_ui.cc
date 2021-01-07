// Copyright (c) 2020 The Huhi Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#include "huhi/browser/ui/webui/new_tab_page/huhi_new_tab_ui.h"

#include <string>

#include "base/memory/ptr_util.h"
#include "huhi/browser/new_tab/new_tab_shows_options.h"
#include "huhi/browser/ui/webui/basic_ui.h"
#include "huhi/browser/ui/webui/new_tab_page/huhi_new_tab_message_handler.h"
#include "huhi/browser/ui/webui/new_tab_page/instant_service_message_handler.h"
#include "huhi/common/pref_names.h"
#include "huhi/common/webui_url_constants.h"
#include "huhi/components/huhi_new_tab/resources/grit/huhi_new_tab_generated_map.h"
#include "chrome/browser/profiles/profile.h"
#include "components/grit/huhi_components_resources.h"
#include "components/strings/grit/components_strings.h"
#include "content/public/browser/web_ui_data_source.h"
#include "ui/base/l10n/l10n_util.h"

HuhiNewTabUI::HuhiNewTabUI(content::WebUI* web_ui, const std::string& name)
    : WebUIController(web_ui) {
  Profile* profile = Profile::FromWebUI(web_ui);

  if (huhi::ShouldNewTabShowBlankpage(profile)) {
    content::WebUIDataSource* source =
        content::WebUIDataSource::Create(name);
    source->SetDefaultResource(IDR_HUHI_BLANK_NEW_TAB_HTML);
    content::WebUIDataSource::Add(profile, source);
  } else {
    content::WebUIDataSource* source = CreateBasicUIHTMLSource(profile, name,
        kHuhiNewTabGenerated, kHuhiNewTabGeneratedSize,
        IDR_HUHI_NEW_TAB_HTML);
    web_ui->AddMessageHandler(base::WrapUnique(
      HuhiNewTabMessageHandler::Create(source, profile)));
    web_ui->AddMessageHandler(base::WrapUnique(
      new InstantServiceMessageHandler(profile)));
    content::WebUIDataSource::Add(profile, source);
  }

  web_ui->OverrideTitle(l10n_util::GetStringUTF16(IDS_NEW_TAB_TITLE));
}

HuhiNewTabUI::~HuhiNewTabUI() {
}
