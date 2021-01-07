/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_HUHI_WALLET_HUHI_WALLET_DELEGATE_IMPL_H_
#define HUHI_BROWSER_HUHI_WALLET_HUHI_WALLET_DELEGATE_IMPL_H_

#include "huhi/components/huhi_wallet/huhi_wallet_delegate.h"

class HuhiWalletDelegateImpl : public HuhiWalletDelegate {
 public:
  ~HuhiWalletDelegateImpl() override;
  void LoadCryptoWalletsExtension(content::BrowserContext* context) override;
};

#endif  // HUHI_BROWSER_HUHI_WALLET_HUHI_WALLET_DELEGATE_IMPL_H_
