/* Copyright 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_HUHI_REWARDS_TIP_DIALOG_H_
#define HUHI_BROWSER_HUHI_REWARDS_TIP_DIALOG_H_

#include <memory>
#include <string>

namespace base {
class DictionaryValue;
}

namespace content {
class WebContents;
}

namespace huhi_rewards {

void OpenTipDialog(content::WebContents* initiator,
                   std::unique_ptr<base::DictionaryValue> params);

}

#endif  // HUHI_BROWSER_HUHI_REWARDS_TIP_DIALOG_H_
