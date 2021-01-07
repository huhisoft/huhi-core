/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_COMPONENT_UPDATER_HUHI_COMPONENT_UPDATER_DELEGATE_H_
#define HUHI_BROWSER_COMPONENT_UPDATER_HUHI_COMPONENT_UPDATER_DELEGATE_H_

#include <string>

#include "base/macros.h"
#include "huhi/components/huhi_component_updater/browser/huhi_component.h"

using huhi_component_updater::HuhiComponent;

namespace base {
class SequencedTaskRunner;
}

namespace huhi {

class HuhiComponentUpdaterDelegate : public HuhiComponent::Delegate {
 public:
  HuhiComponentUpdaterDelegate();
  ~HuhiComponentUpdaterDelegate() override;

  // huhi_component_updater::HuhiComponent::Delegate implementation
  void Register(const std::string& component_name,
                const std::string& component_base64_public_key,
                base::OnceClosure registered_callback,
                HuhiComponent::ReadyCallback ready_callback) override;
  bool Unregister(const std::string& component_id) override;
  void OnDemandUpdate(const std::string& component_id) override;
  scoped_refptr<base::SequencedTaskRunner> GetTaskRunner() override;

 private:
  scoped_refptr<base::SequencedTaskRunner> task_runner_;

  DISALLOW_COPY_AND_ASSIGN(HuhiComponentUpdaterDelegate);
};

}  // namespace huhi

#endif  // HUHI_BROWSER_COMPONENT_UPDATER_HUHI_COMPONENT_UPDATER_DELEGATE_H_
