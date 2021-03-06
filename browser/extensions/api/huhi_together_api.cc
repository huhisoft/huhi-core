/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/extensions/api/huhi_together_api.h"

#include <string>
#include <memory>

#include "base/environment.h"
#include "huhi/browser/profiles/profile_util.h"
#include "huhi/components/huhi_together/browser/regions.h"
#include "huhi/components/ntp_widget_utils/browser/ntp_widget_utils_region.h"
#include "chrome/browser/profiles/profile.h"

namespace extensions {
namespace api {

ExtensionFunction::ResponseAction
HuhiTogetherIsSupportedFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());

  if (huhi::IsTorProfile(profile)) {
    return RespondNow(Error("Not available in Tor profile"));
  }

  bool is_supported = ntp_widget_utils::IsRegionSupported(
      profile->GetPrefs(), huhi_together::supported_regions, true);
  return RespondNow(OneArgument(
      std::make_unique<base::Value>(is_supported)));
}

}  // namespace api
}  // namespace extensions
