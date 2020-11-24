/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/ui/tabs/huhi_tab_menu_model.h"

#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/sessions/tab_restore_service_factory.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_finder.h"
#include "chrome/browser/ui/tabs/tab_strip_model.h"
#include "chrome/grit/generated_resources.h"
#include "components/sessions/core/tab_restore_service.h"

HuhiTabMenuModel::HuhiTabMenuModel(ui::SimpleMenuModel::Delegate* delegate,
                                     TabStripModel* tab_strip_model,
                                     int index)
    : TabMenuModel(delegate, tab_strip_model, index) {
  web_contents_ = tab_strip_model->GetWebContentsAt(index);
  if (web_contents_) {
    Browser* browser = chrome::FindBrowserWithWebContents(web_contents_);
    restore_service_ =
        TabRestoreServiceFactory::GetForProfile(browser->profile());
  }

  Build();
}

HuhiTabMenuModel::~HuhiTabMenuModel() {
}

int HuhiTabMenuModel::GetRestoreTabCommandStringId() const {
  int id = IDS_RESTORE_TAB;

  if (!web_contents_)
    return id;

  if (!restore_service_)
    return id;

  if (!restore_service_->IsLoaded() || restore_service_->entries().empty())
    return id;

  if (restore_service_->entries().front()->type ==
          sessions::TabRestoreService::WINDOW) {
      id = IDS_RESTORE_WINDOW;
  }

  return id;
}

void HuhiTabMenuModel::Build() {
  AddSeparator(ui::NORMAL_SEPARATOR);
  AddItemWithStringId(CommandRestoreTab, GetRestoreTabCommandStringId());
  AddItemWithStringId(CommandBookmarkAllTabs, IDS_TAB_CXMENU_BOOKMARK_ALL_TABS);
}
