/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMMON_SHIELD_EXCEPTIONS_H_
#define HUHI_COMMON_SHIELD_EXCEPTIONS_H_

class GURL;

namespace huhi {

bool IsUAWhitelisted(const GURL& gurl);

}  // namespace huhi

#endif  // HUHI_COMMON_SHIELD_EXCEPTIONS_H_
