/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_COMPONENTS_INFOBARS_CORE_INFOBAR_DELEGATE_H_
#define HUHI_CHROMIUM_SRC_COMPONENTS_INFOBARS_CORE_INFOBAR_DELEGATE_H_

#define HUHI_INFOBAR_DELEGATE_IDENTIFIERS \
    HUHI_CONFIRM_P3A_INFOBAR_DELEGATE = 500, \
    CRYPTO_WALLETS_INFOBAR_DELEGATE = 501, \
    WAYBACK_MACHINE_INFOBAR_DELEGATE = 502, \
    SYNC_V2_MIGRATE_INFOBAR_DELEGATE = 503, \
    IPFS_INFOBAR_DELEGATE = 504,

#include "../../../../../components/infobars/core/infobar_delegate.h"

#undef HUHI_INFOBAR_DELEGATE_IDENTIFIERS

#endif  // HUHI_CHROMIUM_SRC_COMPONENTS_INFOBARS_CORE_INFOBAR_DELEGATE_H_
