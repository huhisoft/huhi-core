/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "components/signin/internal/identity_manager/profile_oauth2_token_service_builder.h"

#include "huhi/components/signin/internal/identity_manager/huhi_mutable_profile_oauth2_token_service_delegate.h"

#define MutableProfileOAuth2TokenServiceDelegate \
  HuhiMutableProfileOAuth2TokenServiceDelegate
#include "../../../../../../components/signin/internal/identity_manager/profile_oauth2_token_service_builder.cc"
#undef MutableProfileOAuth2TokenServiceDelegate
