/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_IPFS_COMMON_IPFS_UTILS_H_
#define HUHI_COMPONENTS_IPFS_COMMON_IPFS_UTILS_H_

class GURL;

namespace ipfs {

class IpfsUtils {
 public:
  static bool IsIPFSURL(const GURL& url);
};

}  // namespace ipfs

#endif  // HUHI_COMPONENTS_IPFS_COMMON_IPFS_UTILS_H_
