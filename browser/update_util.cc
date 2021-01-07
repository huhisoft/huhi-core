/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/update_util.h"

#include "base/command_line.h"
#include "huhi/common/huhi_switches.h"

namespace huhi {

bool UpdateEnabled() {
#if defined(OFFICIAL_BUILD)
  return !base::CommandLine::ForCurrentProcess()->HasSwitch(
      switches::kDisableHuhiUpdate);
#else
  return false;
#endif
}

}  //namespace huhi
