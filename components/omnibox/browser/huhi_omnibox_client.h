/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_OMNIBOX_BROWSER_HUHI_OMNIBOX_CLIENT_H_
#define HUHI_COMPONENTS_OMNIBOX_BROWSER_HUHI_OMNIBOX_CLIENT_H_

#include "components/omnibox/browser/omnibox_client.h"

class HuhiOmniboxClient : public OmniboxClient {
 public:
  virtual bool IsAutocompleteEnabled() const;

 protected:
  ~HuhiOmniboxClient() override {}
};

#endif  // HUHI_COMPONENTS_OMNIBOX_BROWSER_HUHI_OMNIBOX_CLIENT_H_
