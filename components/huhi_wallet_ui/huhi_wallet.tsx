// Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Huhi Software
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

import * as React from 'react'
import { render } from 'react-dom'
import { initLocale } from 'huhi-ui'

import 'emptykit.css'

// Fonts
import '../../ui/webui/resources/fonts/poppins.css'
import '../../ui/webui/resources/fonts/muli.css'

// Components
import App from './components/app'
import Theme from 'huhi-ui/theme/huhi-default'
import DarkTheme from 'huhi-ui/theme/huhi-dark'
import HuhiCoreThemeProvider from '../common/HuhiCoreThemeProvider'

function initialize () {
  chrome.huhiWallet.shouldPromptForSetup((prompt: boolean) => {
    if (!prompt) {
      chrome.huhiWallet.loadUI(() => {
        window.location.href = 'chrome://wallet'
      })
      return
    }

    renderWebUIView()
  })
}

function renderWebUIView () {
  new Promise(resolve => chrome.huhiTheme.getHuhiThemeType(resolve))
  .then((themeType: chrome.huhiTheme.ThemeType) => {
    window.i18nTemplate.process(window.document, window.loadTimeData)
    if (window.loadTimeData && window.loadTimeData.data_) {
      initLocale(window.loadTimeData.data_)
    }

    render(
      <HuhiCoreThemeProvider
        initialThemeType={themeType}
        dark={DarkTheme}
        light={Theme}
      >
        <App />
      </HuhiCoreThemeProvider>,
      document.getElementById('root')
    )
  })
  .catch(({ message }) => {
    console.error(`Could not mount huhi wallet: ${message}`)
  })
}

document.addEventListener('DOMContentLoaded', initialize)
