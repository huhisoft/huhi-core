/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/ui/toolbar/huhi_location_bar_model_delegate.h"

#include "base/strings/utf_string_conversions.h"
#include "huhi/components/huhi_wallet/buildflags/buildflags.h"
#include "extensions/buildflags/buildflags.h"
#include "testing/gtest/include/gtest/gtest.h"

#if BUILDFLAG(HUHI_WALLET_ENABLED)
#include "huhi/components/huhi_wallet/huhi_wallet_constants.h"
#endif

using HuhiLocationBarModelDelegateTest = testing::Test;

#if BUILDFLAG(HUHI_WALLET_ENABLED)
TEST_F(HuhiLocationBarModelDelegateTest, ResolvesEthereumRemoteClient) {
  GURL url(ethereum_remote_client_base_url);
  base::string16 formatted_url = base::UTF8ToUTF16(url.spec());
  HuhiLocationBarModelDelegate::FormattedStringFromURL(url, &formatted_url);
  ASSERT_STREQ(base::UTF16ToASCII(formatted_url).c_str(), "huhi://wallet");
}
TEST_F(HuhiLocationBarModelDelegateTest,
    ResolvesEthereumRemoteClientPhishingRoute) {
  GURL url(ethereum_remote_client_phishing_url);
  base::string16 formatted_url = base::UTF8ToUTF16(url.spec());
  HuhiLocationBarModelDelegate::FormattedStringFromURL(url, &formatted_url);
  ASSERT_STREQ(base::UTF16ToASCII(formatted_url).c_str(), "huhi://wallet");
}
TEST_F(HuhiLocationBarModelDelegateTest,
    ResolvesEthereumRemoteClientENSRoute) {
  GURL url(ethereum_remote_client_ens_redirect_url);
  base::string16 formatted_url = base::UTF8ToUTF16(url.spec());
  HuhiLocationBarModelDelegate::FormattedStringFromURL(url, &formatted_url);
  ASSERT_STREQ(base::UTF16ToASCII(formatted_url).c_str(), "huhi://wallet");
}
#endif

TEST_F(HuhiLocationBarModelDelegateTest, ResolvesChromeSchemeToHuhi) {
  GURL url("chrome://sync/");
  base::string16 formatted_url = base::UTF8ToUTF16(url.spec());
  HuhiLocationBarModelDelegate::FormattedStringFromURL(url, &formatted_url);
  ASSERT_STREQ(base::UTF16ToASCII(formatted_url).c_str(), "huhi://sync/");
}
