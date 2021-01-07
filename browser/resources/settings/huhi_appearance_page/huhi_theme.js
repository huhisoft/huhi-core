// Copyright (c) 2020 The Huhi Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

import {Polymer, html} from 'chrome://resources/polymer/v3_0/polymer/polymer_bundled.min.js';
import {WebUIListenerBehavior} from 'chrome://resources/js/web_ui_listener_behavior.m.js';
import {routes} from '../route.js';
import {Router} from '../router.m.js';
import 'chrome://resources/cr_elements/md_select_css.m.js';
import '../settings_shared_css.m.js';
import '../settings_vars_css.m.js';
import {loadTimeData} from "../i18n_setup.js"
import {HuhiAppearanceBrowserProxy,  HuhiAppearanceBrowserProxyImpl} from './huhi_appearance_browser_proxy.js';

/**
 * 'settings-huhi-appearance-theme' is the settings page area containing
 * huhi's appearance related settings that located at the top of appearance
 * area.
 */
Polymer({
  is: 'settings-huhi-appearance-theme',

  _template: html`{__html_template__}`,

  behaviors: [
    WebUIListenerBehavior,
  ],

  properties: {
    huhiThemeList_: Array,
    huhiThemeType_: Number,
  },

  /** @private {?settings.HuhiAppearanceBrowserProxy} */
  browserProxy_: null,

  observers: [
    'updateSelected_(huhiThemeType_, huhiThemeList_)',
  ],

  /** @override */
  created: function() {
    this.browserProxy_ = HuhiAppearanceBrowserProxyImpl.getInstance();
  },

  /** @override */
  ready: function() {
    this.addWebUIListener('huhi-theme-type-changed', (type) => {
      this.huhiThemeType_ = type;
    })
    this.browserProxy_.getHuhiThemeList().then(list => {
      this.huhiThemeList_ = JSON.parse(list);
    })
    this.browserProxy_.getHuhiThemeType().then(type => {
      this.huhiThemeType_ = type;
    })
  },

  onHuhiThemeTypeChange_: function() {
    this.browserProxy_.setHuhiThemeType(Number(this.$.huhiThemeType.value));
  },

  huhiThemeTypeEqual_: function(theme1, theme2) {
    return theme1 === theme2;
  },

  onThemeTap_: function() {
    Router.getInstance().navigateTo(routes.THEMES);
  },

  // Wait for the dom-repeat to populate the <select> before setting
  // <select>#value so the correct option gets selected.
  updateSelected_: function() {
    this.async(() => {
      this.$.huhiThemeType.value = this.huhiThemeType_;
    });
  },

  useThemesSubPage_: function() {
    return loadTimeData.getString('superReferralThemeName') !== "";
  }
});
