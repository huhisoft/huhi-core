// Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Huhi Software
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

import {RegisterPolymerTemplateModifications} from 'chrome://huhi-resources/polymer_overriding.js'
import {I18nBehavior} from 'chrome://resources/js/i18n_behavior.m.js'
import {Router} from '../router.m.js'
import {loadTimeData} from '../i18n_setup.js'

import '../huhi_appearance_page/super_referral.js'
import '../huhi_appearance_page/huhi_theme.js'
import '../huhi_appearance_page/toolbar.js'

const superReferralStringId = 'superReferralThemeName'

RegisterPolymerTemplateModifications({
  'settings-appearance-page': (templateContent) => {
    const theme = templateContent.getElementById('themeRow')
    if (!theme) {
      console.error(`[Huhi Settings Overrides] Couldn't find #themeRow`)
    } else {
      theme.insertAdjacentHTML('beforebegin', `
        <settings-huhi-appearance-theme prefs="{{prefs}}"></settings-huhi-appearance-theme>
      `)
    }
    const r = Router.getInstance().routes_
    // Super-referral
    // W/o super referral, we don't need to themes link option with themes sub
    // page.
    const hasSuperReferral = (
      loadTimeData.valueExists(superReferralStringId) &&
      loadTimeData.getString(superReferralStringId) !== ''
    )
    if (hasSuperReferral) {
      // Routes
      if (!r.APPEARANCE) {
        console.error('[Huhi Settings Overrides] Routes: could not find APPEARANCE page')
        return
      } else {
        r.THEMES = r.APPEARANCE.createChild('/themes');
        // Hide chromium's theme section. It's replaced with our themes page.
        if (theme) {
          theme.remove()
        }
      }
    }
    // Toolbar prefs
    const bookmarkBarToggle = templateContent.querySelector('[pref="{{prefs.bookmark_bar.show_on_all_tabs}}"]')
    if (!bookmarkBarToggle) {
      console.error(`[Huhi Settings Overrides] Couldn't find bookmark bar toggle`)
    } else {
      bookmarkBarToggle.insertAdjacentHTML('afterend', `
        <settings-huhi-appearance-toolbar prefs="{{prefs}}"></settings-huhi-appearance-toolbar>
      `)
    }
    // Super referral themes prefs
    const pages = templateContent.getElementById('pages')
    if (!pages) {
      console.error(`[Huhi Settings Overrides] Couldn't find appearance_page #pages`)
    } else {
      pages.insertAdjacentHTML('beforeend', `
        <template is="dom-if" route-path="/themes">
          <settings-subpage
          associated-control="[[$$('#themes-subpage-trigger')]]"
          page-title="${I18nBehavior.i18n('themes')}">
            <settings-huhi-appearance-super-referral prefs="{{prefs}}">
            </settings-huhi-appearance-super-referral>
          </settings-subpage>
        </template>
      `)
    }
  },
})
