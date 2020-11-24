/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/resources/extensions/grit/huhi_extensions_resources.h"
#include "huhi/browser/resources/extensions/grit/huhi_extensions_resources_map.h"
#include "huhi/browser/ui/webui/navigation_bar_data_provider.h"
#include "huhi/grit/huhi_generated_resources.h"
#include "chrome/common/buildflags.h"
#include "chrome/grit/generated_resources.h"
#include "content/public/browser/web_ui_data_source.h"

namespace extensions {

namespace {

#if !BUILDFLAG(OPTIMIZE_WEBUI)
constexpr char kHuhiGeneratedPath[] =
    "@out_folder@/gen/huhi/browser/resources/extensions/";
#endif

// Called from the original extension_ui.cc's CreateMdExtensionsSource via a
// patch.
void HuhiAddExtensionsResources(content::WebUIDataSource* source) {
#if !BUILDFLAG(OPTIMIZE_WEBUI)
  for (size_t i = 0; i < kHuhiExtensionsResourcesSize; ++i) {
    std::string path = kHuhiExtensionsResources[i].name;
    if (path.rfind(kHuhiGeneratedPath, 0) == 0) {
      path = path.substr(strlen(kHuhiGeneratedPath));
    }
    source->AddResourcePath(path, kHuhiExtensionsResources[i].value);
  }
#endif
  NavigationBarDataProvider::Initialize(source);
}

}  // namespace

}  // namespace extensions

// These are defined in generated_resources.h, but since we are including it
// here the original extensions_ui.cc shouldn't include it again and the
// redefined values will be used.
#undef IDS_EXTENSIONS_ITEM_CHROME_WEB_STORE
#define IDS_EXTENSIONS_ITEM_CHROME_WEB_STORE \
  IDS_EXTENSIONS_HUHI_ITEM_CHROME_WEB_STORE
#undef IDS_EXTENSIONS_ITEM_SOURCE_WEBSTORE
#define IDS_EXTENSIONS_ITEM_SOURCE_WEBSTORE \
  IDS_EXTENSIONS_HUHI_ITEM_SOURCE_WEBSTORE

#include "../../../../../../../chrome/browser/ui/webui/extensions/extensions_ui.cc"
