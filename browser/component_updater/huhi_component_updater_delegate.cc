/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/component_updater/huhi_component_updater_delegate.h"

#include <utility>

#include "base/sequenced_task_runner.h"
#include "base/task/post_task.h"
#include "huhi/browser/component_updater/huhi_component_installer.h"
#include "huhi/components/huhi_component_updater/browser/huhi_on_demand_updater.h"
#include "chrome/browser/browser_process.h"
#include "components/component_updater/component_updater_service.h"

using huhi_component_updater::HuhiComponent;
using huhi_component_updater::HuhiOnDemandUpdater;

namespace huhi {

HuhiComponentUpdaterDelegate::HuhiComponentUpdaterDelegate()
    : task_runner_(base::CreateSequencedTaskRunner(
          {base::ThreadPool(), base::MayBlock(),
           base::TaskPriority::USER_VISIBLE,
           base::TaskShutdownBehavior::SKIP_ON_SHUTDOWN})) {}

HuhiComponentUpdaterDelegate::~HuhiComponentUpdaterDelegate() {}

void HuhiComponentUpdaterDelegate::Register(
    const std::string& component_name,
    const std::string& component_base64_public_key,
    base::OnceClosure registered_callback,
    HuhiComponent::ReadyCallback ready_callback) {
  huhi::RegisterComponent(g_browser_process->component_updater(),
                           component_name,
                           component_base64_public_key,
                           std::move(registered_callback),
                           std::move(ready_callback));
}

bool HuhiComponentUpdaterDelegate::Unregister(
    const std::string& component_id) {
  return g_browser_process->component_updater()->UnregisterComponent(
      component_id);
}

void HuhiComponentUpdaterDelegate::OnDemandUpdate(
    const std::string& component_id) {
  HuhiOnDemandUpdater::GetInstance()->OnDemandUpdate(component_id);
}

scoped_refptr<base::SequencedTaskRunner>
HuhiComponentUpdaterDelegate::GetTaskRunner() {
  return task_runner_;
}

}  // namespace huhi
