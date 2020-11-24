// Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Huhi Software
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

import {addSingletonGetter, sendWithPromise} from 'chrome://resources/js/cr.m.js';

export class HuhiSyncBrowserProxy {
  getSyncCode() {
    return sendWithPromise('SyncSetupGetSyncCode');
  }
  getQRCode(syncCode) {
    return sendWithPromise('SyncGetQRCode', syncCode);
  }
  getDeviceList() {
    return sendWithPromise('SyncGetDeviceList');
  }
  setSyncCode(syncCode) {
    return sendWithPromise('SyncSetupSetSyncCode', syncCode);
  }
  resetSyncChain() {
    return sendWithPromise('SyncSetupReset');
  }
}

addSingletonGetter(HuhiSyncBrowserProxy);
