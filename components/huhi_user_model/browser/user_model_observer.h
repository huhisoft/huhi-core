/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_USER_MODEL_BROWSER_USER_MODEL_OBSERVER_H_
#define HUHI_COMPONENTS_HUHI_USER_MODEL_BROWSER_USER_MODEL_OBSERVER_H_

#include <string>

#include "base/observer_list.h"

namespace huhi_user_model {

class Observer : public base::CheckedObserver {
 public:
  virtual void OnUserModelUpdated(
      const std::string& id) = 0;

 protected:
  ~Observer() override = default;
};

}  // namespace huhi_user_model

#endif  // HUHI_COMPONENTS_HUHI_USER_MODEL_BROWSER_USER_MODEL_OBSERVER_H_
