/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/components/huhi_shields/browser/base_huhi_shields_service.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "base/bind.h"
#include "base/bind_helpers.h"
#include "base/logging.h"
#include "base/macros.h"
#include "base/memory/ptr_util.h"

using huhi_component_updater::HuhiComponent;

namespace huhi_shields {

BaseHuhiShieldsService::BaseHuhiShieldsService(
    HuhiComponent::Delegate* delegate)
    : HuhiComponent(delegate),
      initialized_(false) {
}

BaseHuhiShieldsService::~BaseHuhiShieldsService() {
}

bool BaseHuhiShieldsService::IsInitialized() const {
  return initialized_;
}

void BaseHuhiShieldsService::InitShields() {
  if (Init()) {
    std::lock_guard<std::mutex> guard(initialized_mutex_);
    initialized_ = true;
  }
}

bool BaseHuhiShieldsService::Start() {
  if (initialized_) {
    return true;
  }

  InitShields();
  return false;
}

bool BaseHuhiShieldsService::ShouldStartRequest(
    const GURL& url,
    blink::mojom::ResourceType resource_type,
    const std::string& tab_host,
    bool* did_match_exception,
    bool* cancel_request_explicitly,
    std::string* mock_data_url) {
  if (did_match_exception) {
    *did_match_exception = false;
  }
  // Intentionally don't set cancel_request_explicitly
  return true;
}

}  // namespace huhi_shields
