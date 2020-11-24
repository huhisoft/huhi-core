/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_IPFS_COMMON_IPFS_CONSTANTS_H_
#define HUHI_COMPONENTS_IPFS_COMMON_IPFS_CONSTANTS_H_

namespace ipfs {

extern const char kServerEndpoint[];
extern const char kSwarmPeersPath[];
extern const char kConfigPath[];
extern const char kArgQueryParam[];
extern const char kAddressesField[];
extern const char kShutdownPath[];

enum class IPFSResolveMethodTypes {
  IPFS_GATEWAY,
  IPFS_LOCAL,
  IPFS_DISABLED,
};

}  // namespace ipfs

#endif  // HUHI_COMPONENTS_IPFS_COMMON_IPFS_CONSTANTS_H_
