/* Copyright 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMMON_HUHI_CONTENT_CLIENT_H_
#define HUHI_COMMON_HUHI_CONTENT_CLIENT_H_

#include "chrome/common/chrome_content_client.h"

class HuhiContentClient : public ChromeContentClient {
 public:
  HuhiContentClient();
  ~HuhiContentClient() override;

 private:
  // ChromeContentClinet overrides:
  base::RefCountedMemory* GetDataResourceBytes(int resource_id) override;
  void AddAdditionalSchemes(Schemes* schemes) override;
};

#endif  // HUHI_COMMON_HUHI_CONTENT_CLIENT_H_
