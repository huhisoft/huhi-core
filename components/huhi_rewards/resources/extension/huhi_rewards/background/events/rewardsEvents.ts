/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import rewardsPanelActions from '../actions/rewardsPanelActions'

chrome.huhiRewards.onPublisherData.addListener((windowId: number, publisher: RewardsExtension.Publisher) => {
  rewardsPanelActions.onPublisherData(windowId, publisher)

  // Get publisher amounts
  if (publisher && publisher.publisherKey && publisher.status !== 0) {
    chrome.huhiRewards.getPublisherBanner(publisher.publisherKey, ((banner: RewardsExtension.PublisherBanner) => {
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
