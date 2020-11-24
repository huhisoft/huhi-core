/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

function testBasics() {
  chrome.test.runTests([
    function huhiShieldsHasWalletAccessButNotSeed() {
      if (chrome.huhiWallet && !chrome.huhiWallet.getWalletSeed &&
          !chrome.huhiWallet.getBitGoSeed &&
          !chrome.huhiWallet.getProjectID &&
          !chrome.huhiWallet.getHuhiKey) {
        chrome.test.succeed();
      } else {
        chrome.test.fail();
      }
    },
  ]);
}

function testNoDappCheck() {
  chrome.test.runTests([
    function testNotENabled() {
      chrome.huhiWallet.shouldCheckForDapps((dappDetection) => {
        if (dappDetection) {
          chrome.test.fail();
        } else {
          chrome.test.succeed();
        }
      })
    },
  ]);
}

function testDappCheck() {
  chrome.test.runTests([
    function testNotENabled() {
      chrome.huhiWallet.shouldCheckForDapps((dappDetection) => {
        if (dappDetection) {
          chrome.test.succeed();
        } else {
          chrome.test.fail();
        }
      })
    },
  ]);
}
