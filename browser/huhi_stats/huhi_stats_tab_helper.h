/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_HUHI_STATS_HUHI_STATS_TAB_HELPER_H_
#define HUHI_BROWSER_HUHI_STATS_HUHI_STATS_TAB_HELPER_H_

#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_contents_user_data.h"

namespace content {
class NavigationHandle;
class WebContents;
}  // namespace content

namespace huhi_stats {

class HuhiStatsUpdater;

class HuhiStatsTabHelper
    : public content::WebContentsObserver,
      public content::WebContentsUserData<HuhiStatsTabHelper> {
 public:
  explicit HuhiStatsTabHelper(content::WebContents*);
  ~HuhiStatsTabHelper() override;
  HuhiStatsTabHelper(const HuhiStatsTabHelper&) = delete;
  HuhiStatsTabHelper& operator=(const HuhiStatsTabHelper&) = delete;

  void NotifyStatsUpdater();

 private:
  void DidStartNavigation(content::NavigationHandle*) override;

  friend class content::WebContentsUserData<HuhiStatsTabHelper>;
  WEB_CONTENTS_USER_DATA_KEY_DECL();
};

}  // namespace huhi_stats
#endif  // HUHI_BROWSER_HUHI_STATS_HUHI_STATS_TAB_HELPER_H_
