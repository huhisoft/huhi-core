/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import rewardsPanelActions from '../actions/rewardsPanelActions'

// Handle all rewards events and pass to actions
chrome.huhiRewards.walletCreated.addListener(() => {
  rewardsPanelActions.walletCreated()
})
chrome.huhiRewards.walletCreationFailed.addListener((result: RewardsExtension.Result) => {
  rewardsPanelActions.walletCreationFailed(result)
})

chrome.huhiRewards.onPublisherData.addListener((windowId: number, publisher: RewardsExtension.Publisher) => {
  rewardsPanelActions.onPublisherData(windowId, publisher)

  // Get publisher amounts
  if (publisher && publisher.publisher_key && publisher.status !== 0) {
    chrome.huhiRewards.getPublisherBanner(publisher.publisher_key, ((banner: RewardsExtension.PublisherBanner) => {
      rewardsPanelActions.onPublisherBanner(banner)
    }))
  }
})

chrome.huhiRewards.onPromotions.addListener((result: number, promotions: RewardsExtension.Promotion[]) => {
  rewardsPanelActions.onPromotions(result, promotions)
})

chrome.rewardsNotifications.onNotificationAdded.addListener((id: string, type: number, timestamp: number, args: string[]) => {
  rewardsPanelActions.onNotificationAdded(id, type, timestamp, args)
})

chrome.rewardsNotifications.onNotificationDeleted.addListener((id: string, type: number, timestamp: number) => {
  chrome.windows.getAll({ populate: true }, (windows) => {
    rewardsPanelActions.onNotificationDeleted(id, type, timestamp, windows)
  })
})

chrome.rewardsNotifications.onAllNotificationsDeleted.addListener(() => {
  rewardsPanelActions.onAllNotificationsDeleted()
})

chrome.huhiRewards.onEnabledMain.addListener((enabledMain: boolean) => {
  rewardsPanelActions.onEnabledMain(enabledMain)
})

chrome.huhiRewards.onPendingContributionSaved.addListener((result: number) => {
  if (result === 0) {
    chrome.huhiRewards.getPendingContributionsTotal(((amount: number) => {
      rewardsPanelActions.OnPendingContributionsTotal(amount)
    }))
  }
})

chrome.huhiRewards.onPublisherListNormalized.addListener((properties: RewardsExtension.PublisherNormalized[]) => {
  rewardsPanelActions.onPublisherListNormalized(properties)
})

chrome.huhiRewards.onExcludedSitesChanged.addListener((properties: RewardsExtension.ExcludedSitesChanged) => {
  rewardsPanelActions.onExcludedSitesChanged(properties)
})

chrome.huhiRewards.onRecurringTipSaved.addListener((success: boolean) => {
  if (success) {
    chrome.huhiRewards.getRecurringTips((tips: RewardsExtension.RecurringTips) => {
      rewardsPanelActions.onRecurringTips(tips)
    })
  }
})

chrome.huhiRewards.onRecurringTipRemoved.addListener((success: boolean) => {
  if (success) {
    chrome.huhiRewards.getRecurringTips((tips: RewardsExtension.RecurringTips) => {
      rewardsPanelActions.onRecurringTips(tips)
    })
  }
})

chrome.huhiRewards.onReconcileComplete.addListener((result: number, type: number) => {
  if (result === 0) {
    chrome.huhiRewards.fetchBalance((balance: RewardsExtension.Balance) => {
      rewardsPanelActions.onBalance(balance)
    })

    chrome.huhiRewards.getBalanceReport(new Date().getMonth() + 1, new Date().getFullYear(),
    (report: RewardsExtension.BalanceReport) => {
      rewardsPanelActions.onBalanceReport(report)
    })
  }
})

chrome.huhiRewards.onDisconnectWallet.addListener((properties: {result: number, walletType: string}) => {
  if (properties.result === 0) {
    chrome.huhiRewards.getExternalWallet(properties.walletType, (result: number, wallet: RewardsExtension.ExternalWallet) => {
      rewardsPanelActions.onExternalWallet(wallet)
    })

    chrome.huhiRewards.fetchBalance((balance: RewardsExtension.Balance) => {
      rewardsPanelActions.onBalance(balance)
    })
  }
})

chrome.huhiRewards.onUnblindedTokensReady.addListener(() => {
  chrome.huhiRewards.fetchBalance((balance: RewardsExtension.Balance) => {
    rewardsPanelActions.onBalance(balance)
  })
})

chrome.huhiRewards.onPromotionFinish.addListener((result: RewardsExtension.Result, promotion: RewardsExtension.Promotion) => {
  rewardsPanelActions.promotionFinished(result, promotion)

  chrome.huhiRewards.getBalanceReport(new Date().getMonth() + 1, new Date().getFullYear(),
  (report: RewardsExtension.BalanceReport) => {
    rewardsPanelActions.onBalanceReport(report)
  })
})

chrome.huhiRewards.onCompleteReset.addListener((properties: { success: boolean }) => {
  rewardsPanelActions.onCompleteReset(properties.success)
})

chrome.huhiRewards.initialized.addListener((result: RewardsExtension.Result) => {
  rewardsPanelActions.initialized()
})

// Fetch initial data required to refresh state, keeping in mind
// that the extension process be restarted at any time.
// TODO(petemill): Move to initializer function or single 'init' action.
chrome.huhiRewards.getRewardsMainEnabled((enabledMain: boolean) => {
  rewardsPanelActions.onEnabledMain(enabledMain)
  if (enabledMain) {
    chrome.huhiRewards.getAnonWalletStatus((result: RewardsExtension.Result) => {
      rewardsPanelActions.onAnonWalletStatus(result)
    })
    chrome.huhiRewards.fetchPromotions()
    chrome.huhiRewards.fetchBalance((balance: RewardsExtension.Balance) => {
      rewardsPanelActions.onBalance(balance)
    })
    chrome.huhiRewards.getAllNotifications((list: RewardsExtension.Notification[]) => {
      rewardsPanelActions.onAllNotifications(list)
    })
    chrome.huhiRewards.getRewardsParameters((parameters: RewardsExtension.RewardsParameters) => {
      rewardsPanelActions.onRewardsParameters(parameters)
    })
  }
})
