/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_VIEWS_TABS_HUHI_BROWSER_TAB_STRIP_CONTROLLER_H_
#define HUHI_BROWSER_UI_VIEWS_TABS_HUHI_BROWSER_TAB_STRIP_CONTROLLER_H_

#include <memory>

#include "chrome/browser/ui/views/tabs/browser_tab_strip_controller.h"

class HuhiTabContextMenuContents;

class HuhiBrowserTabStripController : public BrowserTabStripController {
 public:
  HuhiBrowserTabStripController(TabStripModel* model,
                                 BrowserView* browser_view,
                                 std::unique_ptr<TabMenuModelFactory>
                                     menu_model_factory_override = nullptr);
  ~HuhiBrowserTabStripController() override;

  // BrowserTabStripController overrides:
  void ShowContextMenuForTab(Tab* tab,
                             const gfx::Point& p,
                             ui::MenuSourceType source_type) override;

 private:
  // If non-NULL it means we're showing a menu for the tab.
  std::unique_ptr<HuhiTabContextMenuContents> context_menu_contents_;

  DISALLOW_COPY_AND_ASSIGN(HuhiBrowserTabStripController);
};

#endif  // HUHI_BROWSER_UI_VIEWS_TABS_HUHI_BROWSER_TAB_STRIP_CONTROLLER_H_
