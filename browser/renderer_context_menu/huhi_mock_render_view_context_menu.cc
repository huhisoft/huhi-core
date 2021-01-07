/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/renderer_context_menu/huhi_mock_render_view_context_menu.h"

#include <string>

#include "base/strings/string_number_conversions.h"
#include "chrome/app/chrome_command_ids.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/renderer_context_menu/render_view_context_menu.h"
#include "chrome/grit/generated_resources.h"
#include "chrome/test/base/testing_profile.h"
#include "components/prefs/pref_service.h"
#include "content/public/browser/browser_context.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "ui/base/l10n/l10n_util.h"

HuhiMockRenderViewContextMenu::MockMenuItem::MockMenuItem()
    : command_id(0),
      enabled(false),
      checked(false),
      hidden(false),
      is_submenu(false),
      has_submenu(false) {}

HuhiMockRenderViewContextMenu::MockMenuItem::MockMenuItem(
    const MockMenuItem& other) = default;

HuhiMockRenderViewContextMenu::MockMenuItem::~MockMenuItem() {}

HuhiMockRenderViewContextMenu::MockMenuItem&
HuhiMockRenderViewContextMenu::MockMenuItem::operator=(
    const MockMenuItem& other) = default;

void HuhiMockRenderViewContextMenu::MockMenuItem::PrintMockMenuItem(
    unsigned int offset) const {
  std::cout << std::setfill(' ');
  if (offset)
    std::cout << std::setfill(' ') << std::setw(offset) << ' ';
  std::cout << (has_submenu ? "> " : "  ");
  if (command_id == -1) {
    std::cout << std::setfill(' ') << std::setw(9) << ' ';
    std::cout << std::setfill('-') << std::setw(15) << '-';
  } else {
    std::cout << std::setw(8) << command_id;
    std::cout << " " << title;
    if (!enabled || checked || hidden) {
      std::cout << " (";
      if (!enabled)
        std::cout << " disabled ";
      if (checked)
        std::cout << " checked ";
      if (hidden)
        std::cout << " hidden ";
      std::cout << ")";
    }
  }
  std::cout << std::endl;
}

HuhiMockRenderViewContextMenu::HuhiMockRenderViewContextMenu(Profile* profile)
    : observer_(nullptr), profile_(profile), enable_print_menu_(false) {}

HuhiMockRenderViewContextMenu::~HuhiMockRenderViewContextMenu() {}

// SimpleMenuModel::Delegate implementation.

bool HuhiMockRenderViewContextMenu::IsCommandIdChecked(int command_id) const {
  return observer_->IsCommandIdChecked(command_id);
}

bool HuhiMockRenderViewContextMenu::IsCommandIdEnabled(int command_id) const {
  return observer_->IsCommandIdEnabled(command_id);
}

void HuhiMockRenderViewContextMenu::ExecuteCommand(int command_id,
                                                    int event_flags) {
  observer_->ExecuteCommand(command_id);
}

// RenderViewContextMenuProxy implementation.

void HuhiMockRenderViewContextMenu::AddMenuItem(int command_id,
                                                 const base::string16& title) {
  MockMenuItem item;
  item.command_id = command_id;
  item.enabled = observer_->IsCommandIdEnabled(command_id);
  item.checked = false;
  item.hidden = false;
  item.title = title;
  items_.push_back(item);
}

void HuhiMockRenderViewContextMenu::AddMenuItemWithIcon(
    int command_id,
    const base::string16& title,
    const ui::ImageModel& icon) {
  AddMenuItem(command_id, title);
}

void HuhiMockRenderViewContextMenu::AddCheckItem(int command_id,
                                                  const base::string16& title) {
  MockMenuItem item;
  item.command_id = command_id;
  item.enabled = observer_->IsCommandIdEnabled(command_id);
  item.checked = observer_->IsCommandIdChecked(command_id);
  item.hidden = false;
  item.title = title;
  items_.push_back(item);
}

void HuhiMockRenderViewContextMenu::AddSeparator() {
  MockMenuItem item;
  item.command_id = -1;
  item.enabled = false;
  item.checked = false;
  item.hidden = false;
  items_.push_back(item);
}

void HuhiMockRenderViewContextMenu::AddSubMenu(int command_id,
                                                const base::string16& label,
                                                ui::MenuModel* model) {
  MockMenuItem item;
  item.command_id = command_id;
  item.enabled = observer_->IsCommandIdEnabled(command_id);
  item.checked = observer_->IsCommandIdChecked(command_id);
  item.hidden = false;
  item.title = label;
  item.has_submenu = true;
  items_.push_back(item);

  for (int i = 0; i < model->GetItemCount(); ++i) {
    MockMenuItem sub_item;
    sub_item.is_submenu = true;
    if (model->GetTypeAt(i) != ui::MenuModel::TYPE_SEPARATOR) {
      sub_item.command_id = model->GetCommandIdAt(i);
      sub_item.enabled = observer_->IsCommandIdSupported(sub_item.command_id)
                             ? model->IsEnabledAt(i)
                             : false;
      sub_item.checked = observer_->IsCommandIdSupported(sub_item.command_id)
                             ? model->IsItemCheckedAt(i)
                             : false;
      sub_item.hidden = !model->IsVisibleAt(i);
      sub_item.title = model->GetLabelAt(i);
    } else {
      sub_item.command_id = -1;
    }
    items_.push_back(sub_item);
  }
}

void HuhiMockRenderViewContextMenu::AddSubMenuWithStringIdAndIcon(
    int command_id,
    int message_id,
    ui::MenuModel* model,
    const ui::ImageModel& icon) {
  AddSubMenu(command_id, base::NumberToString16(message_id), model);
}

void HuhiMockRenderViewContextMenu::UpdateMenuItem(
    int command_id,
    bool enabled,
    bool hidden,
    const base::string16& title) {
  for (auto& item : items_) {
    if (item.command_id == command_id) {
      item.enabled = enabled;
      item.hidden = hidden;
      item.title = title;
      return;
    }
  }

  FAIL() << "Menu observer is trying to change a menu item it doesn't own."
         << " command_id: " << command_id;
}

void HuhiMockRenderViewContextMenu::UpdateMenuIcon(
    int command_id,
    const ui::ImageModel& image) {
  for (auto& item : items_) {
    if (item.command_id == command_id) {
      return;
    }
  }

  FAIL() << "Menu observer is trying to change a menu item it doesn't own."
         << " command_id: " << command_id;
}

void HuhiMockRenderViewContextMenu::RemoveMenuItem(int command_id) {
  auto it = items_.begin();
  while (it != items_.end()) {
    if (it->command_id == command_id) {
      bool submenu = it->has_submenu;
      it = items_.erase(it);
      if (submenu) {
        while (it != items_.end() && it->is_submenu)
          it = items_.erase(it);
      }
      break;
    } else {
      ++it;
    }
  }
}

void HuhiMockRenderViewContextMenu::RemoveAdjacentSeparators() {}

void HuhiMockRenderViewContextMenu::AddSpellCheckServiceItem(bool is_checked) {
  // Call the static method of RenderViewContextMenu which should our override
  // that doesn't add the item.
  RenderViewContextMenu::AddSpellCheckServiceItem(nullptr, is_checked);
}

void HuhiMockRenderViewContextMenu::AddAccessibilityLabelsServiceItem(
    bool is_checked) {}

content::RenderViewHost* HuhiMockRenderViewContextMenu::GetRenderViewHost()
    const {
  return nullptr;
}

content::BrowserContext* HuhiMockRenderViewContextMenu::GetBrowserContext()
    const {
  return profile_;
}

content::WebContents* HuhiMockRenderViewContextMenu::GetWebContents() const {
  return nullptr;
}

// Methods that don't implement inherited interfaces.

void HuhiMockRenderViewContextMenu::SetObserver(
    RenderViewContextMenuObserver* observer) {
  observer_ = observer;
}

size_t HuhiMockRenderViewContextMenu::GetMenuSize() const {
  return items_.size();
}

bool HuhiMockRenderViewContextMenu::GetMenuItem(size_t index,
                                                 MockMenuItem* item) const {
  if (index >= items_.size())
    return false;
  *item = items_[index];
  return true;
}

PrefService* HuhiMockRenderViewContextMenu::GetPrefs() {
  return profile_->GetPrefs();
}

void HuhiMockRenderViewContextMenu::PrintMenu(const std::string& title) const {
  if (!enable_print_menu_)
    return;

  std::cout << title << std::endl;
  std::cout << std::setfill('-') << std::setw(40) << '-' << std::endl;
  for (const auto& item : items_)
    item.PrintMockMenuItem(item.is_submenu ? 4 : 0);
  std::cout << std::setfill('-') << std::setw(40) << '-' << std::endl;
}

void HuhiMockRenderViewContextMenu::EnablePrintMenu(bool enable) {
  enable_print_menu_ = enable;
}
