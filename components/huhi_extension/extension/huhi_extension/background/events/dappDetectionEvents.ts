/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

// content script listener for dapp detection.
chrome.runtime.onMessage.addListener((msg, sender, sendResponse) => {
  switch (msg.type) {
    case 'dappAvailable': {
      if (sender.frameId === 0 && sender.tab) {
        chrome.huhiWallet.promptToEnableWallet(sender.tab.id)
      }
      break
    }
  }
})
