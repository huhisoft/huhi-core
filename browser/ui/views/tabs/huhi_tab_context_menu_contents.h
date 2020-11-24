/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_VIEWS_TABS_HUHI_TAB_CONTEXT_MENU_CONTENTS_H_
#define HUHI_BROWSER_UI_VIEWS_TABS_HUHI_TAB_CONTEXT_MENU_CONTENTS_H_

#include <memory>

#include "ui/base/models/simple_menu_model.h"
#include "ui/base/ui_base_types.h"

class HuhiBrowserTabStripController;
class HuhiTabMenuModel;
class Browser;
class Tab;

namespace sessions {
class TabRestoreService;
}  // namespace sessions

namespace views {
class MenuRunner;
}  // namespace views

class HuhiTabContextMenuContents : public ui::SimpleMenuModel::Delegate {
 public:
  HuhiTabContextMenuContents(Tab* tab,
                              HuhiBrowserTabStripController* controller,
                              int index);
  ~HuhiTabContextMenuContents() override;

  void Cancel();

  void RunMenuAt(const gfx::Point& point, ui::MenuSourceType source_type);

  // ui::SimpleMenuModel::Delegate overrides:
  bool IsCommandIdChecked(int command_id) const override;
  bool IsCommandIdEnabled(int command_id) const override;
  bool GetAcceleratorForCommandId(int command_id,
                                  ui::Accelerator* accelerator) const override;
  void ExecuteCommand(int command_id, int event_flags) override;

 private:
  bool IsHuhiCommandIdEnabled(int command_id) const;
  void ExecuteHuhiCommand(int command_id);
  bool IsHuhiCommandId(int command_id) const;

  std::unique_ptr<HuhiTabMenuModel> model_;
  std::unique_ptr<views::MenuRunner> menu_runner_;

  Tab* tab_;
  Browser* browser_;
  sessions::TabRestoreService* restore_service_ = nullptr;
  HuhiBrowserTabStripController* controller_;

  DISALLOW_COPY_AND_ASSIGN(HuhiTabContextMenuContents);
};

#endif  // HUHI_BROWSER_UI_VIEWS_TABS_HUHI_TAB_CONTEXT_MENU_CONTENTS_H_
