/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_SHIELDS_BROWSER_AD_BLOCK_CUSTOM_FILTERS_SERVICE_H_
#define HUHI_COMPONENTS_HUHI_SHIELDS_BROWSER_AD_BLOCK_CUSTOM_FILTERS_SERVICE_H_

#include <memory>
#include <string>

#include "huhi/components/huhi_shields/browser/ad_block_base_service.h"

class AdBlockServiceTest;

using huhi_component_updater::HuhiComponent;

namespace huhi_shields {

// The huhi shields service in charge of custom filter ad-block
// checking and init.
class AdBlockCustomFiltersService : public AdBlockBaseService {
 public:
  explicit AdBlockCustomFiltersService(HuhiComponent::Delegate* delegate);
  ~AdBlockCustomFiltersService() override;

  std::string GetCustomFilters();
  bool UpdateCustomFilters(const std::string& custom_filters);

 protected:
  bool Init() override;

 private:
  friend class ::AdBlockServiceTest;
  void UpdateCustomFiltersOnFileTaskRunner(const std::string& custom_filters);

  DISALLOW_COPY_AND_ASSIGN(AdBlockCustomFiltersService);
};

// Creates the AdBlockCustomFiltersService
std::unique_ptr<AdBlockCustomFiltersService>
AdBlockCustomFiltersServiceFactory(HuhiComponent::Delegate* delegate);

}  // namespace huhi_shields

#endif  // HUHI_COMPONENTS_HUHI_SHIELDS_BROWSER_AD_BLOCK_CUSTOM_FILTERS_SERVICE_H_
