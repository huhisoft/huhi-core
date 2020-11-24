/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/components/ipfs/browser/features.h"

#include "base/feature_list.h"

namespace ipfs {
namespace features {

const base::Feature kIpfsFeature {
      "Ipfs",
      base::FEATURE_DISABLED_BY_DEFAULT
};

}  // namespace features
}  // namespace ipfs
