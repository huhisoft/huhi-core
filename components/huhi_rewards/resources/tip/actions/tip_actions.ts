/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import { action } from 'typesafe-actions'

// Constant
import { types } from '../constants/tip_types'

export const onCloseDialog = () => action(types.ON_CLOSE_DIALOG)

export const onTweet = (name: string, tweetId: string) => action(types.ON_TWEET, {
  name,
  tweetId
})

export const onPublisherBanner = (data: RewardsTip.Publisher) => action(types.ON_PUBLISHER_BANNER, {
  data
})

export const getRewardsParameters = () => action(types.GET_REWARDS_PARAMETERS)

export const onRewardsParameters = (parameters: RewardsTip.RewardsParameters) =>
  action(types.ON_REWARDS_PARAMETERS, {
    parameters
  })

export const onTip = (publisherKey: string, amount: number, recurring: boolean) => action(types.ON_TIP, {
  publisherKey,
  amount,
  recurring
})

export const getRecurringTips = () => action(types.GET_RECURRING_TIPS)

export const onRecurringTips = (list: RewardsTip.RecurringTips[]) => action(types.ON_RECURRING_TIPS, {
  list
})

export const getReconcileStamp = () => action(types.GET_RECONCILE_STAMP)

export const onReconcileStamp = (stamp: number) => action(types.ON_RECONCILE_STAMP, {
  stamp
})

export const onRecurringTipRemoved = (success: boolean) => action(types.ON_RECURRING_TIP_REMOVED, {
  success
})

export const onRecurringTipSaved = (success: boolean) => action(types.ON_RECURRING_TIP_SAVED, {
  success
})

export const getBalance = () => action(types.GET_BALANCE)

export const onBalance = (status: number, balance: RewardsTip.Balance) => action(types.ON_BALANCE, {
  status,
  balance
})

export const getExternalWallet = () => action(types.GET_EXTERNAL_WALLET)

export const onExternalWallet = (wallet: RewardsTip.ExternalWallet) => action(types.ON_EXTERNAL_WALLET, {
  wallet
})

export const onlyAnonWallet = () => action(types.ONLY_ANON_WALLET)

export const onOnlyAnonWallet = (only: boolean) => action(types.ON_ONLY_ANON_WALLET, {
  only
})
