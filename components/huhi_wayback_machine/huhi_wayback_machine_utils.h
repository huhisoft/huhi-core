/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_WAYBACK_MACHINE_HUHI_WAYBACK_MACHINE_UTILS_H_
#define HUHI_COMPONENTS_HUHI_WAYBACK_MACHINE_HUHI_WAYBACK_MACHINE_UTILS_H_

class GURL;

bool IsWaybackMachineDisabledFor(const GURL& url);

#endif  // HUHI_COMPONENTS_HUHI_WAYBACK_MACHINE_HUHI_WAYBACK_MACHINE_UTILS_H_
