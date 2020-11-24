/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#define LoadLocalState LoadLocalState_ChromiumImpl
#include "../../../../chrome/browser/chrome_resource_bundle_helper.cc"
#undef LoadLocalState
#include "huhi/common/resource_bundle_helper.h"

std::string LoadLocalState(
    ChromeFeatureListCreator* chrome_feature_list_creator,
    bool is_running_tests) {
  std::string ret = LoadLocalState_ChromiumImpl(chrome_feature_list_creator, is_running_tests);
  huhi::InitializeResourceBundle();
  return ret;
}