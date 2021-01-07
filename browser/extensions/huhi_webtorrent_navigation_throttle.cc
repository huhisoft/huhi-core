/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/extensions/huhi_webtorrent_navigation_throttle.h"

#include "base/bind.h"
#include "huhi/browser/extensions/huhi_component_loader.h"
#include "huhi/browser/profiles/profile_util.h"
#include "huhi/common/pref_names.h"
#include "huhi/common/url_constants.h"
#include "huhi/components/huhi_webtorrent/browser/buildflags/buildflags.h"
#include "huhi/components/huhi_webtorrent/browser/webtorrent_util.h"
#include "chrome/browser/extensions/extension_service.h"
#include "chrome/browser/profiles/profile.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/navigation_handle.h"
#include "content/public/browser/web_contents.h"
#include "content/public/common/url_constants.h"
#include "extensions/browser/extension_registry.h"
#include "extensions/browser/extension_system.h"
#include "extensions/common/constants.h"
#include "extensions/common/extension.h"

#if BUILDFLAG(ENABLE_HUHI_WEBTORRENT)
#include "huhi/browser/net/huhi_torrent_redirect_network_delegate_helper.h"
#endif

namespace extensions {

HuhiWebTorrentNavigationThrottle::HuhiWebTorrentNavigationThrottle(
        content::NavigationHandle* navigation_handle) :
    content::NavigationThrottle(navigation_handle),
    extension_registry_observer_(this),
    resume_pending_(false) {
  extension_registry_observer_.Add(
      ExtensionRegistry::Get(
          navigation_handle->GetWebContents()->GetBrowserContext()));
}

HuhiWebTorrentNavigationThrottle::~HuhiWebTorrentNavigationThrottle() {
  timer_.Stop();
}

content::NavigationThrottle::ThrottleCheckResult
HuhiWebTorrentNavigationThrottle::WillStartRequest() {
  // This handles magnet URLs and .torrent filenames in the URL but not
  // response headers.
  return CommonWillProcessRequestResponse();
}

content::NavigationThrottle::ThrottleCheckResult
HuhiWebTorrentNavigationThrottle::WillProcessResponse() {
  // This handles response headers with headers that indicate torrent content.
  // This is not as good as if we catch it in the WillStartRequest section
  // because the user will need to manually restart the request to make it work.
  return CommonWillProcessRequestResponse();
}

// static
bool HuhiWebTorrentNavigationThrottle::MaybeLoadWebtorrent(
  content::BrowserContext* context,
  const GURL& url) {
  // No need to load Webtorrent if pref is off or it is already enabled.
  if (!webtorrent::IsWebtorrentPrefEnabled(context) ||
      webtorrent::IsWebtorrentEnabled(context)) {
    return false;
  }

  extensions::ExtensionService* service =
    extensions::ExtensionSystem::Get(context)->extension_service();
  if (!service)
    return false;

  extensions::ComponentLoader* loader = service->component_loader();
  static_cast<extensions::HuhiComponentLoader*>(loader)->
    AddWebTorrentExtension();
  return true;
}

content::NavigationThrottle::ThrottleCheckResult
HuhiWebTorrentNavigationThrottle::CommonWillProcessRequestResponse() {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
  content::WebContents* web_contents = navigation_handle()->GetWebContents();

  // Is this navigation targeting an extension resource?
  const GURL& url = navigation_handle()->GetURL();
  // Note, if we use WillProcessResponse we can also use response headers, but
  // it would be too late to handle the request as WebTorrent in that case.
  // So the best we can do is via URL pattern match and magnet links.
  // Headers are null when processing WillStartRequest.
  auto* headers = navigation_handle()->GetResponseHeaders();
  bool is_torrent_file = headers ? webtorrent::IsTorrentFile(url, headers) :
      webtorrent::TorrentURLMatched(url);
  if ((url.SchemeIs(kMagnetScheme) || is_torrent_file) &&
       MaybeLoadWebtorrent(web_contents->GetBrowserContext(), url)) {
    resume_pending_ = true;
    return content::NavigationThrottle::DEFER;
  }

  return content::NavigationThrottle::PROCEED;
}

const char* HuhiWebTorrentNavigationThrottle::GetNameForLogging() {
  return "HuhiWebTorrentNavigationThrottle";
}

void HuhiWebTorrentNavigationThrottle::OnExtensionReady(
    content::BrowserContext* browser_context,
    const Extension* extension) {
  if (resume_pending_ &&
      extension->id() == huhi_webtorrent_extension_id) {
    ResumeThrottle();
  }
}

void HuhiWebTorrentNavigationThrottle::ResumeThrottle() {
  timer_.Stop();
  resume_pending_ = false;
  Resume();
}

}  // namespace extensions
