/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#import <Foundation/Foundation.h>

typedef NSString *BATWalletType NS_SWIFT_NAME(WalletType) NS_STRING_ENUM;

static BATWalletType const BATWalletTypeUphold = @"uphold";
static BATWalletType const BATWalletTypeAnonymous = @"anonymous";
static BATWalletType const BATWalletTypeUnblindedTokens = @"blinded";

