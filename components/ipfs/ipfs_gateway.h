/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_IPFS_IPFS_GATEWAY_H_
#define HUHI_COMPONENTS_IPFS_IPFS_GATEWAY_H_

#include "url/gurl.h"

namespace ipfs {

void SetIPFSDefaultGatewayForTest(const GURL& url);
GURL GetDefaultIPFSLocalGateway();
GURL GetDefaultIPFSGateway();

}  // namespace ipfs

#endif  // HUHI_COMPONENTS_IPFS_IPFS_GATEWAY_H_
