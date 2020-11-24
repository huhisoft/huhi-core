// Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Huhi Software
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

import {RegisterPolymerTemplateModifications} from 'chrome://huhi-resources/polymer_overriding.js'

RegisterPolymerTemplateModifications({
  'settings-printing-page': (templateContent) => {
    const link = templateContent.getElementById('cloudPrinters')
    if (!link) {
      console.error('[Huhi Settings Overrides] Could not find cloudPrinters id on printing page.')
    } else {
      link.setAttribute('hidden', 'true')
    }
  }
})
