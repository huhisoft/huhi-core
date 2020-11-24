/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_WEBUI_HUHI_REWARDS_SOURCE_H_
#define HUHI_BROWSER_UI_WEBUI_HUHI_REWARDS_SOURCE_H_

#include <string>
#include <vector>

#include "base/macros.h"
#include "chrome/browser/bitmap_fetcher/bitmap_fetcher_service.h"
#include "content/public/browser/url_data_source.h"

class GURL;
class Profile;
class SkBitmap;

class HuhiRewardsSource : public content::URLDataSource {
 public:
  explicit HuhiRewardsSource(Profile* profile);

  ~HuhiRewardsSource() override;

  // content::URLDataSource implementation.
  std::string GetSource() override;
  void StartDataRequest(
      const GURL& url,
      const content::WebContents::Getter& wc_getter,
      content::URLDataSource::GotDataCallback got_data_callback)
      override;
  std::string GetMimeType(const std::string&) override;
  bool AllowCaching() override;
  bool ShouldReplaceExistingSource() override;
  bool ShouldServiceRequest(const GURL& url,
                            content::BrowserContext* browser_context,
                            int render_process_id) override;

 private:
  void OnBitmapFetched(
      content::URLDataSource::GotDataCallback got_data_callback,
      const GURL& url,
      const SkBitmap& bitmap);

  Profile* profile_;
  std::vector<GURL> resource_fetchers_;

  DISALLOW_COPY_AND_ASSIGN(HuhiRewardsSource);
};

#endif  // HUHI_BROWSER_UI_WEBUI_HUHI_REWARDS_SOURCE_H_
