/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_HUHI_DRM_TAB_HELPER_H_
#define HUHI_BROWSER_HUHI_DRM_TAB_HELPER_H_

#include <string>

#include "base/scoped_observer.h"
#include "huhi/components/huhi_drm/huhi_drm.mojom.h"
#include "components/component_updater/component_updater_service.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_contents_receiver_set.h"
#include "content/public/browser/web_contents_user_data.h"

// Reacts to DRM content detected on the renderer side.
class HuhiDrmTabHelper final
    : public content::WebContentsObserver,
      public content::WebContentsUserData<HuhiDrmTabHelper>,
      public huhi_drm::mojom::HuhiDRM,
      public component_updater::ComponentUpdateService::Observer {
 public:
  explicit HuhiDrmTabHelper(content::WebContents* contents);
  ~HuhiDrmTabHelper() override;

  bool ShouldShowWidevineOptIn() const;

  // content::WebContentsObserver
  void DidStartNavigation(
      content::NavigationHandle* navigation_handle) override;

  // blink::mojom::HuhiDRM
  void OnWidevineKeySystemAccessRequest() override;

  // component_updater::ComponentUpdateService::Observer
  void OnEvent(Events event, const std::string& id) override;

  WEB_CONTENTS_USER_DATA_KEY_DECL();

 private:
  content::WebContentsFrameReceiverSet<huhi_drm::mojom::HuhiDRM> receivers_;

  // Permission request is done only once during the navigation. If user
  // chooses dismiss/deny, additional request is added again only when new
  // main frame navigation is started.
  bool is_permission_requested_ = false;

  // True if we are notified that a page requested widevine availability.
  bool is_widevine_requested_ = false;

  ScopedObserver<component_updater::ComponentUpdateService,
                 component_updater::ComponentUpdateService::Observer> observer_;
};

#endif  // HUHI_BROWSER_HUHI_DRM_TAB_HELPER_H_
