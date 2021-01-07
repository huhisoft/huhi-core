/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import * as React from 'react'
import { render } from 'react-dom'
import { bindActionCreators } from 'redux'
import { Provider } from 'react-redux'

import welcomeDarkTheme from './theme/welcome-dark'
import welcomeLightTheme from './theme/welcome-light'
import HuhiCoreThemeProvider from '../common/HuhiCoreThemeProvider'

// Components
import App from './containers/app'

// Utils
import store from './store'
import * as welcomeActions from './actions/welcome_actions'

window.cr.define('huhi_welcome', function () {
  'use strict'

  function loadWelcomeData () {
    const actions = bindActionCreators(welcomeActions, store.dispatch.bind(store))
    actions.getSearchEngineProviders()
    actions.getBrowserProfiles()
  }

  function initialize () {
    loadWelcomeData()
    new Promise(resolve => chrome.huhiTheme.getHuhiThemeType(resolve))
    .then((themeType: chrome.huhiTheme.ThemeType) => {
      render(
        <Provider store={store}>
          <HuhiCoreThemeProvider
            initialThemeType={themeType}
            dark={welcomeDarkTheme}
            light={welcomeLightTheme}
          >
            <App />
          </HuhiCoreThemeProvider>
        </Provider>,
        document.getElementById('root'))
    })
    .catch((error) => {
      console.error('Problem mounting huhi welcome', error)
    })
    window.i18nTemplate.process(window.document, window.loadTimeData)
  }

  return {
    initialize
  }
})

document.addEventListener('DOMContentLoaded', window.huhi_welcome.initialize)
