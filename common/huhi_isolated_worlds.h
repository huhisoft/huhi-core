/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMMON_HUHI_ISOLATED_WORLDS_H_
#define HUHI_COMMON_HUHI_ISOLATED_WORLDS_H_

#include "content/public/common/isolated_world_ids.h"

enum HuhiIsolatedWorldIDs {
    // Isolated world ID for Greaselion (Google Translate reserves END + 1)
    ISOLATED_WORLD_ID_GREASELION = content::ISOLATED_WORLD_ID_CONTENT_END + 2,
};

#endif  // HUHI_COMMON_HUHI_ISOLATED_WORLDS_H_
