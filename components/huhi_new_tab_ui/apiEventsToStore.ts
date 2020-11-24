// Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Huhi Software
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

import getActions from './api/getActions'
import * as preferencesAPI from './api/preferences'
import * as statsAPI from './api/stats'
import * as privateTabDataAPI from './api/privateTabData'
import { getInitialData, getRewardsInitialData, getRewardsPreInitialData, getBinanceBlackList } from './api/initialData'

async function updatePreferences (prefData: preferencesAPI.Preferences) {
  getActions().preferencesUpdated(prefData)
}

async function updateStats (statsData: statsAPI.Stats) {
  getActions().statsUpdated(statsData)
}

async function updatePrivateTabData (data: privateTabDataAPI.PrivateTabData) {
  getActions().privateTabDataUpdated(data)
}

function onRewardsToggled (prefData: preferencesAPI.Preferences): void {
  if (prefData.showRewards) {
    rewardsInitData()
  }
}

// Not marked as async so we don't return a promise
// and confuse callers
export function wireApiEventsToStore () {
  // Get initial data and dispatch to store
  getInitialData()
  .then((initialData) => {
    if (initialData.preferences.showRewards) {
      rewardsInitData()
    }
    binanceInitData()
    getActions().setInitialData(initialData)
    getActions().setFirstRenderGridSitesData(initialData)
    // Listen for API changes and dispatch to store
    statsAPI.addChangeListener(updateStats)
    preferencesAPI.addChangeListener(updatePreferences)
    preferencesAPI.addChangeListener(onRewardsToggled)
    privateTabDataAPI.addChangeListener(updatePrivateTabData)
  })
  .catch(e => {
    console.error('New Tab Page fatal error:', e)
  })
}

export function rewardsInitData () {
  getRewardsPreInitialData()
  .then((preInitialRewardsData) => {
    getActions().setPreInitialRewardsData(preInitialRewardsData)

    chrome.huhiRewards.getWalletExists((exists: boolean) => {
      getActions().onWalletExists(exists)
      if (exists) {
        if (!preInitialRewardsData.enabledMain) {
          return
        }

        fetchCreatedWalletData()
        setRewardsFetchInterval()
      }
    })
  })
  .catch(e => {
    console.error('Error fetching pre-initial rewards data: ', e)
  })
}

function binanceInitData () {
  getBinanceBlackList()
  .then(({ isSupportedRegion, onlyAnonWallet }) => {
    if (onlyAnonWallet || !isSupportedRegion) {
      getActions().removeStackWidget('binance')
    }
    getActions().setOnlyAnonWallet(onlyAnonWallet)
    getActions().setBinanceSupported(isSupportedRegion && !onlyAnonWallet)
  })
  .catch(e => {
    console.error('Error fetching binance init data')
  })
}

function setRewardsFetchInterval () {
  window.setInterval(() => {
    chrome.huhiRewards.getRewardsMainEnabled((enabledMain: boolean) => {
      if (!enabledMain) {
        return
      }
      chrome.huhiRewards.getWalletExists((exists: boolean) => {
        if (exists) {
          fetchCreatedWalletData()
        }
      })
    })
  }, 30000)
}

function fetchCreatedWalletData () {
  chrome.huhiRewards.isInitialized((initialized: boolean) => {
    if (!initialized) {
      return
    }

    getRewardsInitialData()
    .then((initialRewardsData) => {
      getActions().setInitialRewardsData(initialRewardsData)
    })
    .catch(e => {
      console.error('Error fetching initial rewards data: ', e)
    })
  })
}

chrome.huhiRewards.walletCreated.addListener(() => {
  getActions().onWalletInitialized(12)
})

chrome.huhiRewards.walletCreationFailed.addListener((result: any | NewTab.RewardsResult) => {
  getActions().onWalletInitialized(result)
})

chrome.huhiRewards.initialized.addListener((result: any | NewTab.RewardsResult) => {
  rewardsInitData()
})

chrome.huhiRewards.onEnabledMain.addListener((enabledMain: boolean) => {
  if (enabledMain) {
    chrome.huhiRewards.getAdsEnabled((enabledAds: boolean) => {
      getActions().onEnabledMain(enabledMain, enabledAds)
    })
  } else {
    getActions().onEnabledMain(false, false)
  }
})

chrome.huhiRewards.onAdsEnabled.addListener((enabled: boolean) => {
  getActions().onAdsEnabled(enabled)
})

chrome.huhiRewards.onPromotions.addListener((result: number, promotions: NewTab.Promotion[]) => {
  getActions().onPromotions(result, promotions)
})

chrome.huhiRewards.onPromotionFinish.addListener((result: number, promotion: NewTab.Promotion) => {
  getActions().onPromotionFinish(result, promotion)
})

chrome.huhiRewards.onCompleteReset.addListener((properties: { success: boolean }) => {
  getActions().onCompleteReset(properties.success)
})
