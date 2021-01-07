/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import {addSingletonGetter, sendWithPromise} from 'chrome://resources/js/cr.m.js';

/** @interface */
export class HuhiAppearanceBrowserProxy {
  /**
   * @return {!Promise<Array>}
   */
  getHuhiThemeList() {}
  /**
   * @return {!Promise<Number>}
   */
  getHuhiThemeType() {}
  /**
   * @param {Number} type
   */
  setHuhiThemeType(value) {}
}

/**
 * @implements {HuhiAppearanceBrowserProxy}
 */
export class HuhiAppearanceBrowserProxyImpl {
  /** @override */
  getHuhiThemeList() {
    return new Promise(resolve => chrome.huhiTheme.getHuhiThemeList(resolve))
  }
  getHuhiThemeType() {
    return sendWithPromise('getHuhiThemeType');
  }
  setHuhiThemeType(value) {
    chrome.send('setHuhiThemeType', [value]);
  }
}

addSingletonGetter(HuhiAppearanceBrowserProxyImpl);
