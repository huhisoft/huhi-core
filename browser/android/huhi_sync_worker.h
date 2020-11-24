/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_ANDROID_HUHI_SYNC_WORKER_H_
#define HUHI_BROWSER_ANDROID_HUHI_SYNC_WORKER_H_

#include <jni.h>
#include <string>

#include "base/android/jni_weak_ref.h"
#include "base/scoped_observer.h"
#include "components/sync/driver/sync_service.h"
#include "components/sync/driver/sync_service_observer.h"

class Profile;

namespace syncer {
class HuhiProfileSyncService;
}  // namespace syncer

namespace chrome {
namespace android {

class HuhiSyncWorker : public syncer::SyncServiceObserver {
 public:
  HuhiSyncWorker(JNIEnv* env,
                  const base::android::JavaRef<jobject>& obj);
  ~HuhiSyncWorker() override;

  void Destroy(JNIEnv* env,
               const base::android::JavaParamRef<jobject>& jcaller);

  base::android::ScopedJavaLocalRef<jstring> GetSyncCodeWords(
      JNIEnv* env,
      const base::android::JavaParamRef<jobject>& jcaller);

  void SaveCodeWords(JNIEnv* env,
                     const base::android::JavaParamRef<jobject>& jcaller,
                     const base::android::JavaParamRef<jstring>& passphrase);

  void RequestSync(JNIEnv* env,
                   const base::android::JavaParamRef<jobject>& jcaller);

  void FinalizeSyncSetup(JNIEnv* env,
                         const base::android::JavaParamRef<jobject>& jcaller);

  bool IsFirstSetupComplete(
      JNIEnv* env,
      const base::android::JavaParamRef<jobject>& jcaller);

  void ResetSync(JNIEnv* env,
                 const base::android::JavaParamRef<jobject>& jcaller);

  bool GetSyncV1WasEnabled(JNIEnv* env,
                           const base::android::JavaParamRef<jobject>& jcaller);

  bool GetSyncV2MigrateNoticeDismissed(
      JNIEnv* env,
      const base::android::JavaParamRef<jobject>& jcaller);

  void SetSyncV2MigrateNoticeDismissed(
      JNIEnv* env,
      const base::android::JavaParamRef<jobject>& jcaller,
      bool sync_v2_migration_notice_dismissed);

 private:
  syncer::HuhiProfileSyncService* GetSyncService() const;
  void MarkFirstSetupComplete();

  // syncer::SyncServiceObserver implementation.
  void OnStateChanged(syncer::SyncService* sync) override;

  void OnResetDone();

  JavaObjectWeakGlobalRef weak_java_huhi_sync_worker_;
  Profile* profile_ = nullptr;

  std::string passphrase_;

  ScopedObserver<syncer::SyncService, syncer::SyncServiceObserver>
      sync_service_observer_{this};
  base::WeakPtrFactory<HuhiSyncWorker> weak_ptr_factory_{this};

  DISALLOW_COPY_AND_ASSIGN(HuhiSyncWorker);
};

}  // namespace android
}  // namespace chrome

#endif  // HUHI_BROWSER_ANDROID_HUHI_SYNC_WORKER_H_
