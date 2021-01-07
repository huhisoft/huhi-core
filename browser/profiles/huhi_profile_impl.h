/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_PROFILES_HUHI_PROFILE_IMPL_H_
#define HUHI_BROWSER_PROFILES_HUHI_PROFILE_IMPL_H_

#include "chrome/browser/profiles/profile_impl.h"

#include "base/memory/weak_ptr.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"

class PrefStore;

class HuhiProfileImpl : public ProfileImpl,
                         public content::NotificationObserver {
 public:
  HuhiProfileImpl(const base::FilePath& path,
                   Delegate* delegate,
                   CreateMode create_mode,
                   base::Time creation_time,
                   scoped_refptr<base::SequencedTaskRunner> io_task_runner);
  ~HuhiProfileImpl() override;

  // content::NotificationObserver override.
  void Observe(int type,
               const content::NotificationSource& source,
               const content::NotificationDetails& details) override;

 private:
  // Listens for parent profile destruction.
  content::NotificationRegistrar notification_registrar_;

  base::WeakPtrFactory<HuhiProfileImpl> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(HuhiProfileImpl);
};

#endif  // HUHI_BROWSER_PROFILES_HUHI_PROFILE_IMPL_H_
