/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_SEARCH_ENGINES_PRIVATE_WINDOW_SEARCH_ENGINE_PROVIDER_SERVICE_H_
#define HUHI_BROWSER_SEARCH_ENGINES_PRIVATE_WINDOW_SEARCH_ENGINE_PROVIDER_SERVICE_H_

#include "huhi/browser/search_engines/search_engine_provider_service.h"
#include "components/search_engines/template_url_service_observer.h"

class PrivateWindowSearchEngineProviderService
    : public SearchEngineProviderService,
      public TemplateURLServiceObserver {
 public:
  explicit PrivateWindowSearchEngineProviderService(Profile* otr_profile);
  ~PrivateWindowSearchEngineProviderService() override;

 private:
  // Configure appropriate provider according to prefs.
  void ConfigureSearchEngineProvider();

  // TemplateURLServiceObserver overrides:
  void OnTemplateURLServiceChanged() override;

  // SearchEngineProviderService overrides:
  void OnUseAlternativeSearchEngineProviderChanged() override;

  DISALLOW_COPY_AND_ASSIGN(PrivateWindowSearchEngineProviderService);
};

#endif  // HUHI_BROWSER_SEARCH_ENGINES_PRIVATE_WINDOW_SEARCH_ENGINE_PROVIDER_SERVICE_H_
