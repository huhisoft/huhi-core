/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_DEVTOOLS_HUHI_DEVTOOLS_UI_BINDINGS_H_
#define HUHI_BROWSER_DEVTOOLS_HUHI_DEVTOOLS_UI_BINDINGS_H_

#include "chrome/browser/devtools/devtools_ui_bindings.h"

class HuhiDevToolsUIBindings : public DevToolsUIBindings {
 public:
  using DevToolsUIBindings::DevToolsUIBindings;

 private:
  FRIEND_TEST_ALL_PREFIXES(HuhiDevToolsUIBindingsBrowserTest, ThemeTest);

  // DevToolsUIBindings overrides:
  void GetPreferences(const DispatchCallback& callback) override;

  DISALLOW_COPY_AND_ASSIGN(HuhiDevToolsUIBindings);
};

#endif  // HUHI_BROWSER_DEVTOOLS_HUHI_DEVTOOLS_UI_BINDINGS_H_
