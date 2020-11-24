/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/components/huhi_wayback_machine/huhi_wayback_machine_infobar_delegate.h"

using InfoBarIdentifier = infobars::InfoBarDelegate::InfoBarIdentifier;

HuhiWaybackMachineInfoBarDelegate::
HuhiWaybackMachineInfoBarDelegate() = default;

HuhiWaybackMachineInfoBarDelegate::
~HuhiWaybackMachineInfoBarDelegate() = default;

InfoBarIdentifier HuhiWaybackMachineInfoBarDelegate::GetIdentifier() const {
  return WAYBACK_MACHINE_INFOBAR_DELEGATE;
}

bool HuhiWaybackMachineInfoBarDelegate::EqualsDelegate(
    infobars::InfoBarDelegate* delegate) const {
  return delegate->GetIdentifier() == GetIdentifier();
}
