/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/net/url_context.h"

#include <memory>
#include <string>

#include "huhi/components/huhi_shields/browser/huhi_shields_util.h"
#include "huhi/components/huhi_shields/browser/huhi_shields_web_contents_observer.h"
#include "huhi/components/huhi_webtorrent/browser/buildflags/buildflags.h"
#include "huhi/components/huhi_webtorrent/browser/webtorrent_util.h"
#include "huhi/components/ipfs/buildflags/buildflags.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "content/public/browser/browser_thread.h"
#include "net/base/isolation_info.h"

#if BUILDFLAG(IPFS_ENABLED)
#include "huhi/components/ipfs/pref_names.h"
#include "huhi/components/ipfs/ipfs_constants.h"
#include "components/prefs/testing_pref_service.h"
#include "components/user_prefs/user_prefs.h"
#endif

namespace huhi {

namespace {

std::string GetUploadData(const network::ResourceRequest& request) {
  std::string upload_data;
  if (!request.request_body) {
    return {};
  }
  const auto* elements = request.request_body->elements();
  for (const network::DataElement& element : *elements) {
    if (element.type() == network::mojom::DataElementType::kBytes) {
      upload_data.append(element.bytes(), element.length());
    }
  }

  return upload_data;
}

}  // namespace

HuhiRequestInfo::HuhiRequestInfo() = default;

HuhiRequestInfo::HuhiRequestInfo(const GURL& url) : request_url(url) {}

HuhiRequestInfo::~HuhiRequestInfo() = default;

// static
std::shared_ptr<huhi::HuhiRequestInfo> HuhiRequestInfo::MakeCTX(
    const network::ResourceRequest& request,
    int render_process_id,
    int frame_tree_node_id,
    uint64_t request_identifier,
    content::BrowserContext* browser_context,
    std::shared_ptr<huhi::HuhiRequestInfo> old_ctx) {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);

  auto ctx = std::make_shared<huhi::HuhiRequestInfo>();
  ctx->request_identifier = request_identifier;
  ctx->method = request.method;
  ctx->request_url = request.url;
  // TODO(iefremov): Replace GURL with Origin
  ctx->initiator_url =
      request.request_initiator.value_or(url::Origin()).GetURL();

  ctx->referrer = request.referrer;
  ctx->referrer_policy = request.referrer_policy;

  ctx->resource_type =
      static_cast<blink::mojom::ResourceType>(request.resource_type);

  ctx->is_webtorrent_disabled =
#if BUILDFLAG(ENABLE_HUHI_WEBTORRENT)
      !webtorrent::IsWebtorrentEnabled(browser_context);
#else
      true;
#endif

  ctx->render_frame_id = request.render_frame_id;
  ctx->render_process_id = render_process_id;
  ctx->frame_tree_node_id = frame_tree_node_id;

  // TODO(iefremov): remove tab_url. Change tab_origin from GURL to Origin.
  // ctx->tab_url = request.top_frame_origin;
  if (request.trusted_params) {
    // TODO(iefremov): Turns out it provides us a not expected value for
    // cross-site top-level navigations. Fortunately for now it is not a problem
    // for shields functionality. We should reconsider this machinery, also
    // given that this is always empty for subresources.
    ctx->network_isolation_key =
        request.trusted_params->isolation_info.network_isolation_key();
    ctx->tab_origin = ctx->network_isolation_key
            .GetTopFrameOrigin()
            .value_or(url::Origin())
            .GetURL();
  }
  // TODO(iefremov): We still need this for WebSockets, currently
  // |AddChannelRequest| provides only old-fashioned |site_for_cookies|.
  // (See |HuhiProxyingWebSocket|).
  if (ctx->tab_origin.is_empty()) {
    ctx->tab_origin = huhi_shields::HuhiShieldsWebContentsObserver::
                          GetTabURLFromRenderFrameInfo(ctx->render_process_id,
                                                       ctx->render_frame_id,
                                                       ctx->frame_tree_node_id)
                              .GetOrigin();
  }

  if (old_ctx) {
    ctx->internal_redirect = old_ctx->internal_redirect;
    ctx->redirect_source = old_ctx->redirect_source;
  }

  Profile* profile = Profile::FromBrowserContext(browser_context);
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile);
  ctx->allow_huhi_shields =
      huhi_shields::GetHuhiShieldsEnabled(map, ctx->tab_origin);
  ctx->allow_ads = huhi_shields::GetAdControlType(
      map, ctx->tab_origin) == huhi_shields::ControlType::ALLOW;
  ctx->allow_http_upgradable_resource =
      !huhi_shields::GetHTTPSEverywhereEnabled(map, ctx->tab_origin);

  // HACK: after we fix multiple creations of HuhiRequestInfo we should
  // use only tab_origin. Since we recreate HuhiRequestInfo during consequent
  // stages of navigation, |tab_origin| changes and so does |allow_referrers|
  // flag, which is not what we want for determining referrers.
  ctx->allow_referrers = huhi_shields::AllowReferrers(
      map, ctx->redirect_source.is_empty() ? ctx->tab_origin :
                                             ctx->redirect_source);
  ctx->upload_data = GetUploadData(request);

#if BUILDFLAG(IPFS_ENABLED)
  auto* prefs = user_prefs::UserPrefs::Get(browser_context);
  ctx->ipfs_local = static_cast<ipfs::IPFSResolveMethodTypes>(
      prefs->GetInteger(kIPFSResolveMethod)) ==
          ipfs::IPFSResolveMethodTypes::IPFS_LOCAL;
#endif

  // TODO(fmarier): remove this once the hacky code in
  // huhi_proxying_url_loader_factory.cc is refactored. See
  // HuhiProxyingURLLoaderFactory::InProgressRequest::UpdateRequestInfo().
  if (old_ctx) {
    ctx->internal_redirect = old_ctx->internal_redirect;
    ctx->redirect_source = old_ctx->redirect_source;
  }

  return ctx;
}

}  // namespace huhi
