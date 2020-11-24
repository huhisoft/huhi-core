/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import * as React from 'react'
import { render } from 'react-dom'
import { Provider } from 'react-redux'
import { Store } from 'webext-redux'

import Theme from 'huhi-ui/theme/huhi-default'
import { ThemeProvider } from 'huhi-ui/theme'
import { initLocale } from 'huhi-ui/helpers'
require('emptykit.css')
require('../../../../../ui/webui/resources/fonts/muli.css')
require('../../../../../ui/webui/resources/fonts/poppins.css')

// Components
import App from './components/app'

// Utils
import { getUIMessages } from './background/api/locale_api'

const store: Store<RewardsExtension.State> = new Store({
  portName: 'REWARDSPANEL'
})

initLocale(getUIMessages())

store.ready().then(
  () => {
    render(
      <Provider store={store}>
        <ThemeProvider theme={Theme}>
          <App />
        </ThemeProvider>
      </Provider>,
      document.getElementById('root'))
  })
  .catch(() => {
    console.error('Problem mounting rewards panel')
  })
