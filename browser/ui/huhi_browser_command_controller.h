/* Copyright 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_HUHI_BROWSER_COMMAND_CONTROLLER_H_
#define HUHI_BROWSER_UI_HUHI_BROWSER_COMMAND_CONTROLLER_H_

#include "huhi/components/tor/buildflags/buildflags.h"
#include "chrome/browser/ui/browser_command_controller.h"

// This namespace is needed for a chromium_src override
namespace chrome {

class HuhiBrowserCommandController : public chrome::BrowserCommandController {
 public:
  explicit HuhiBrowserCommandController(Browser* browser);

#if BUILDFLAG(ENABLE_TOR)
  void UpdateCommandForTor();
#endif

 private:
  // Overriden from CommandUpdater:
  bool SupportsCommand(int id) const override;
  bool IsCommandEnabled(int id) const override;
  bool ExecuteCommandWithDisposition(
      int id,
      WindowOpenDisposition disposition,
      base::TimeTicks time_stamp = base::TimeTicks::Now()) override;
  void AddCommandObserver(int id, CommandObserver* observer) override;
  void RemoveCommandObserver(int id, CommandObserver* observer) override;
  void RemoveCommandObserver(CommandObserver* observer) override;
  bool UpdateCommandEnabled(int id, bool state) override;

  void InitHuhiCommandState();
  void UpdateCommandForHuhiRewards();
  void UpdateCommandForHuhiAdblock();
  void UpdateCommandForWebcompatReporter();
  void UpdateCommandForHuhiSync();
  void UpdateCommandForHuhiWallet();

  bool ExecuteHuhiCommandWithDisposition(int id,
                                          WindowOpenDisposition disposition,
                                          base::TimeTicks time_stamp);

  Browser* const browser_;

  CommandUpdaterImpl huhi_command_updater_;

  DISALLOW_COPY_AND_ASSIGN(HuhiBrowserCommandController);
};

}   // namespace chrome

#endif  // HUHI_BROWSER_UI_HUHI_BROWSER_COMMAND_CONTROLLER_H_
