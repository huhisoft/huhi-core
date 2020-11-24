// Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Huhi Software
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

import {RegisterPolymerComponentProperties, RegisterPolymerTemplateModifications} from 'chrome://huhi-resources/polymer_overriding.js'

RegisterPolymerTemplateModifications({
  'settings-sync-account-control': (templateContent) => {
    const banner = templateContent.querySelector('#banner')
    const promo_header = templateContent.querySelector('#promo-header')
    if (!banner) {
      console.error('[Huhi Settings Overrides] Could not find sync banner')
      return
    }
    if (!promo_header) {
      console.error('[Huhi Settings Overrides] Could not find promo header')
      return
    }
    banner.hidden = true
    promo_header.hidden = true
  }
})

RegisterPolymerComponentProperties({
  'settings-sync-account-control': {
    shouldShowAvatarRow_: {
      type: Boolean,
      value: false
    }
  }
})