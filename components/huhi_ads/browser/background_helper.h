/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_ADS_BROWSER_BACKGROUND_HELPER_H_
#define HUHI_COMPONENTS_HUHI_ADS_BROWSER_BACKGROUND_HELPER_H_

#include <string>

#include "base/macros.h"
#include "base/memory/singleton.h"
#include "base/observer_list.h"
#include "build/build_config.h"

namespace huhi_ads {

class BackgroundHelper {
 public:
  class Observer {
   public:
    virtual void OnBackground() = 0;
    virtual void OnForeground() = 0;
  };

  BackgroundHelper(const BackgroundHelper&) = delete;
  BackgroundHelper& operator=(const BackgroundHelper&) = delete;

  static BackgroundHelper* GetInstance();

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  void TriggerOnBackground();
  void TriggerOnForeground();

  virtual bool IsForeground() const;

 protected:
  friend struct base::DefaultSingletonTraits<BackgroundHelper>;

  BackgroundHelper();
  virtual ~BackgroundHelper();

 private:
  base::ObserverList<Observer>::Unchecked observers_;
};

}  // namespace huhi_ads

#endif  // HUHI_COMPONENTS_HUHI_ADS_BROWSER_BACKGROUND_HELPER_H_
