/* Copyright (c) 2019 The Huhi Software Team. Distributed under the MPL2
 * license. This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/net/huhi_ad_block_tp_network_delegate_helper.h"

#include <memory>
#include <string>
#include <vector>

#include "huhi/browser/net/url_context.h"
#include "huhi/common/network_constants.h"
#include "net/base/net_errors.h"
#include "testing/gtest/include/gtest/gtest.h"

using huhi::ResponseCallback;

TEST(HuhiAdBlockTPNetworkDelegateHelperTest, NoChangeURL) {
  const GURL url("https://bradhatesprimes.huhisoft.com/composite_numbers_ftw");
  auto request_info = std::make_shared<huhi::HuhiRequestInfo>(url);
  int rc =
      OnBeforeURLRequest_AdBlockTPPreWork(ResponseCallback(), request_info);
  EXPECT_TRUE(request_info->new_url_spec.empty());
  EXPECT_EQ(rc, net::OK);
}

TEST(HuhiAdBlockTPNetworkDelegateHelperTest, EmptyRequestURL) {
  auto request_info = std::make_shared<huhi::HuhiRequestInfo>(GURL());
  int rc =
      OnBeforeURLRequest_AdBlockTPPreWork(ResponseCallback(), request_info);
  EXPECT_TRUE(request_info->new_url_spec.empty());
  EXPECT_EQ(rc, net::OK);
}
