import 'emptykit.css'
import { configure, addDecorator, addParameters } from '@storybook/react'
import { initLocale } from 'huhi-ui/helpers'
import locale from './locale'
import { withThemesProvider } from 'storybook-addon-styled-component-theme'
import DarkTheme from 'huhi-ui/theme/huhi-dark'
import DefaultTheme from 'huhi-ui/theme/huhi-default'

// Fonts
import '../ui/webui/resources/fonts/muli.css'
import '../ui/webui/resources/fonts/poppins.css'

const themes = [DefaultTheme, DarkTheme]
addDecorator(withThemesProvider(themes))

addParameters({
  backgrounds: [
    { name: 'Neutral300', value: '#DEE2E6', default: true },
    { name: 'Grey700', value: '#5E6175' },
    { name: 'White', value: '#FFF' },
    { name: 'Grey900', value: '#1E2029' }
  ]
})

addParameters({
  options: {
    name: 'Huhi Browser UI',
    url: 'https://github.com/huhisoft/huhi-core',
    panelPosition: 'right'
  }
})

function loadStories() {
  initLocale(locale)
  window.loadTimeData = {
    getString (key) {
      return locale[key] || key
    },
    getBoolean (key) {
      return false
    }
  }
  chrome.extension = {
    inIncognitoContext: false
  }
  const req = require.context('../components/', true, /\/stories\/.*\.tsx$/)
  req.keys().forEach(filename => req(filename))
}

configure(loadStories, module)
