/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/huhi_rewards/android/huhi_rewards_native_worker.h"

#include <iomanip>
#include <string>
#include <vector>
#include <utility>

#include "base/time/time.h"
#include "base/android/jni_android.h"
#include "base/android/jni_string.h"
#include "base/android/jni_array.h"
#include "base/json/json_writer.h"
#include "huhi/components/huhi_ads/browser/ads_service.h"
#include "huhi/components/huhi_ads/browser/ads_service_factory.h"
#include "huhi/browser/huhi_rewards/rewards_service_factory.h"
#include "huhi/components/huhi_rewards/browser/rewards_service.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_manager.h"
#include "content/public/browser/url_data_source.h"
#include "huhi/build/android/jni_headers/HuhiRewardsNativeWorker_jni.h"

#define DEFAULT_ADS_PER_HOUR 2
#define DEFAULT_AUTO_CONTRIBUTION_AMOUNT 10

namespace chrome {
namespace android {

HuhiRewardsNativeWorker::HuhiRewardsNativeWorker(JNIEnv* env,
    const base::android::JavaRef<jobject>& obj):
    weak_java_huhi_rewards_native_worker_(env, obj),
    huhi_rewards_service_(nullptr),
    weak_factory_(this) {
  Java_HuhiRewardsNativeWorker_setNativePtr(env, obj,
    reinterpret_cast<intptr_t>(this));

  huhi_rewards_service_ = huhi_rewards::RewardsServiceFactory::GetForProfile(
      ProfileManager::GetActiveUserProfile()->GetOriginalProfile());
  if (huhi_rewards_service_) {
    huhi_rewards_service_->AddObserver(this);
    huhi_rewards_service_->AddPrivateObserver(this);
    huhi_rewards::RewardsNotificationService* notification_service =
      huhi_rewards_service_->GetNotificationService();
    if (notification_service) {
      notification_service->AddObserver(this);
    }
  }
}

HuhiRewardsNativeWorker::~HuhiRewardsNativeWorker() {
}

void HuhiRewardsNativeWorker::Destroy(JNIEnv* env, const
        base::android::JavaParamRef<jobject>& jcaller) {
  if (huhi_rewards_service_) {
    huhi_rewards_service_->RemoveObserver(this);
    huhi_rewards_service_->RemovePrivateObserver(this);
    huhi_rewards::RewardsNotificationService* notification_service =
      huhi_rewards_service_->GetNotificationService();
    if (notification_service) {
      notification_service->RemoveObserver(this);
    }
  }
  delete this;
}

void HuhiRewardsNativeWorker::GetRewardsParameters(JNIEnv* env, const
        base::android::JavaParamRef<jobject>& jcaller) {
  if (huhi_rewards_service_) {
    huhi_rewards_service_->GetRewardsParameters(
        base::BindOnce(&HuhiRewardsNativeWorker::OnGetRewardsParameters,
                       base::Unretained(this), huhi_rewards_service_));
  }
}

void HuhiRewardsNativeWorker::GetPublisherInfo(JNIEnv* env, const
        base::android::JavaParamRef<jobject>& jcaller, int tabId,
        const base::android::JavaParamRef<jstring>& host) {
  if (huhi_rewards_service_) {
    huhi_rewards_service_->GetPublisherActivityFromUrl(tabId,
      base::android::ConvertJavaStringToUTF8(env, host), "", "");
  }
}

void HuhiRewardsNativeWorker::OnPanelPublisherInfo(
      huhi_rewards::RewardsService* rewards_service,
      const ledger::type::Result result,
      const ledger::type::PublisherInfo* info,
      uint64_t tabId) {
  if (!info) {
    return;
  }
  ledger::type::PublisherInfoPtr pi = info->Clone();
  map_publishers_info_[tabId] = std::move(pi);
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_HuhiRewardsNativeWorker_OnPublisherInfo(env,
        weak_java_huhi_rewards_native_worker_.get(env), tabId);
}

base::android::ScopedJavaLocalRef<jstring>
  HuhiRewardsNativeWorker::GetPublisherURL(JNIEnv* env,
        const base::android::JavaParamRef<jobject>& obj, uint64_t tabId) {
  base::android::ScopedJavaLocalRef<jstring> res =
    base::android::ConvertUTF8ToJavaString(env, "");

  PublishersInfoMap::const_iterator iter(map_publishers_info_.find(tabId));
  if (iter != map_publishers_info_.end()) {
    res = base::android::ConvertUTF8ToJavaString(env, iter->second->url);
  }

  return res;
}

base::android::ScopedJavaLocalRef<jstring>
  HuhiRewardsNativeWorker::GetPublisherFavIconURL(JNIEnv* env,
        const base::android::JavaParamRef<jobject>& obj, uint64_t tabId) {
  base::android::ScopedJavaLocalRef<jstring> res =
    base::android::ConvertUTF8ToJavaString(env, "");

  PublishersInfoMap::const_iterator iter(map_publishers_info_.find(tabId));
  if (iter != map_publishers_info_.end()) {
    res = base::android::ConvertUTF8ToJavaString(env,
      iter->second->favicon_url);
  }

  return res;
}

base::android::ScopedJavaLocalRef<jstring>
  HuhiRewardsNativeWorker::GetPublisherName(JNIEnv* env,
        const base::android::JavaParamRef<jobject>& obj, uint64_t tabId) {
  base::android::ScopedJavaLocalRef<jstring> res =
    base::android::ConvertUTF8ToJavaString(env, "");

  PublishersInfoMap::const_iterator iter(map_publishers_info_.find(tabId));
  if (iter != map_publishers_info_.end()) {
    res = base::android::ConvertUTF8ToJavaString(env, iter->second->name);
  }

  return res;
}

base::android::ScopedJavaLocalRef<jstring>
  HuhiRewardsNativeWorker::GetPublisherId(JNIEnv* env,
        const base::android::JavaParamRef<jobject>& obj, uint64_t tabId) {
  base::android::ScopedJavaLocalRef<jstring> res =
    base::android::ConvertUTF8ToJavaString(env, "");

  PublishersInfoMap::const_iterator iter(map_publishers_info_.find(tabId));
  if (iter != map_publishers_info_.end()) {
    res = base::android::ConvertUTF8ToJavaString(env, iter->second->id);
  }

  return res;
}

int HuhiRewardsNativeWorker::GetPublisherPercent(JNIEnv* env,
        const base::android::JavaParamRef<jobject>& obj, uint64_t tabId) {
  int res = 0;

  PublishersInfoMap::const_iterator iter(map_publishers_info_.find(tabId));
  if (iter != map_publishers_info_.end()) {
    res = iter->second->percent;
  }

  return res;
}

bool HuhiRewardsNativeWorker::GetPublisherExcluded(JNIEnv* env,
        const base::android::JavaParamRef<jobject>& obj, uint64_t tabId) {
  bool res = false;

  PublishersInfoMap::const_iterator iter(map_publishers_info_.find(tabId));
  if (iter != map_publishers_info_.end()) {
    res = iter->second->excluded == ledger::type::PublisherExclude::EXCLUDED;
  }

  return res;
}

int HuhiRewardsNativeWorker::GetPublisherStatus(JNIEnv* env,
        const base::android::JavaParamRef<jobject>& obj, uint64_t tabId) {
  int res = static_cast<int>(ledger::type::PublisherStatus::NOT_VERIFIED);
  PublishersInfoMap::const_iterator iter = map_publishers_info_.find(tabId);
  if (iter != map_publishers_info_.end()) {
    res = static_cast<int>(iter->second->status);
  }
  return res;
}

void HuhiRewardsNativeWorker::IncludeInAutoContribution(JNIEnv* env,
        const base::android::JavaParamRef<jobject>& obj, uint64_t tabId,
        bool exclude) {
  PublishersInfoMap::iterator iter(map_publishers_info_.find(tabId));
  if (iter != map_publishers_info_.end()) {
    if (exclude) {
      iter->second->excluded = ledger::type::PublisherExclude::EXCLUDED;
    } else {
      iter->second->excluded = ledger::type::PublisherExclude::INCLUDED;
    }
    if (huhi_rewards_service_) {
      huhi_rewards_service_->SetPublisherExclude(iter->second->id, exclude);
    }
  }
}

void HuhiRewardsNativeWorker::RemovePublisherFromMap(JNIEnv* env,
        const base::android::JavaParamRef<jobject>& obj, uint64_t tabId) {
  PublishersInfoMap::const_iterator iter(map_publishers_info_.find(tabId));
  if (iter != map_publishers_info_.end()) {
    map_publishers_info_.erase(iter);
  }
}

void HuhiRewardsNativeWorker::OnGetRewardsParameters(
    huhi_rewards::RewardsService* rewards_service,
    ledger::type::RewardsParametersPtr parameters) {
  if (parameters) {
    parameters_ = *parameters;
  }

  if (rewards_service) {
    rewards_service->FetchBalance(
      base::Bind(
        &HuhiRewardsNativeWorker::OnBalance,
        weak_factory_.GetWeakPtr()));
  }
}

void HuhiRewardsNativeWorker::OnBalance(
    const ledger::type::Result result,
    ledger::type::BalancePtr balance) {
  if (result == ledger::type::Result::LEDGER_OK && balance) {
    balance_ = *balance;
  }

  JNIEnv* env = base::android::AttachCurrentThread();
  Java_HuhiRewardsNativeWorker_OnRewardsParameters(
      env, weak_java_huhi_rewards_native_worker_.get(env), 0);
}

base::android::ScopedJavaLocalRef<jstring>
    HuhiRewardsNativeWorker::GetWalletBalance(JNIEnv* env,
    const base::android::JavaParamRef<jobject>& obj) {
  std::string json_balance;
  base::DictionaryValue json_root;
  json_root.SetDoubleKey("total", balance_.total);

  auto json_wallets = std::make_unique<base::DictionaryValue>();
  for (const auto & item : balance_.wallets) {
    json_wallets->SetDoubleKey(item.first, item.second);
  }
  json_root.SetDictionary("wallets", std::move(json_wallets));
  base::JSONWriter::Write(json_root, &json_balance);

  return base::android::ConvertUTF8ToJavaString(env, json_balance);
}

double HuhiRewardsNativeWorker::GetWalletRate(JNIEnv* env,
    const base::android::JavaParamRef<jobject>& obj) {
  return parameters_.rate;
}

void HuhiRewardsNativeWorker::FetchGrants(JNIEnv* env,
    const base::android::JavaParamRef<jobject>& obj) {
  if (huhi_rewards_service_) {
    huhi_rewards_service_->FetchPromotions();
  }
}

void HuhiRewardsNativeWorker::StartProcess(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& obj) {
  if (huhi_rewards_service_) {
    huhi_rewards_service_->StartProcess(base::Bind(
          &HuhiRewardsNativeWorker::OnStartProcess,
          weak_factory_.GetWeakPtr()));
  }
}

void HuhiRewardsNativeWorker::OnStartProcess(
    const ledger::type::Result result) {
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_HuhiRewardsNativeWorker_OnStartProcess(
      env, weak_java_huhi_rewards_native_worker_.get(env));
}

void HuhiRewardsNativeWorker::GetCurrentBalanceReport(JNIEnv* env,
        const base::android::JavaParamRef<jobject>& obj) {
  if (huhi_rewards_service_) {
    auto now = base::Time::Now();
    base::Time::Exploded exploded;
    now.LocalExplode(&exploded);

    huhi_rewards_service_->GetBalanceReport(
        exploded.month, exploded.year,
        base::BindOnce(&HuhiRewardsNativeWorker::OnGetCurrentBalanceReport,
                       base::Unretained(this), huhi_rewards_service_));
  }
}

void HuhiRewardsNativeWorker::OnGetCurrentBalanceReport(
        huhi_rewards::RewardsService* rewards_service,
        const ledger::type::Result result,
        ledger::type::BalanceReportInfoPtr report) {
  base::android::ScopedJavaLocalRef<jdoubleArray> java_array;
  JNIEnv* env = base::android::AttachCurrentThread();
  if (report) {
    std::vector<double> values;
    values.push_back(report->grants);
    values.push_back(report->earning_from_ads);
    values.push_back(report->auto_contribute);
    values.push_back(report->recurring_donation);
    values.push_back(report->one_time_donation);
    java_array = base::android::ToJavaDoubleArray(env, values);
  }
  Java_HuhiRewardsNativeWorker_OnGetCurrentBalanceReport(env,
        weak_java_huhi_rewards_native_worker_.get(env), java_array);
}

void HuhiRewardsNativeWorker::Donate(JNIEnv* env,
        const base::android::JavaParamRef<jobject>& obj,
        const base::android::JavaParamRef<jstring>& publisher_key,
        int amount, bool recurring) {
  if (huhi_rewards_service_) {
    huhi_rewards_service_->OnTip(
      base::android::ConvertJavaStringToUTF8(env, publisher_key), amount,
        recurring);
    if (!recurring) {
      Java_HuhiRewardsNativeWorker_OnOneTimeTip(env,
        weak_java_huhi_rewards_native_worker_.get(env));
    }
  }
}

void HuhiRewardsNativeWorker::GetAllNotifications(JNIEnv* env,
        const base::android::JavaParamRef<jobject>& obj) {
  if (!huhi_rewards_service_) {
    return;
  }
  huhi_rewards::RewardsNotificationService* notification_service =
    huhi_rewards_service_->GetNotificationService();
  if (notification_service) {
    notification_service->GetNotifications();
  }
}

void HuhiRewardsNativeWorker::DeleteNotification(JNIEnv* env,
        const base::android::JavaParamRef<jobject>& obj,
        const base::android::JavaParamRef<jstring>& notification_id) {
  if (!huhi_rewards_service_) {
    return;
  }
  huhi_rewards::RewardsNotificationService* notification_service =
    huhi_rewards_service_->GetNotificationService();
  if (notification_service) {
    notification_service->DeleteNotification(
      base::android::ConvertJavaStringToUTF8(env, notification_id));
  }
}

void HuhiRewardsNativeWorker::GetGrant(JNIEnv* env,
    const base::android::JavaParamRef<jobject>& obj,
    const base::android::JavaParamRef<jstring>& promotionId) {
  if (huhi_rewards_service_) {
    std::string promotion_id =
      base::android::ConvertJavaStringToUTF8(env, promotionId);
    huhi_rewards_service_->ClaimPromotion(promotion_id,
      base::BindOnce(
        &HuhiRewardsNativeWorker::OnClaimPromotion,
        base::Unretained(this)));
  }
}

void HuhiRewardsNativeWorker::OnClaimPromotion(
    const ledger::type::Result result,
    ledger::type::PromotionPtr promotion) {
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_HuhiRewardsNativeWorker_OnClaimPromotion(env,
      weak_java_huhi_rewards_native_worker_.get(env),
      static_cast<int>(result));
}

base::android::ScopedJavaLocalRef<jobjectArray>
    HuhiRewardsNativeWorker::GetCurrentGrant(JNIEnv* env,
      const base::android::JavaParamRef<jobject>& obj,
      int position) {
  if ((size_t)position > promotions_.size() - 1) {
    return base::android::ScopedJavaLocalRef<jobjectArray>();
  }
  std::stringstream stream;
  stream << std::fixed << std::setprecision(2) <<
      (promotions_[position])->approximate_value;
  std::vector<std::string> values;
  values.push_back(stream.str());
  values.push_back(
    std::to_string((promotions_[position])->expires_at));
  values.push_back(
      std::to_string(static_cast<int>((promotions_[position])->type)));

  return base::android::ToJavaArrayOfStrings(env, values);
}

void HuhiRewardsNativeWorker::GetPendingContributionsTotal(JNIEnv* env,
        const base::android::JavaParamRef<jobject>& obj) {
  if (huhi_rewards_service_) {
    huhi_rewards_service_->GetPendingContributionsTotal(base::Bind(
          &HuhiRewardsNativeWorker::OnGetPendingContributionsTotal,
          weak_factory_.GetWeakPtr()));
  }
}

void HuhiRewardsNativeWorker::GetRecurringDonations(JNIEnv* env,
        const base::android::JavaParamRef<jobject>& obj) {
  if (huhi_rewards_service_) {
    huhi_rewards_service_->GetRecurringTips(base::Bind(
          &HuhiRewardsNativeWorker::OnGetRecurringTips,
          weak_factory_.GetWeakPtr()));
  }
}

void HuhiRewardsNativeWorker::OnGetRecurringTips(
    ledger::type::PublisherInfoList list) {
  map_recurrent_publishers_.clear();
  for (const auto& item : list) {
    map_recurrent_publishers_[item->id] = item->Clone();
  }

  JNIEnv* env = base::android::AttachCurrentThread();
  Java_HuhiRewardsNativeWorker_OnRecurringDonationUpdated(env,
        weak_java_huhi_rewards_native_worker_.get(env));
}

bool HuhiRewardsNativeWorker::IsCurrentPublisherInRecurrentDonations(
    JNIEnv* env, const base::android::JavaParamRef<jobject>& obj,
    const base::android::JavaParamRef<jstring>& publisher) {
  return map_recurrent_publishers_.find(
    base::android::ConvertJavaStringToUTF8(env, publisher)) !=
      map_recurrent_publishers_.end();
}


void HuhiRewardsNativeWorker::GetAutoContributeProperties(JNIEnv* env,
    const base::android::JavaParamRef<jobject>& obj) {
  if (huhi_rewards_service_) {
    huhi_rewards_service_->GetAutoContributeProperties(
        base::Bind(&HuhiRewardsNativeWorker::OnGetAutoContributeProperties,
                   weak_factory_.GetWeakPtr()));
  }
}

void HuhiRewardsNativeWorker::OnGetAutoContributeProperties(
    ledger::type::AutoContributePropertiesPtr properties) {
  if (properties) {
    auto_contrib_properties_ = std::move(properties);
  }

  JNIEnv* env = base::android::AttachCurrentThread();
  Java_HuhiRewardsNativeWorker_OnGetAutoContributeProperties(
      env, weak_java_huhi_rewards_native_worker_.get(env));
}

bool HuhiRewardsNativeWorker::IsAutoContributeEnabled(JNIEnv* env,
    const base::android::JavaParamRef<jobject>& obj) {
  if (!auto_contrib_properties_) {
    return false;
  }

  return auto_contrib_properties_->enabled_contribute;
}

void HuhiRewardsNativeWorker::GetReconcileStamp(JNIEnv* env,
    const base::android::JavaParamRef<jobject>& obj) {
  if (huhi_rewards_service_) {
    huhi_rewards_service_->GetReconcileStamp(base::Bind(
            &HuhiRewardsNativeWorker::OnGetGetReconcileStamp,
            weak_factory_.GetWeakPtr()));
  }
}

void HuhiRewardsNativeWorker::ResetTheWholeState(JNIEnv* env,
    const base::android::JavaParamRef<jobject>& obj) {
  if (huhi_rewards_service_) {
    huhi_rewards_service_->CompleteReset(base::Bind(
           &HuhiRewardsNativeWorker::OnResetTheWholeState,
           weak_factory_.GetWeakPtr()));
  } else {
    JNIEnv* env = base::android::AttachCurrentThread();

    Java_HuhiRewardsNativeWorker_OnResetTheWholeState(env,
            weak_java_huhi_rewards_native_worker_.get(env), false);
  }
}

void HuhiRewardsNativeWorker::OnResetTheWholeState(const bool success) {
  JNIEnv* env = base::android::AttachCurrentThread();

  Java_HuhiRewardsNativeWorker_OnResetTheWholeState(env,
          weak_java_huhi_rewards_native_worker_.get(env), success);
}

double HuhiRewardsNativeWorker::GetPublisherRecurrentDonationAmount(
    JNIEnv* env, const base::android::JavaParamRef<jobject>& obj,
    const base::android::JavaParamRef<jstring>& publisher) {
  double amount(0.0);
  auto it = map_recurrent_publishers_.find(
    base::android::ConvertJavaStringToUTF8(env, publisher));
  if (it != map_recurrent_publishers_.end()) {
    // for Recurrent Donations, the amount is stored in ContentSite::percentage
    amount = it->second->percent;
  }
  return  amount;
}

void HuhiRewardsNativeWorker::RemoveRecurring(JNIEnv* env,
    const base::android::JavaParamRef<jobject>& obj,
    const base::android::JavaParamRef<jstring>& publisher) {
  if (huhi_rewards_service_) {
      huhi_rewards_service_->RemoveRecurringTip(
        base::android::ConvertJavaStringToUTF8(env, publisher));
  }
}

void HuhiRewardsNativeWorker::OnGetGetReconcileStamp(uint64_t timestamp) {
  JNIEnv* env = base::android::AttachCurrentThread();

  Java_HuhiRewardsNativeWorker_OnGetReconcileStamp(env,
          weak_java_huhi_rewards_native_worker_.get(env), timestamp);
}

void HuhiRewardsNativeWorker::OnGetPendingContributionsTotal(double amount) {
  JNIEnv* env = base::android::AttachCurrentThread();

  Java_HuhiRewardsNativeWorker_OnGetPendingContributionsTotal(env,
        weak_java_huhi_rewards_native_worker_.get(env), amount);
}

void HuhiRewardsNativeWorker::OnNotificationAdded(
    huhi_rewards::RewardsNotificationService* rewards_notification_service,
    const huhi_rewards::RewardsNotificationService::RewardsNotification&
      notification) {
  JNIEnv* env = base::android::AttachCurrentThread();

  Java_HuhiRewardsNativeWorker_OnNotificationAdded(env,
        weak_java_huhi_rewards_native_worker_.get(env),
        base::android::ConvertUTF8ToJavaString(env, notification.id_),
        notification.type_,
        notification.timestamp_,
        base::android::ToJavaArrayOfStrings(env, notification.args_));
}

void HuhiRewardsNativeWorker::OnGetAllNotifications(
    huhi_rewards::RewardsNotificationService* rewards_notification_service,
    const huhi_rewards::RewardsNotificationService::RewardsNotificationsList&
      notifications_list) {
  JNIEnv* env = base::android::AttachCurrentThread();

  // Notify about notifications count
  Java_HuhiRewardsNativeWorker_OnNotificationsCount(env,
        weak_java_huhi_rewards_native_worker_.get(env),
        notifications_list.size());

  huhi_rewards::RewardsNotificationService::RewardsNotificationsList::
    const_iterator iter =
      std::max_element(notifications_list.begin(), notifications_list.end(),
        [](const huhi_rewards::RewardsNotificationService::
            RewardsNotification& notification_a,
          const huhi_rewards::RewardsNotificationService::
            RewardsNotification& notification_b) {
        return notification_a.timestamp_ > notification_b.timestamp_;
      });

  if (iter != notifications_list.end()) {
    Java_HuhiRewardsNativeWorker_OnGetLatestNotification(env,
        weak_java_huhi_rewards_native_worker_.get(env),
        base::android::ConvertUTF8ToJavaString(env, iter->id_),
        iter->type_,
        iter->timestamp_,
        base::android::ToJavaArrayOfStrings(env, iter->args_));
  }
}

void HuhiRewardsNativeWorker::OnNotificationDeleted(
      huhi_rewards::RewardsNotificationService* rewards_notification_service,
      const huhi_rewards::RewardsNotificationService::RewardsNotification&
        notification) {
  JNIEnv* env = base::android::AttachCurrentThread();

  Java_HuhiRewardsNativeWorker_OnNotificationDeleted(env,
        weak_java_huhi_rewards_native_worker_.get(env),
        base::android::ConvertUTF8ToJavaString(env, notification.id_));
}

void HuhiRewardsNativeWorker::OnPromotionFinished(
    huhi_rewards::RewardsService* rewards_service,
    const ledger::type::Result result,
    ledger::type::PromotionPtr promotion) {
  JNIEnv* env = base::android::AttachCurrentThread();

  Java_HuhiRewardsNativeWorker_OnGrantFinish(env,
        weak_java_huhi_rewards_native_worker_.get(env),
        static_cast<int>(result));
}

int HuhiRewardsNativeWorker::GetAdsPerHour(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& obj) {
  auto* ads_service_ = huhi_ads::AdsServiceFactory::GetForProfile(
      ProfileManager::GetActiveUserProfile()->GetOriginalProfile());
  if (!ads_service_) {
    return DEFAULT_ADS_PER_HOUR;
  }
  return ads_service_->GetAdsPerHour();
}

void HuhiRewardsNativeWorker::SetAdsPerHour(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& obj,
    jint value) {
  auto* ads_service_ = huhi_ads::AdsServiceFactory::GetForProfile(
      ProfileManager::GetActiveUserProfile()->GetOriginalProfile());
  if (!ads_service_) {
    return;
  }
  ads_service_->SetAdsPerHour(value);
}

void HuhiRewardsNativeWorker::SetAutoContributionAmount(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& obj,
    jdouble value) {
  if (huhi_rewards_service_) {
    huhi_rewards_service_->SetAutoContributionAmount(value);
  }
}

bool HuhiRewardsNativeWorker::IsAnonWallet(JNIEnv* env,
    const base::android::JavaParamRef<jobject>& jcaller) {
  if (huhi_rewards_service_) {
    return huhi_rewards_service_->OnlyAnonWallet();
  }
  return false;
}

void HuhiRewardsNativeWorker::GetExternalWallet(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& obj) {
  if (huhi_rewards_service_) {
    auto callback = base::Bind(
        &HuhiRewardsNativeWorker::OnGetExternalWallet,
        base::Unretained(this));
    huhi_rewards_service_->GetUpholdWallet(callback);
  }
}

void HuhiRewardsNativeWorker::OnGetExternalWallet(
    const ledger::type::Result result,
    ledger::type::UpholdWalletPtr wallet) {
  std::string json_wallet;
  if (!wallet) {
    json_wallet = "";
  } else {
    base::Value dict(base::Value::Type::DICTIONARY);
    dict.SetStringKey("token", wallet->token);
    dict.SetStringKey("address", wallet->address);

    // enum class WalletStatus : int32_t
    dict.SetIntKey("status", static_cast<int32_t>(wallet->status));
    dict.SetStringKey("verify_url", wallet->verify_url);
    dict.SetStringKey("add_url", wallet->add_url);
    dict.SetStringKey("withdraw_url", wallet->withdraw_url);
    dict.SetStringKey("user_name", wallet->user_name);
    dict.SetStringKey("account_url", wallet->account_url);
    dict.SetStringKey("login_url", wallet->login_url);
    base::JSONWriter::Write(dict, &json_wallet);
  }
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_HuhiRewardsNativeWorker_OnGetExternalWallet(env,
      weak_java_huhi_rewards_native_worker_.get(env),
      static_cast<int>(result),
      base::android::ConvertUTF8ToJavaString(env, json_wallet));
}

void HuhiRewardsNativeWorker::DisconnectWallet(JNIEnv* env,
    const base::android::JavaParamRef<jobject>& obj,
    const base::android::JavaParamRef<jstring>& wallet_type) {
  if (huhi_rewards_service_) {
    std::string str_wallet_type =
        base::android::ConvertJavaStringToUTF8(env, wallet_type);
    huhi_rewards_service_->DisconnectWallet(str_wallet_type);
  }
}

void HuhiRewardsNativeWorker::OnDisconnectWallet(
    huhi_rewards::RewardsService* rewards_service,
    const ledger::type::Result result,
    const std::string& wallet_type) {
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_HuhiRewardsNativeWorker_OnDisconnectWallet(env,
        weak_java_huhi_rewards_native_worker_.get(env),
        static_cast<int>(result),
        base::android::ConvertUTF8ToJavaString(env, wallet_type));
}

void HuhiRewardsNativeWorker::ProcessRewardsPageUrl(JNIEnv* env,
        const base::android::JavaParamRef<jobject>& obj,
        const base::android::JavaParamRef<jstring>& path,
        const base::android::JavaParamRef<jstring>& query) {
  if (huhi_rewards_service_) {
    std::string cpath = base::android::ConvertJavaStringToUTF8(env, path);
    std::string cquery = base::android::ConvertJavaStringToUTF8(env, query);
    auto callback = base::Bind(
        &HuhiRewardsNativeWorker::OnProcessRewardsPageUrl,
        base::Unretained(this));
    huhi_rewards_service_->ProcessRewardsPageUrl(cpath, cquery, callback);
  }
}

void HuhiRewardsNativeWorker::OnProcessRewardsPageUrl(
    const ledger::type::Result result,
    const std::string& wallet_type,
    const std::string& action,
    const std::map<std::string, std::string>& args) {
  std::string json_args = StdStrStrMapToJsonString(args);
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_HuhiRewardsNativeWorker_OnProcessRewardsPageUrl(env,
        weak_java_huhi_rewards_native_worker_.get(env),
        static_cast<int>(result),
        base::android::ConvertUTF8ToJavaString(env, wallet_type),
        base::android::ConvertUTF8ToJavaString(env, action),
        base::android::ConvertUTF8ToJavaString(env, json_args));
}

std::string HuhiRewardsNativeWorker::StdStrStrMapToJsonString(
    const std::map<std::string, std::string>& args) {
    std::string json_args;
    base::Value dict(base::Value::Type::DICTIONARY);
    for (const auto & item : args) {
      dict.SetStringKey(item.first, item.second);
    }
    base::JSONWriter::Write(dict, &json_args);
    return json_args;
}

void HuhiRewardsNativeWorker::RecoverWallet(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& obj,
    const base::android::JavaParamRef<jstring>& pass_phrase) {
  if (huhi_rewards_service_) {
    huhi_rewards_service_->RecoverWallet(
        base::android::ConvertJavaStringToUTF8(env, pass_phrase));
  }
}

void HuhiRewardsNativeWorker::OnRecoverWallet(
    huhi_rewards::RewardsService* rewards_service,
    const ledger::type::Result result) {
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_HuhiRewardsNativeWorker_OnRecoverWallet(
      env, weak_java_huhi_rewards_native_worker_.get(env),
      static_cast<int>(result));
}

void HuhiRewardsNativeWorker::RefreshPublisher(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& obj,
    const base::android::JavaParamRef<jstring>& publisher_key) {
  if (!huhi_rewards_service_) {
    NOTREACHED();
    return;
  }
  huhi_rewards_service_->RefreshPublisher(
      base::android::ConvertJavaStringToUTF8(env, publisher_key),
      base::BindOnce(&HuhiRewardsNativeWorker::OnRefreshPublisher,
                     base::Unretained(this)));
}

void HuhiRewardsNativeWorker::OnRefreshPublisher(
    const ledger::type::PublisherStatus status,
    const std::string& publisher_key) {
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_HuhiRewardsNativeWorker_OnRefreshPublisher(
      env, weak_java_huhi_rewards_native_worker_.get(env),
      static_cast<int>(status),
      base::android::ConvertUTF8ToJavaString(env, publisher_key));
}

void HuhiRewardsNativeWorker::SetAutoContributeEnabled(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& obj,
    bool isAutoContributeEnabled) {
  if (huhi_rewards_service_) {
    huhi_rewards_service_->SetAutoContributeEnabled(isAutoContributeEnabled);
  }
}

static void JNI_HuhiRewardsNativeWorker_Init(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& jcaller) {
  new HuhiRewardsNativeWorker(env, jcaller);
}

}  // namespace android
}  // namespace chrome
