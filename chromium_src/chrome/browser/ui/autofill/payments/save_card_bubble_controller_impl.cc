/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#define HUHI_SHOULD_SHOW_SIGNIN_PROMO_SHORT_CIRCUIT_TO_FALSE \
return false;

#include "../../../../../../../chrome/browser/ui/autofill/payments/save_card_bubble_controller_impl.cc"  // NOLINT
#undef HUHI_SHOULD_SHOW_SIGNIN_PROMO_SHORT_CIRCUIT_TO_FALSE
