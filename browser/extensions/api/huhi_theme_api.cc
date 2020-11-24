/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/extensions/api/huhi_theme_api.h"

#include <memory>
#include <string>

#include "base/json/json_writer.h"
#include "base/values.h"
#include "huhi/browser/themes/huhi_dark_mode_utils.h"
#include "huhi/common/extensions/api/huhi_theme.h"

namespace extensions {
namespace api {

ExtensionFunction::ResponseAction HuhiThemeGetHuhiThemeListFunction::Run() {
  std::string json_string;
  base::JSONWriter::Write(dark_mode::GetHuhiDarkModeTypeList(), &json_string);
  return RespondNow(OneArgument(std::make_unique<base::Value>(json_string)));
}

ExtensionFunction::ResponseAction HuhiThemeGetHuhiThemeTypeFunction::Run() {
  const std::string theme_type =
      dark_mode::GetStringFromHuhiDarkModeType(
          dark_mode::GetActiveHuhiDarkModeType());
  return RespondNow(OneArgument(std::make_unique<base::Value>(theme_type)));
}

ExtensionFunction::ResponseAction HuhiThemeSetHuhiThemeTypeFunction::Run() {
  std::unique_ptr<huhi_theme::SetHuhiThemeType::Params> params(
      huhi_theme::SetHuhiThemeType::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  dark_mode::SetHuhiDarkModeType(params->type);

  return RespondNow(NoArguments());
}

}  // namespace api
}  // namespace extensions
