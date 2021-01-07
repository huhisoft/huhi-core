/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_UTILITY_HUHI_CONTENT_UTILITY_CLIENT_H_
#define HUHI_UTILITY_HUHI_CONTENT_UTILITY_CLIENT_H_

#include <string>

#include "chrome/utility/chrome_content_utility_client.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"

class HuhiContentUtilityClient : public ChromeContentUtilityClient {
 public:
  HuhiContentUtilityClient();
  ~HuhiContentUtilityClient() override;

 private:
  DISALLOW_COPY_AND_ASSIGN(HuhiContentUtilityClient);
};

#endif  // HUHI_UTILITY_HUHI_CONTENT_UTILITY_CLIENT_H_
