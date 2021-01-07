/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_NET_NETWORK_HELPER_DELEGATE_H_
#define HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_NET_NETWORK_HELPER_DELEGATE_H_

#include "huhi/browser/net/url_context.h"

namespace huhi_rewards {

int OnBeforeURLRequest(
    const huhi::ResponseCallback& next_callback,
    std::shared_ptr<huhi::HuhiRequestInfo> ctx);

}  // namespace huhi_rewards

#endif  // HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_NET_NETWORK_HELPER_DELEGATE_H_
