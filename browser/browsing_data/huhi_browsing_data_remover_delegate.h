/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_BROWSING_DATA_HUHI_BROWSING_DATA_REMOVER_DELEGATE_H_
#define HUHI_BROWSER_BROWSING_DATA_HUHI_BROWSING_DATA_REMOVER_DELEGATE_H_

#include "base/time/time.h"
#include "chrome/browser/browsing_data/chrome_browsing_data_remover_delegate.h"

namespace content_settings {
class HuhiPrefProvider;
}  // namespace content_settings

class Profile;

class HuhiBrowsingDataRemoverDelegate
    : public ChromeBrowsingDataRemoverDelegate {
 public:
  explicit HuhiBrowsingDataRemoverDelegate(
      content::BrowserContext* browser_context);
  ~HuhiBrowsingDataRemoverDelegate() override = default;

  HuhiBrowsingDataRemoverDelegate(
      const HuhiBrowsingDataRemoverDelegate&) = delete;
  HuhiBrowsingDataRemoverDelegate operator=(
      const HuhiBrowsingDataRemoverDelegate&) = delete;

 private:
  FRIEND_TEST_ALL_PREFIXES(HuhiBrowsingDataRemoverDelegateTest,
                           ShieldsSettingsClearTest);

  // ChromeBrowsingDataRemoverDelegate overrides:
  void RemoveEmbedderData(const base::Time& delete_begin,
                          const base::Time& delete_end,
                          uint64_t remove_mask,
                          content::BrowsingDataFilterBuilder* filter_builder,
                          uint64_t origin_type_mask,
                          base::OnceCallback<void(uint64_t)> callback)
                          override;

  void ClearShieldsSettings(base::Time begin_time, base::Time end_time);

  Profile* profile_;
};

#endif  // HUHI_BROWSER_BROWSING_DATA_HUHI_BROWSING_DATA_REMOVER_DELEGATE_H_
