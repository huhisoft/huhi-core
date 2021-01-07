/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_WAYBACK_MACHINE_HUHI_WAYBACK_MACHINE_TAB_HELPER_H_
#define HUHI_COMPONENTS_HUHI_WAYBACK_MACHINE_HUHI_WAYBACK_MACHINE_TAB_HELPER_H_

#include <memory>

#include "base/memory/weak_ptr.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_contents_user_data.h"

class HuhiWaybackMachineDelegate;
class PrefService;

class HuhiWaybackMachineTabHelper
    : public content::WebContentsObserver,
      public content::WebContentsUserData<HuhiWaybackMachineTabHelper> {
 public:
  explicit HuhiWaybackMachineTabHelper(content::WebContents* contents);
  ~HuhiWaybackMachineTabHelper() override;

  HuhiWaybackMachineTabHelper(const HuhiWaybackMachineTabHelper&) = delete;
  HuhiWaybackMachineTabHelper& operator=(
      const HuhiWaybackMachineTabHelper&) = delete;

  void set_delegate(std::unique_ptr<HuhiWaybackMachineDelegate> delegate);

  WEB_CONTENTS_USER_DATA_KEY_DECL();
 private:
  FRIEND_TEST_ALL_PREFIXES(HuhiWaybackMachineTest, InfobarAddTest);

  // content::WebContentsObserver overrides:
  void DidFinishNavigation(
      content::NavigationHandle* navigation_handle) override;

  void CreateInfoBar();
  bool IsWaybackMachineEnabled() const;

  // virtual for test.
  virtual bool ShouldAttachWaybackMachineInfoBar(int response_code) const;

  PrefService* pref_service_ = nullptr;
  std::unique_ptr<HuhiWaybackMachineDelegate> delegate_;

  base::WeakPtrFactory<HuhiWaybackMachineTabHelper> weak_factory_;
};

#endif  // HUHI_COMPONENTS_HUHI_WAYBACK_MACHINE_HUHI_WAYBACK_MACHINE_TAB_HELPER_H_
