/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#define ShouldManagePasswordsinGooglePasswordManager \
  ShouldManagePasswordsinGooglePasswordManager_ChromiumImpl
#include "../../../../../../chrome/browser/ui/passwords/manage_passwords_view_utils.cc"
#undef ShouldManagePasswordsinGooglePasswordManager
bool ShouldManagePasswordsinGooglePasswordManager(Profile* profile) {
  return false;
}
