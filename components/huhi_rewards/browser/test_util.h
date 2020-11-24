/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_TEST_UTIL_H_
#define HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_TEST_UTIL_H_

#include <memory>

#include "base/files/file_path.h"

class KeyedService;
class Profile;

namespace huhi_rewards {

std::unique_ptr<Profile> CreateHuhiRewardsProfile(const base::FilePath& path);

}  // namespace huhi_rewards

#endif  // HUHI_COMPONENTS_HUHI_REWARDS_BROWSER_TEST_UTIL_H_
