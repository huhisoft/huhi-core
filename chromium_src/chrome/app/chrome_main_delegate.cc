/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

// This chormium_src override allows us to skip a lot of patching to
// chrome/BUILD.gn
#include "huhi/app/huhi_command_line_helper.cc"  // NOLINT
#include "huhi/app/huhi_main_delegate.cc"  // NOLINT
#include "../../../../chrome/app/chrome_main_delegate.cc"  // NOLINT
