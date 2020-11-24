/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_TOOLBAR_HUHI_APP_MENU_MODEL_H_
#define HUHI_BROWSER_UI_TOOLBAR_HUHI_APP_MENU_MODEL_H_

#include "chrome/browser/ui/toolbar/app_menu_model.h"

class HuhiAppMenuModel : public AppMenuModel {
 public:
  using AppMenuModel::AppMenuModel;
  ~HuhiAppMenuModel() override;

  HuhiAppMenuModel(const HuhiAppMenuModel&) = delete;
  HuhiAppMenuModel& operator=(const HuhiAppMenuModel&) = delete;

 private:
  // AppMenuModel overrides:
  void Build() override;

  void InsertHuhiMenuItems();
  int GetIndexOfHuhiRewardsItem() const;
  int GetIndexOfHuhiAdBlockItem() const;
  int GetIndexOfHuhiSyncItem() const;
};

#endif  // HUHI_BROWSER_UI_TOOLBAR_HUHI_APP_MENU_MODEL_H_
