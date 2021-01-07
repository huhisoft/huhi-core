/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_CRYPTO_DOT_COM_BROWSER_CRYPTO_DOT_COM_PREF_UTILS_H_
#define HUHI_COMPONENTS_CRYPTO_DOT_COM_BROWSER_CRYPTO_DOT_COM_PREF_UTILS_H_

class PrefRegistrySimple;

namespace crypto_dot_com {

void RegisterPrefs(PrefRegistrySimple* registry);

}  // namespace crypto_dot_com

#endif  // HUHI_COMPONENTS_CRYPTO_DOT_COM_BROWSER_CRYPTO_DOT_COM_PREF_UTILS_H_
