/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/components/huhi_shields/browser/ad_block_custom_filters_service.h"

#include "base/logging.h"
#include "huhi/browser/huhi_browser_process_impl.h"
#include "huhi/common/pref_names.h"
#include "huhi/components/huhi_shields/browser/ad_block_service.h"
#include "huhi/vendor/adblock_rust_ffi/src/wrapper.hpp"
#include "components/prefs/pref_service.h"
#include "content/public/browser/browser_thread.h"

using huhi_component_updater::HuhiComponent;

namespace huhi_shields {

AdBlockCustomFiltersService::AdBlockCustomFiltersService(
    HuhiComponent::Delegate* delegate) : AdBlockBaseService(delegate) {
}

AdBlockCustomFiltersService::~AdBlockCustomFiltersService() {
}

bool AdBlockCustomFiltersService::Init() {
  return UpdateCustomFilters(GetCustomFilters());
}

std::string AdBlockCustomFiltersService::GetCustomFilters() {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
  PrefService* local_state = g_browser_process->local_state();
  if (!local_state)
    return std::string();
  return local_state->GetString(kAdBlockCustomFilters);
}

bool AdBlockCustomFiltersService::UpdateCustomFilters(
    const std::string& custom_filters) {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
  PrefService* local_state = g_browser_process->local_state();
  if (!local_state)
    return false;
  local_state->SetString(kAdBlockCustomFilters, custom_filters);

  GetTaskRunner()->PostTask(
      FROM_HERE,
      base::BindOnce(
          &AdBlockCustomFiltersService::UpdateCustomFiltersOnFileTaskRunner,
          base::Unretained(this), custom_filters));

  return true;
}

void AdBlockCustomFiltersService::UpdateCustomFiltersOnFileTaskRunner(
    const std::string& custom_filters) {
  DCHECK(GetTaskRunner()->RunsTasksInCurrentSequence());
  ad_block_client_.reset(new adblock::Engine(custom_filters.c_str()));
}

///////////////////////////////////////////////////////////////////////////////

std::unique_ptr<AdBlockCustomFiltersService>
AdBlockCustomFiltersServiceFactory(HuhiComponent::Delegate* delegate) {
  return std::make_unique<AdBlockCustomFiltersService>(delegate);
}

}  // namespace huhi_shields
