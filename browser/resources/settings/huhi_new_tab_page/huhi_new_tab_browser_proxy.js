/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

// clang-format off
// #import {addSingletonGetter, sendWithPromise} from 'chrome://resources/js/cr.m.js';
// clang-format on

cr.define('settings', function() {
  /** @interface */
  /* #export */ class HuhiNewTabBrowserProxy {
    /**
     * @return {!Promise<Boolean>}
     */
    getIsSuperReferralActive() {}

    /**
     * @return {!Promise<Boolean>}
     */
    getIsBinanceSupported() {}

    /**
     * @return {!Promise<Boolean>}
     */
    getIsHuhiTogetherSupported() {}

    /**
     * @return {!Promise<Boolean>}
     */
    getIsGeminiSupported() {}

    /**
     * @return {!Promise<Boolean>}
     */
    getIsBitcoinDotComSupported() {}
  }

  /**
   * @implements {settings.HuhiNewTabBrowserProxy}
   */
  /* #export */ class HuhiNewTabBrowserProxyImpl {
    /** @override */
    getIsSuperReferralActive() {
      return cr.sendWithPromise('getIsSuperReferralActive');
    }

    /** @override */
    getIsBinanceSupported() {
      return cr.sendWithPromise('getIsBinanceSupported')
    }

    /** @override */
    getIsHuhiTogetherSupported() {
      return cr.sendWithPromise('getIsHuhiTogetherSupported')
    }

    /** @override */
    getIsGeminiSupported() {
      return cr.sendWithPromise('getIsGeminiSupported')
    }

    /** @override */
    getIsBitcoinDotComSupported() {
      return cr.sendWithPromise('getIsBitcoinDotComSupported')
    }
  }

  cr.addSingletonGetter(HuhiNewTabBrowserProxyImpl);

  // #cr_define_end
  return {
    HuhiNewTabBrowserProxy,
    HuhiNewTabBrowserProxyImpl
  };
});
