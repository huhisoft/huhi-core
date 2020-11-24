/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_EXTENSIONS_API_HUHI_THEME_API_H_
#define HUHI_BROWSER_EXTENSIONS_API_HUHI_THEME_API_H_

#include "extensions/browser/extension_function.h"

namespace extensions {
namespace api {

class HuhiThemeGetHuhiThemeListFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiTheme.getHuhiThemeList", UNKNOWN)

 protected:
  ~HuhiThemeGetHuhiThemeListFunction() override {}

  ResponseAction Run() override;
};

class HuhiThemeGetHuhiThemeTypeFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiTheme.getHuhiThemeType", UNKNOWN)

 protected:
  ~HuhiThemeGetHuhiThemeTypeFunction() override {}

  ResponseAction Run() override;
};

class HuhiThemeSetHuhiThemeTypeFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiTheme.setHuhiThemeType", UNKNOWN)

 protected:
  ~HuhiThemeSetHuhiThemeTypeFunction() override {}

  ResponseAction Run() override;
};

}  // namespace api
}  // namespace extensions

#endif  // HUHI_BROWSER_EXTENSIONS_API_HUHI_THEME_API_H_
