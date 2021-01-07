/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_SYNC_HUHI_SYNC_DEVICES_ANDROID_H_
#define HUHI_BROWSER_SYNC_HUHI_SYNC_DEVICES_ANDROID_H_

#include <jni.h>

#include "base/android/jni_weak_ref.h"
#include "base/scoped_observer.h"
#include "base/values.h"
#include "chrome/browser/sync/profile_sync_service_android.h"
#include "components/sync_device_info/device_info_tracker.h"

namespace syncer {
class HuhiProfileSyncService;
}

namespace chrome {
namespace android {

class HuhiSyncDevicesAndroid : public syncer::DeviceInfoTracker::Observer {
 public:
  HuhiSyncDevicesAndroid(JNIEnv* env,
                          const base::android::JavaRef<jobject>& obj);
  virtual ~HuhiSyncDevicesAndroid();

  void Destroy(JNIEnv* env,
               const base::android::JavaParamRef<jobject>& jcaller);

  base::android::ScopedJavaLocalRef<jstring> GetSyncDeviceListJson(
      JNIEnv* env,
      const base::android::JavaParamRef<jobject>& jcaller);

  void DeleteDevice(JNIEnv* env,
                    const base::android::JavaParamRef<jobject>& jcaller,
                    const base::android::JavaParamRef<jstring>& device_guid);

 private:
  // syncer::DeviceInfoTracker::Observer
  void OnDeviceInfoChange() override;

  base::Value GetSyncDeviceList();

  syncer::HuhiProfileSyncService* GetSyncService() const;

  ScopedObserver<syncer::DeviceInfoTracker, syncer::DeviceInfoTracker::Observer>
      device_info_tracker_observer_{this};

  JavaObjectWeakGlobalRef weak_java_huhi_sync_worker_;
  Profile* profile_ = nullptr;
};

}  // namespace android
}  // namespace chrome

#endif  // HUHI_BROWSER_SYNC_HUHI_SYNC_DEVICES_ANDROID_H_
