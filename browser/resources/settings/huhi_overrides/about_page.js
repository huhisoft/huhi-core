// Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Huhi Software
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

import {RegisterPolymerTemplateModifications} from 'chrome://huhi-resources/polymer_overriding.js'
import {getSectionElement} from './basic_page.js'

RegisterPolymerTemplateModifications({
  'settings-about-page': (templateContent) => {
    const section = getSectionElement(templateContent, 'about')
    if (!section.querySelector('a#release-notes')) {
      const version = section.querySelector('#updateStatusMessage ~ .secondary')
      if (!version) {
        console.error('[Huhi Settings Overrides] Could not find version div')
      }
      version.innerHTML = '<a id="release-notes" target="_blank" href="https://huhisoft.com/latest/">' + version.innerHTML + '</a>'
    }
  }
})
