/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/components/huhi_rewards/common/pref_names.h"

namespace huhi_rewards {
namespace prefs {

const char kHideButton[] = "huhi.hide_huhi_rewards_button";
const char kEnabled[] = "huhi.rewards.enabled";
const char kNotifications[] = "huhi.rewards.notifications";
const char kNotificationTimerInterval[]=
    "huhi.rewards.notification_timer_interval";
const char kBackupNotificationInterval[] =
    "huhi.rewards.backup_notification_interval";
const char kBackupSucceeded[] = "huhi.rewards.backup_succeeded";
const char kUserHasFunded[] = "huhi.rewards.user_has_funded";
const char kAddFundsNotification[] =
    "huhi.rewards.add_funds_notification";
const char kNotificationStartupDelay[] =
    "huhi.rewards.notification_startup_delay";
const char kExternalWallets[] = "huhi.rewards.external_wallets";
const char kServerPublisherListStamp[] =
    "huhi.rewards.publisher_prefix_list_stamp";
const char kUpholdAnonAddress[] =
    "huhi.rewards.uphold_anon_address";
const char kBadgeText[] = "huhi.rewards.badge_text";
const char kUseRewardsStagingServer[] = "huhi.rewards.use_staging_server";
const char kPromotionLastFetchStamp[] =
    "huhi.rewards.promotion_last_fetch_stamp";
const char kPromotionCorruptedMigrated[] =
    "huhi.rewards.promotion_corrupted_migrated2";
const char kAnonTransferChecked[] =  "huhi.rewards.anon_transfer_checked";
const char kVersion[] =  "huhi.rewards.version";
const char kMinVisitTime[] =  "huhi.rewards.ac.min_visit_time";
const char kMinVisits[] =  "huhi.rewards.ac.min_visits";
const char kAllowNonVerified[] =  "huhi.rewards.ac.allow_non_verified";
const char kAllowVideoContribution[] =
    "huhi.rewards.ac.allow_video_contributions";
const char kScoreA[] = "huhi.rewards.ac.score.a";
const char kScoreB[] = "huhi.rewards.ac.score.b";
const char kAutoContributeEnabled[] = "huhi.rewards.ac.enabled";
const char kAutoContributeAmount[] = "huhi.rewards.ac.amount";
const char kNextReconcileStamp[] = "huhi.rewards.ac.next_reconcile_stamp";
const char kCreationStamp[] = "huhi.rewards.creation_stamp";
const char kRecoverySeed[] = "huhi.rewards.wallet.seed";
const char kPaymentId[] = "huhi.rewards.wallet.payment_id";
const char kInlineTipRedditEnabled[] = "huhi.rewards.inline_tip.reddit";
const char kInlineTipTwitterEnabled[] = "huhi.rewards.inline_tip.twitter";
const char kInlineTipGithubEnabled[] = "huhi.rewards.inline_tip.github";
const char kParametersRate[] = "huhi.rewards.parameters.rate";
const char kParametersAutoContributeChoice[] =
    "huhi.rewards.parameters.ac.choice";
const char kParametersAutoContributeChoices[] =
    "huhi.rewards.parameters.ac.choices";
const char kParametersTipChoices[] =
    "huhi.rewards.parameters.tip.choices";
const char kParametersMonthlyTipChoices[] =
    "huhi.rewards.parameters.tip.monthly_choices";
const char kFetchOldBalance[] =
    "huhi.rewards.fetch_old_balance";
const char kEmptyBalanceChecked[] =
    "huhi.rewards.empty_balance_checked";
}  // namespace prefs
}  // namespace huhi_rewards
