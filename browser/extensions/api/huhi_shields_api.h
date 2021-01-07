/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_EXTENSIONS_API_HUHI_SHIELDS_API_H_
#define HUHI_BROWSER_EXTENSIONS_API_HUHI_SHIELDS_API_H_

#include <memory>
#include <string>
#include <vector>

#include "extensions/browser/extension_function.h"

namespace extensions {
namespace api {

class HuhiShieldsUrlCosmeticResourcesFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiShields.urlCosmeticResources", UNKNOWN)

 protected:
  ~HuhiShieldsUrlCosmeticResourcesFunction() override {}

  ResponseAction Run() override;

 private:
  std::unique_ptr<base::ListValue> GetUrlCosmeticResourcesOnTaskRunner(
      const std::string& url);
  void GetUrlCosmeticResourcesOnUI(std::unique_ptr<base::ListValue> resources);
};

class HuhiShieldsHiddenClassIdSelectorsFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiShields.hiddenClassIdSelectors", UNKNOWN)

 protected:
  ~HuhiShieldsHiddenClassIdSelectorsFunction() override {}

  ResponseAction Run() override;

 private:
  std::unique_ptr<base::ListValue> GetHiddenClassIdSelectorsOnTaskRunner(
      const std::vector<std::string>& classes,
      const std::vector<std::string>& ids,
      const std::vector<std::string>& exceptions);
  void GetHiddenClassIdSelectorsOnUI(
      std::unique_ptr<base::ListValue> selectors);
};

class HuhiShieldsAllowScriptsOnceFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiShields.allowScriptsOnce", UNKNOWN)

 protected:
  ~HuhiShieldsAllowScriptsOnceFunction() override {}

  ResponseAction Run() override;
};

class HuhiShieldsOpenBrowserActionUIFunction :
    public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiShields.openBrowserActionUI", UNKNOWN)

 protected:
  ~HuhiShieldsOpenBrowserActionUIFunction() override;

  ResponseAction Run() override;
};

class HuhiShieldsSetHuhiShieldsEnabledFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiShields.setHuhiShieldsEnabled", UNKNOWN)

 protected:
  ~HuhiShieldsSetHuhiShieldsEnabledFunction() override {}

  ResponseAction Run() override;
};

class HuhiShieldsGetHuhiShieldsEnabledFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiShields.getHuhiShieldsEnabled", UNKNOWN)

 protected:
  ~HuhiShieldsGetHuhiShieldsEnabledFunction() override {}

  ResponseAction Run() override;
};

class HuhiShieldsShouldDoCosmeticFilteringFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiShields.shouldDoCosmeticFiltering", UNKNOWN)

 protected:
  ~HuhiShieldsShouldDoCosmeticFilteringFunction() override {}

  ResponseAction Run() override;
};

class HuhiShieldsSetCosmeticFilteringControlTypeFunction :
    public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiShields.setCosmeticFilteringControlType",
                             UNKNOWN)

 protected:
  ~HuhiShieldsSetCosmeticFilteringControlTypeFunction() override {}

  ResponseAction Run() override;
};

class HuhiShieldsIsFirstPartyCosmeticFilteringEnabledFunction :
    public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION(
      "huhiShields.isFirstPartyCosmeticFilteringEnabled",
      UNKNOWN)

 protected:
  ~HuhiShieldsIsFirstPartyCosmeticFilteringEnabledFunction() override {}

  ResponseAction Run() override;
};

class HuhiShieldsSetAdControlTypeFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiShields.setAdControlType", UNKNOWN)

 protected:
  ~HuhiShieldsSetAdControlTypeFunction() override {}

  ResponseAction Run() override;
};

class HuhiShieldsGetAdControlTypeFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiShields.getAdControlType", UNKNOWN)

 protected:
  ~HuhiShieldsGetAdControlTypeFunction() override {}

  ResponseAction Run() override;
};

class HuhiShieldsSetCookieControlTypeFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiShields.setCookieControlType", UNKNOWN)

 protected:
  ~HuhiShieldsSetCookieControlTypeFunction() override {}

  ResponseAction Run() override;
};

class HuhiShieldsGetCookieControlTypeFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiShields.getCookieControlType", UNKNOWN)

 protected:
  ~HuhiShieldsGetCookieControlTypeFunction() override {}

  ResponseAction Run() override;
};

class HuhiShieldsSetFingerprintingControlTypeFunction
    : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiShields.setFingerprintingControlType",
                             UNKNOWN)

 protected:
  ~HuhiShieldsSetFingerprintingControlTypeFunction() override {}

  ResponseAction Run() override;
};

class HuhiShieldsGetFingerprintingControlTypeFunction
    : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiShields.getFingerprintingControlType",
                             UNKNOWN)

 protected:
  ~HuhiShieldsGetFingerprintingControlTypeFunction() override {}

  ResponseAction Run() override;
};

class HuhiShieldsSetHTTPSEverywhereEnabledFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiShields.setHTTPSEverywhereEnabled",
                             UNKNOWN)

 protected:
  ~HuhiShieldsSetHTTPSEverywhereEnabledFunction() override {}

  ResponseAction Run() override;
};

class HuhiShieldsGetHTTPSEverywhereEnabledFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiShields.getHTTPSEverywhereEnabled",
                             UNKNOWN)

 protected:
  ~HuhiShieldsGetHTTPSEverywhereEnabledFunction() override {}

  ResponseAction Run() override;
};

class HuhiShieldsSetNoScriptControlTypeFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiShields.setNoScriptControlType", UNKNOWN)

 protected:
  ~HuhiShieldsSetNoScriptControlTypeFunction() override {}

  ResponseAction Run() override;
};

class HuhiShieldsGetNoScriptControlTypeFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiShields.getNoScriptControlType", UNKNOWN)

 protected:
  ~HuhiShieldsGetNoScriptControlTypeFunction() override {}

  ResponseAction Run() override;
};

// Notifies the browser that the shields panel was shown to the user.
class HuhiShieldsOnShieldsPanelShownFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiShields.onShieldsPanelShown", UNKNOWN)

 protected:
  ~HuhiShieldsOnShieldsPanelShownFunction() override {}

  // ExtensionFunction:
  ResponseAction Run() override;
};

class HuhiShieldsReportBrokenSiteFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("huhiShields.reportBrokenSite", UNKNOWN)

 protected:
  ~HuhiShieldsReportBrokenSiteFunction() override {}

  ResponseAction Run() override;
};

}  // namespace api
}  // namespace extensions

#endif  // HUHI_BROWSER_EXTENSIONS_API_HUHI_SHIELDS_API_H_
