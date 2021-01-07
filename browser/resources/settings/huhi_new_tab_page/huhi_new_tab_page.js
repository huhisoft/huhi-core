// Copyright (c) 2020 The Huhi Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

(function() {
  'use strict';

  /**
   * 'settings-huhi-new-tab-page' is the settings page containing
   * huhi's new tab features.
   */
  Polymer({
    is: 'settings-huhi-new-tab-page',

    /** @private {?settings.HuhiNewTabBrowserProxy} */
    browserProxy_: null,

    behaviors: [
      WebUIListenerBehavior,
    ],

    properties: {
      isSuperReferralActive_: Boolean,
      isBinanceSupported_: Boolean,
      isHuhiTogetherSupported_: Boolean,
      isGeminiSupported_: Boolean,
      isBitcoinDotComSupported_: Boolean,
      showTopSites_: Boolean,
      isCryptoDotComSupported_: Boolean,
      newTabShowOptions_: Array,
      shouldNewTabShowDashboardSettings_: Boolean,
    },

    /** @override */
    created: function() {
      this.browserProxy_ = settings.HuhiNewTabBrowserProxyImpl.getInstance();
      this.isSuperReferralActive_ = false;
      this.isBinanceSupported_ = false;
      this.isHuhiTogetherSupported_ = false;
      this.isGeminiSupported_ = false;
      this.isBitcoinDotComSupported_ = false;
      this.showTopSites_ = false;
      this.isCryptoDotComSupported_ = false;
      this.showNewTabDashboardSettings_ = false;
    },

    /** @override */
    ready: function() {
      this.browserProxy_.getIsSuperReferralActive().then(isSuperReferralActive => {
        this.isSuperReferralActive_ = isSuperReferralActive;
      })
      this.browserProxy_.getIsBinanceSupported().then(isBinanceSupported => {
        this.isBinanceSupported_ = isBinanceSupported;
      })
      this.browserProxy_.getIsHuhiTogetherSupported().then(isHuhiTogetherSupported => {
        this.isHuhiTogetherSupported_ = isHuhiTogetherSupported;
      })
      this.browserProxy_.getIsGeminiSupported().then(isGeminiSupported => {
        this.isGeminiSupported_ = isGeminiSupported;
      })
      this.browserProxy_.getIsBitcoinDotComSupported().then(isBitcoinDotComSupported => {
        this.isBitcoinDotComSupported_ = isBitcoinDotComSupported;
      })
      this.browserProxy_.getShowTopSites().then(visible => {
        this.showTopSites_ = visible;
      })
      this.browserProxy_.getIsCryptoDotComSupported().then(isCryptoDotComSupported => {
        this.isCryptoDotComSupported_ = isCryptoDotComSupported;
      })
      this.browserProxy_.getNewTabShowsOptionsList().then(list => {
        this.newTabShowOptions_ = list;
      })
      this.browserProxy_.shouldShowNewTabDashboardSettings().then(showNewTabDashboardSettings => {
        this.showNewTabDashboardSettings_ = showNewTabDashboardSettings;
      })

      this.addWebUIListener('super-referral-active-state-changed', (isSuperReferralActive) => {
        this.isSuperReferralActive_ = isSuperReferralActive;
      })
      this.addWebUIListener('ntp-shortcut-visibility-changed', (visible) => {
        this.showTopSites_ = visible;
      })
      this.addWebUIListener('show-new-tab-dashboard-settings-changed', (show) => {
        this.showNewTabDashboardSettings_ = show
      })
    },

    onShowTopSitesChange_: function() {
      this.browserProxy_.toggleTopSitesVisible();
    }
  });
})();
