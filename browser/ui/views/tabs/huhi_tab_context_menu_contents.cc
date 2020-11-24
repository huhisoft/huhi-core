/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/ui/views/tabs/huhi_tab_context_menu_contents.h"

#include "huhi/browser/ui/tabs/huhi_tab_menu_model.h"
#include "huhi/browser/ui/views/tabs/huhi_browser_tab_strip_controller.h"
#include "chrome/browser/defaults.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/sessions/tab_restore_service_factory.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_commands.h"
#include "chrome/browser/ui/views/tabs/tab.h"
#include "components/sessions/core/tab_restore_service.h"
#include "ui/views/controls/menu/menu_runner.h"

HuhiTabContextMenuContents::HuhiTabContextMenuContents(
    Tab* tab,
    HuhiBrowserTabStripController* controller,
    int index)
    : tab_(tab),
      browser_(const_cast<Browser*>(controller->browser())),
      controller_(controller) {
  model_ = std::make_unique<HuhiTabMenuModel>(
      this, controller->model(), index);
  restore_service_ =
      TabRestoreServiceFactory::GetForProfile(browser_->profile());
  menu_runner_ = std::make_unique<views::MenuRunner>(
      model_.get(),
      views::MenuRunner::HAS_MNEMONICS | views::MenuRunner::CONTEXT_MENU);
}

HuhiTabContextMenuContents::~HuhiTabContextMenuContents() {
}

void HuhiTabContextMenuContents::Cancel() {
  controller_ = nullptr;
}

void HuhiTabContextMenuContents::RunMenuAt(
    const gfx::Point& point,
    ui::MenuSourceType source_type) {
  menu_runner_->RunMenuAt(tab_->GetWidget(), nullptr,
                          gfx::Rect(point, gfx::Size()),
                          views::MenuAnchorPosition::kTopLeft, source_type);
}

bool HuhiTabContextMenuContents::IsCommandIdChecked(int command_id) const {
  return false;
}

bool HuhiTabContextMenuContents::IsCommandIdEnabled(int command_id) const {
  if (IsHuhiCommandId(command_id))
    return IsHuhiCommandIdEnabled(command_id);

  return controller_->IsCommandEnabledForTab(
      static_cast<TabStripModel::ContextMenuCommand>(command_id),
      tab_);
}

bool HuhiTabContextMenuContents::GetAcceleratorForCommandId(
    int command_id,
    ui::Accelerator* accelerator) const {
  if (IsHuhiCommandId(command_id))
    return false;

  int browser_cmd;
  return TabStripModel::ContextMenuCommandToBrowserCommand(command_id,
                                                           &browser_cmd) ?
      tab_->GetWidget()->GetAccelerator(browser_cmd, accelerator) : false;
}

void HuhiTabContextMenuContents::ExecuteCommand(int command_id,
                                                 int event_flags) {
  if (IsHuhiCommandId(command_id))
    return ExecuteHuhiCommand(command_id);

  // Executing the command destroys |this|, and can also end up destroying
  // |controller_|. So stop the highlights before executing the command.
  controller_->ExecuteCommandForTab(
      static_cast<TabStripModel::ContextMenuCommand>(command_id),
      tab_);
}

bool HuhiTabContextMenuContents::IsHuhiCommandIdEnabled(
    int command_id) const {
  switch (command_id) {
    case HuhiTabMenuModel::CommandRestoreTab:
      return restore_service_ && (!restore_service_->IsLoaded() ||
                                  !restore_service_->entries().empty());
      break;
    case HuhiTabMenuModel::CommandBookmarkAllTabs:
      if (browser_) {
        return browser_defaults::bookmarks_enabled &&
               chrome::CanBookmarkAllTabs(browser_);
      }
      break;
    default:
      NOTREACHED();
      break;
  }

  return false;
}

void HuhiTabContextMenuContents::ExecuteHuhiCommand(int command_id) {
  switch (command_id) {
    case HuhiTabMenuModel::CommandRestoreTab:
      chrome::RestoreTab(browser_);
      return;
    case HuhiTabMenuModel::CommandBookmarkAllTabs:
      chrome::BookmarkAllTabs(browser_);
      return;
    default:
      NOTREACHED();
      return;
  }
}

bool HuhiTabContextMenuContents::IsHuhiCommandId(int command_id) const {
  return command_id > HuhiTabMenuModel::CommandStart &&
         command_id < HuhiTabMenuModel::CommandLast;
}
