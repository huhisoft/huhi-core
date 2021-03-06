/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#import <Foundation/Foundation.h>
#import "BATHuhiLedgerObserver.h"
#import "BATHuhiLedger.h"

@interface BATHuhiLedgerObserver ()
@property (nonatomic, weak) BATHuhiLedger *ledger;
@end

@implementation BATHuhiLedgerObserver

- (instancetype)initWithLedger:(BATHuhiLedger *)ledger {
  if ((self = [super init])) {
    self.ledger = ledger;
  }
  return self;
}

@end
