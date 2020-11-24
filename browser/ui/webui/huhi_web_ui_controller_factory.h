/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_WEBUI_HUHI_WEB_UI_CONTROLLER_FACTORY_H_
#define HUHI_BROWSER_UI_WEBUI_HUHI_WEB_UI_CONTROLLER_FACTORY_H_

#include <memory>

#include "chrome/browser/ui/webui/chrome_web_ui_controller_factory.h"

namespace base {
class RefCountedMemory;
}

class HuhiWebUIControllerFactory : public ChromeWebUIControllerFactory {
 public:
  content::WebUI::TypeID GetWebUIType(content::BrowserContext* browser_context,
                                      const GURL& url) override;
  std::unique_ptr<content::WebUIController> CreateWebUIControllerForURL(
      content::WebUI* web_ui,
      const GURL& url) override;

  static HuhiWebUIControllerFactory* GetInstance();

 protected:
  friend struct base::DefaultSingletonTraits<HuhiWebUIControllerFactory>;

  HuhiWebUIControllerFactory();
  ~HuhiWebUIControllerFactory() override;

 private:
  DISALLOW_COPY_AND_ASSIGN(HuhiWebUIControllerFactory);
};

#endif  // HUHI_BROWSER_UI_WEBUI_HUHI_WEB_UI_CONTROLLER_FACTORY_H_
