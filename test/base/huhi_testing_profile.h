/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_TEST_BASE_HUHI_TESTING_PROFILE_H_
#define HUHI_TEST_BASE_HUHI_TESTING_PROFILE_H_

#include "chrome/test/base/testing_profile.h"

class HuhiTestingProfile : public TestingProfile {
 public:
  HuhiTestingProfile();
  HuhiTestingProfile(const base::FilePath& path, Delegate* delegate);
  ~HuhiTestingProfile() override = default;
};

#endif  // HUHI_TEST_BASE_HUHI_TESTING_PROFILE_H_
