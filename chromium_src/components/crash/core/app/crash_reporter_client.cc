/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#define HUHI_CRASH_REPORTER_CLIENT_GET_UPLOAD_URL \
  return "https://cr.hnq.vn";

#include "../../../../../../components/crash/core/app/crash_reporter_client.cc"
#undef HUHI_CRASH_REPORTER_CLIENT_GET_UPLOAD_URL
