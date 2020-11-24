/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_EXTENSIONS_API_GREASELION_API_H_
#define HUHI_BROWSER_EXTENSIONS_API_GREASELION_API_H_

#include "extensions/browser/extension_function.h"

namespace extensions {
namespace api {

class GreaselionIsGreaselionExtensionFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("greaselion.isGreaselionExtension", UNKNOWN)

 protected:
  ~GreaselionIsGreaselionExtensionFunction() override {}

  ResponseAction Run() override;
};

}  // namespace api
}  // namespace extensions

#endif  // HUHI_BROWSER_EXTENSIONS_API_GREASELION_API_H_
