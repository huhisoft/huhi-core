/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_SHIELDS_BROWSER_BASE_HUHI_SHIELDS_SERVICE_H_
#define HUHI_COMPONENTS_HUHI_SHIELDS_BROWSER_BASE_HUHI_SHIELDS_SERVICE_H_

#include <stdint.h>

#include <memory>
#include <string>
// TODO(huhi): <mutex> is an unapproved C++11 header
#include <mutex>  // NOLINT

#include "base/files/file_path.h"
#include "base/sequenced_task_runner.h"
#include "huhi/components/huhi_component_updater/browser/huhi_component.h"
#include "third_party/blink/public/mojom/loader/resource_load_info.mojom-shared.h"
#include "url/gurl.h"

using huhi_component_updater::HuhiComponent;

namespace huhi_shields {

// The huhi shields service in charge of checking huhi shields like ad-block,
// tracking protection, etc.
class BaseHuhiShieldsService : public HuhiComponent {
 public:
  explicit BaseHuhiShieldsService(HuhiComponent::Delegate* delegate);
  ~BaseHuhiShieldsService() override;
  bool Start();
  bool IsInitialized() const;
  virtual bool ShouldStartRequest(const GURL& url,
                                  blink::mojom::ResourceType resource_type,
                                  const std::string& tab_host,
                                  bool* did_match_exception,
                                  bool* cancel_request_explicitly,
                                  std::string* mock_data_url);

 protected:
  virtual bool Init() = 0;

 private:
  void InitShields();

  bool initialized_;
  std::mutex initialized_mutex_;
  scoped_refptr<base::SequencedTaskRunner> task_runner_;
};

}  // namespace huhi_shields

#endif  // HUHI_COMPONENTS_HUHI_SHIELDS_BROWSER_BASE_HUHI_SHIELDS_SERVICE_H_
