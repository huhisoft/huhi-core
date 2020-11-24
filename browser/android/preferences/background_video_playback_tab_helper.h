/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_ANDROID_PREFERENCES_BACKGROUND_VIDEO_PLAYBACK_TAB_HELPER_H_
#define HUHI_BROWSER_ANDROID_PREFERENCES_BACKGROUND_VIDEO_PLAYBACK_TAB_HELPER_H_

#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_contents_user_data.h"

class BackgroundVideoPlaybackTabHelper
    : public content::WebContentsObserver,
      public content::WebContentsUserData<BackgroundVideoPlaybackTabHelper> {
 public:
  explicit BackgroundVideoPlaybackTabHelper(content::WebContents* contents);
  ~BackgroundVideoPlaybackTabHelper() override;

  // content::WebContentsObserver overrides:
  void DidFinishNavigation(
      content::NavigationHandle* navigation_handle) override;
  void ResourceLoadComplete(
      content::RenderFrameHost* render_frame_host,
      const content::GlobalRequestID& request_id,
      const blink::mojom::ResourceLoadInfo& resource_load_info) override;

  WEB_CONTENTS_USER_DATA_KEY_DECL();

 private:
  DISALLOW_COPY_AND_ASSIGN(BackgroundVideoPlaybackTabHelper);
};

#endif  // HUHI_BROWSER_ANDROID_PREFERENCES_BACKGROUND_VIDEO_PLAYBACK_TAB_HELPER_H_
