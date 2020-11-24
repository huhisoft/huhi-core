/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/net/huhi_system_request_handler.h"

#include <string>

#include "services/network/public/cpp/resource_request.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace huhi {

TEST(HuhiSystemRequestHandlerTest, AddHuhiServiceKeyHeaderForHuhi) {
  GURL url("https://demo.huhisoft.com");
  network::ResourceRequest request;

  request.url = url;
  huhi::AddHuhiServicesKeyHeader(&request);
  std::string key;
  EXPECT_TRUE(request.headers.GetHeader(kHuhiServicesKeyHeader, &key));
  EXPECT_EQ(key, HuhiServicesKeyForTesting());
}

TEST(HuhiSystemRequestHandlerTest, AddHuhiServiceKeyHeaderForHuhiSoftware) {
  GURL url("https://demo.huhisoft.com");
  network::ResourceRequest request;

  request.url = url;
  huhi::AddHuhiServicesKeyHeader(&request);
  std::string key;
  EXPECT_TRUE(request.headers.GetHeader(kHuhiServicesKeyHeader, &key));
  EXPECT_EQ(key, HuhiServicesKeyForTesting());
}

TEST(HuhiSystemRequestHandlerTest, DontAddHuhiServiceKeyHeader) {
  GURL url("https://demo.example.com");
  network::ResourceRequest request;

  request.url = url;
  huhi::AddHuhiServicesKeyHeader(&request);
  std::string key;
  EXPECT_FALSE(request.headers.GetHeader(kHuhiServicesKeyHeader, &key));
}

}  // namespace huhi
