// Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Huhi Software
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

import * as React from 'react'
import { render } from 'react-dom'
import { Provider } from 'react-redux'
import Theme from 'huhi-ui/theme/huhi-default'
import DarkTheme from 'huhi-ui/theme/huhi-dark'
import HuhiCoreThemeProvider from '../common/HuhiCoreThemeProvider'
import { wireApiEventsToStore } from './apiEventsToStore'

// Components
import App from './containers/app'

// Utils
import store from './store'

function initialize () {
  console.timeStamp('loaded')
  // Get rendering going
  new Promise(resolve => chrome.huhiTheme.getHuhiThemeType(resolve))
  .then((themeType: chrome.huhiTheme.ThemeType) => {
    render(
      <Provider store={store}>
        <HuhiCoreThemeProvider
          initialThemeType={themeType}
          dark={DarkTheme}
          light={Theme}
        >
          <App />
        </HuhiCoreThemeProvider>
      </Provider>,
      document.getElementById('root'),
      () => console.timeStamp('first react render'))
  })
  .catch((error) => {
    console.error('Problem mounting huhi new tab', error)
  })
  window.i18nTemplate.process(window.document, window.loadTimeData)
}

console.timeStamp('JS start')

// Get store data going
wireApiEventsToStore()

// Perform DOM-dependent initialization when ready
document.addEventListener('DOMContentLoaded', initialize)
