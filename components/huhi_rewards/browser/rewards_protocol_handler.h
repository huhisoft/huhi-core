/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_REWARDS_PROTOCOL_HANDLER_H_
#define HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_REWARDS_PROTOCOL_HANDLER_H_

#include <string>

#include "chrome/browser/external_protocol/external_protocol_handler.h"
#include "chrome/browser/profiles/profile.h"

namespace huhi_rewards {

void HandleRewardsProtocol(const GURL& url,
                           content::WebContents::OnceGetter web_contents_getter,
                           ui::PageTransition page_transition,
                           bool has_user_gesture);

bool IsRewardsProtocol(const GURL& url);

}  // namespace huhi_rewards

#endif  // HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_REWARDS_PROTOCOL_HANDLER_H_
