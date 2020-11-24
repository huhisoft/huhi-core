/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/extensions/api/greaselion_api.h"

#include <memory>

#include "base/values.h"
#include "huhi/browser/greaselion/greaselion_service_factory.h"
#include "huhi/common/extensions/api/greaselion.h"
#include "huhi/components/greaselion/browser/greaselion_service.h"
#include "chrome/browser/profiles/profile.h"

namespace extensions {
namespace api {

ExtensionFunction::ResponseAction
GreaselionIsGreaselionExtensionFunction::Run() {
  Profile* profile = Profile::FromBrowserContext(browser_context());
  ::greaselion::GreaselionService* greaselion_service =
      ::greaselion::GreaselionServiceFactory::GetForBrowserContext(profile);
  if (!greaselion_service) {
    return RespondNow(OneArgument(std::make_unique<base::Value>(false)));
  }

  std::unique_ptr<greaselion::IsGreaselionExtension::Params> params(
      greaselion::IsGreaselionExtension::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  bool result = greaselion_service->IsGreaselionExtension(params->id);
  return RespondNow(OneArgument(std::make_unique<base::Value>(result)));
}

}  // namespace api
}  // namespace extensions
