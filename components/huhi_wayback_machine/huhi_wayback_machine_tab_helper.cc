/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/components/huhi_wayback_machine/huhi_wayback_machine_tab_helper.h"

#include <utility>

#include "base/bind.h"
#include "base/command_line.h"
#include "base/containers/flat_set.h"
#include "base/threading/sequenced_task_runner_handle.h"
#include "huhi/components/huhi_wayback_machine/huhi_wayback_machine_delegate.h"
#include "huhi/components/huhi_wayback_machine/huhi_wayback_machine_utils.h"
#include "huhi/components/huhi_wayback_machine/pref_names.h"
#include "components/prefs/pref_service.h"
#include "components/user_prefs/user_prefs.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/navigation_handle.h"
#include "content/public/browser/web_contents.h"
#include "net/http/http_response_headers.h"
#include "net/http/http_status_code.h"

HuhiWaybackMachineTabHelper::HuhiWaybackMachineTabHelper(
    content::WebContents* contents)
    : WebContentsObserver(contents),
      weak_factory_(this) {
  pref_service_ = user_prefs::UserPrefs::Get(contents->GetBrowserContext());
}

HuhiWaybackMachineTabHelper::~HuhiWaybackMachineTabHelper() = default;

void HuhiWaybackMachineTabHelper::set_delegate(
    std::unique_ptr<HuhiWaybackMachineDelegate> delegate) {
  DCHECK(delegate);
  delegate_ = std::move(delegate);
}

void HuhiWaybackMachineTabHelper::DidFinishNavigation(
    content::NavigationHandle* navigation_handle) {
  DCHECK(delegate_);
  if (!IsWaybackMachineEnabled())
    return;

  if (IsWaybackMachineDisabledFor(navigation_handle->GetURL()))
    return;

  if (!navigation_handle->IsInMainFrame() ||
      navigation_handle->IsSameDocument()) {
    return;
  }

  if (const net::HttpResponseHeaders* header =
          navigation_handle->GetResponseHeaders()) {
    if (!ShouldAttachWaybackMachineInfoBar(header->response_code()))
      return;

    // Create infobar in the next loop for not blocking navigation.
    base::SequencedTaskRunnerHandle::Get()->PostTask(
        FROM_HERE, base::BindOnce(&HuhiWaybackMachineTabHelper::CreateInfoBar,
                                  weak_factory_.GetWeakPtr()));
  }
}

void HuhiWaybackMachineTabHelper::CreateInfoBar() {
  DCHECK(delegate_);
  delegate_->CreateInfoBar(web_contents());
}

bool HuhiWaybackMachineTabHelper::IsWaybackMachineEnabled() const {
  return pref_service_->GetBoolean(kHuhiWaybackMachineEnabled);
}

bool HuhiWaybackMachineTabHelper::ShouldAttachWaybackMachineInfoBar(
    int response_code) const {
  static base::flat_set<int> responses = {
      net::HTTP_NOT_FOUND,              // 404
      net::HTTP_REQUEST_TIMEOUT,        // 408
      net::HTTP_GONE,                   // 410
      451,                              // Unavailable For Legal Reasons
      net::HTTP_INTERNAL_SERVER_ERROR,  // 500
      net::HTTP_BAD_GATEWAY,            // 502,
      net::HTTP_SERVICE_UNAVAILABLE,    // 503,
      net::HTTP_GATEWAY_TIMEOUT,        // 504,
      509,                              // Bandwidth Limit Exceeded
      520,                              // Web Server Returned an Unknown Error
      521,                              // Web Server Is Down
      523,                              // Origin Is Unreachable
      524,                              // A Timeout Occurred
      525,                              // SSL Handshake Failed
      526                               // Invalid SSL Certificate
  };

  return responses.find(response_code) != responses.end();
}

WEB_CONTENTS_USER_DATA_KEY_IMPL(HuhiWaybackMachineTabHelper)
