/* Copyright 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/common/huhi_content_client.h"

#include <string>

#include "base/memory/ref_counted_memory.h"
#include "components/grit/huhi_components_resources.h"
#include "components/grit/components_resources.h"
#include "content/public/common/url_constants.h"
#include "ui/base/resource/resource_bundle.h"

HuhiContentClient::HuhiContentClient() {}

HuhiContentClient::~HuhiContentClient() {}

base::RefCountedMemory* HuhiContentClient::GetDataResourceBytes(
    int resource_id) {
  if (resource_id == IDR_FLAGS_UI_FLAGS_JS) {
    const ui::ResourceBundle& resource_bundle =
        ui::ResourceBundle::GetSharedInstance();
    const std::string flags_js =
        resource_bundle.LoadDataResourceString(resource_id) +
        resource_bundle.LoadDataResourceString(
            IDR_FLAGS_UI_HUHI_FLAGS_OVERRIDES_JS);
    base::RefCountedString* bytes = new base::RefCountedString();
    bytes->data().assign(flags_js.data(), flags_js.length());
    return bytes;
  }
  return ChromeContentClient::GetDataResourceBytes(resource_id);
}

void HuhiContentClient::AddAdditionalSchemes(Schemes* schemes) {
  ChromeContentClient::AddAdditionalSchemes(schemes);
  schemes->standard_schemes.push_back(content::kHuhiUIScheme);
  schemes->secure_schemes.push_back(content::kHuhiUIScheme);
  schemes->cors_enabled_schemes.push_back(content::kHuhiUIScheme);
  schemes->savable_schemes.push_back(content::kHuhiUIScheme);
}
