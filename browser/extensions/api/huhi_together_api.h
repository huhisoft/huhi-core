/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_EXTENSIONS_API_HUHI_TOGETHER_API_H_
#define HUHI_BROWSER_EXTENSIONS_API_HUHI_TOGETHER_API_H_

#include <map>
#include <string>

#include "extensions/browser/extension_function.h"

class Profile;

namespace extensions {
namespace api {

class HuhiTogetherIsSupportedFunction :
    public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiTogether.isSupported", UNKNOWN)

 protected:
  ~HuhiTogetherIsSupportedFunction() override {}
  ResponseAction Run() override;
};

}  // namespace api
}  // namespace extensions

#endif  // HUHI_BROWSER_EXTENSIONS_API_HUHI_TOGETHER_API_H_
