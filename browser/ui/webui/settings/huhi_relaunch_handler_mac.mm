/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/ui/webui/settings/huhi_relaunch_handler_mac.h"

#include "base/bind.h"
#import "huhi/browser/mac/sparkle_glue.h"

void HuhiRelaunchHandler::RegisterMessages() {
  web_ui()->RegisterMessageCallback(
      "relaunchOnMac",
      base::BindRepeating(&HuhiRelaunchHandler::Relaunch,
                          base::Unretained(this)));
}

void HuhiRelaunchHandler::Relaunch(const base::ListValue* args) {
  [[SparkleGlue sharedSparkleGlue] relaunch];
}
