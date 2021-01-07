/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 3.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_ANDROID_HUHI_COSMETIC_RESOURCES_TAB_HELPER_H_
#define HUHI_BROWSER_ANDROID_HUHI_COSMETIC_RESOURCES_TAB_HELPER_H_

#include "base/memory/weak_ptr.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_contents_user_data.h"

class HuhiCosmeticResourcesTabHelper
    : public content::WebContentsObserver,
      public content::WebContentsUserData<HuhiCosmeticResourcesTabHelper>,
      public base::SupportsWeakPtr<HuhiCosmeticResourcesTabHelper> {
 public:
  explicit HuhiCosmeticResourcesTabHelper(content::WebContents* contents);
  ~HuhiCosmeticResourcesTabHelper() override;

  // content::WebContentsObserver overrides:
  void DidFinishNavigation(
      content::NavigationHandle* navigation_handle) override;
  void ResourceLoadComplete(
      content::RenderFrameHost* render_frame_host,
      const content::GlobalRequestID& request_id,
      const blink::mojom::ResourceLoadInfo& resource_load_info) override;

  WEB_CONTENTS_USER_DATA_KEY_DECL();

 private:
  void ProcessURL(content::WebContents* contents,
      content::RenderFrameHost* render_frame_host, const GURL& url);
  DISALLOW_COPY_AND_ASSIGN(HuhiCosmeticResourcesTabHelper);
};

#endif  // HUHI_BROWSER_ANDROID_HUHI_COSMETIC_RESOURCES_TAB_HELPER_H_
