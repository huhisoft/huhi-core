/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import * as React from 'react'
import { Provider as ReduxProvider } from 'react-redux'
import { storiesOf } from '@storybook/react'
import { withKnobs, select } from '@storybook/addon-knobs/react'
import Theme from 'huhi-ui/theme/huhi-default'
import DarkTheme from 'huhi-ui/theme/huhi-dark'
import HuhiCoreThemeProvider from '../../common/HuhiCoreThemeProvider'

// Components
import NewTabPage from '../containers/newTab'
import * as newTabActions from '../actions/new_tab_actions'
import * as gridSitesActions from '../actions/grid_sites_actions'
import * as rewardsActions from '../actions/rewards_actions'
import * as binanceActions from '../actions/binance_actions'
import * as geminiActions from '../actions/gemini_actions'
import * as bitcoinDotComActions from '../actions/bitcoin_dot_com_actions'
import store from '../store'
import { getNewTabData, getGridSitesData } from './default/data/storybookState'

export default function Provider ({ story }: any) {
  return (
    <ReduxProvider store={store}>
      <HuhiCoreThemeProvider
        dark={DarkTheme}
        light={Theme}
        initialThemeType={select(
          'Theme',
          { ['Light']: 'Light', ['Dark']: 'Dark' },
          'Light'
        )}
      >
      {story}
      </HuhiCoreThemeProvider>
    </ReduxProvider>
  )
}

storiesOf('New Tab/Containers', module)
  .addDecorator(withKnobs)
  .addDecorator(story => <Provider story={story()} />)
  .add('Default', () => {
    const doNothing = (value: boolean) => value
    const newTabData = getNewTabData(store.getState().newTabData)
    const gridSitesData = getGridSitesData(store.getState().gridSitesData)
    return (
      <NewTabPage
        newTabData={newTabData}
        gridSitesData={gridSitesData}
        actions={Object.assign({}, newTabActions, gridSitesActions, rewardsActions, binanceActions, geminiActions, bitcoinDotComActions)}
        saveShowBackgroundImage={doNothing}
        saveShowClock={doNothing}
        saveShowTopSites={doNothing}
        saveShowStats={doNothing}
        saveShowRewards={doNothing}
        saveShowBinance={doNothing}
        saveShowTogether={doNothing}
        saveShowAddCard={doNothing}
        saveShowGemini={doNothing}
        saveShowBitcoinDotCom={doNothing}
        saveBrandedWallpaperOptIn={doNothing}
      />
    )
  })
